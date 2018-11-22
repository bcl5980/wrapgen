import clang.cindex
from clang.cindex import Config
from clang.cindex import _CXString
from clang.cindex import CursorKind
from clang.cindex import TypeKind
from clang.cindex import LinkageKind
from enum import Enum, unique

Config.set_compatibility_check(False)
Config.set_library_file("/usr/lib/llvm-6.0/lib/libclang.so")


class astTypedef(object):
    def __init__(self, node):
        self.top = node
        self.type = node.displayname
        self.underlying = node.underlying_typedef_type.spelling
        self.canonical = node.type.get_canonical().spelling


class astVariable(object):
    def __init__(self, node):
        self.top = node
        # to do here if have global variable

def ostream_basic(field, fieldname, indx):
    strTmpOStream = ''
    if (field.name.find('pad') != -1 or field.name.find('reserved') != -1) and field.array_count != 0:
        return strTmpOStream
        
    if field.array_count == 0 or field.type.kind == TypeKind.CHAR_S:
        strTmpOStream += '<< "    ' + fieldname + ' = " << s.'
        strTmpOStream += fieldname + ' << "\\n" \n        '
    else:
        for i in range(field.array_count):
            strTmpOStream += '<< "    ' + fieldname + '[{}] = " << s.'.format(i)
            strTmpOStream += fieldname + '[{}] << "\\n" \n        '.format(i)

    return strTmpOStream


def ostream_substructure(struct, prefix, indx = 0):
    strTmpOStream = '<< "' + '    ' * indx + prefix + ' {\\n"\n        '
    for field in struct.fields:
        substruture = struct.symbols.get(field.canonical)
        fieldname = prefix + '.' + field.name
        if substruture == None:
            ostream_basic(field, fieldname, indx)
        else:
            strTmpOStream += ostream_substructure(substruture, fieldname, indx + 1)
    
    strTmpOStream += '<< "' + '    ' * indx +'}\\n"\n        '
    
    return strTmpOStream

class astStruct(object):
    class field:
        def __init__(self, node):
            self.top = node
            self.type = node.type
            self.pcount = 0
            self.array_count = 0
            if self.type.kind == TypeKind.CONSTANTARRAY:
                self.array_count = self.type.element_count
                self.type = self.type.element_type
            if self.type.kind == TypeKind.POINTER:
                self.type = self.type.get_pointee()
                self.pcount += 1
            self.canonical = self.type.get_canonical().spelling
            self.name = node.spelling

    def parser_fields(self, node):
        for i in node.get_children():
            if i.kind == CursorKind.FIELD_DECL:
                sf = astStruct.field(i)
                self.fields.append(sf)
            elif i.kind == CursorKind.STRUCT_DECL or i.kind == CursorKind.UNION_DECL:
                struct = astStruct(i)
                if i.is_anonymous():
                    self.fields = self.fields + struct.fields
                    for s in struct.symbols:
                        self.symbols[s] = struct.symbols[s]
                else:
                    self.symbols[struct.typename] = struct

    def __init__(self, node):
        self.top = node
        self.is_union = node.kind == CursorKind.UNION_DECL
        if self.is_union:
            self.typename = node.type.spelling
        else:
            self.typename = node.type.spelling
        self.fields = []
        self.symbols = {}

        self.parser_fields(node)

    @property
    def ostream(self):
        if not hasattr(self, '_ostream'):
            strOStream = 'std::ostream& operator<<(std::ostream& os, const ' + self.typename + '& s)\n'
            strOStream += '{\n'
            strOStream += '    return os << "' + self.typename + ' {\\n"\n        '
            for field in self.fields:
                substruture = self.symbols.get(field.canonical)
                if substruture == None:
                    strOStream += ostream_basic(field, field.name, 0)
                else:
                    strOStream += ostream_substructure(substruture, field.name, 1)
            strOStream += '<< "}\\n";\n'
            strOStream += '}\n'
            self._ostream = strOStream

        return self._ostream

class astEnum(object):
    def __init__(self, node):
        self.top = node
        self.name = 'enum ' + node.type.spelling
        self.nam2val = {}
        self.val2nam = {}
        for i in node.get_children():
            if i.kind == CursorKind.ENUM_CONSTANT_DECL:
                self.nam2val[i.displayname] = i.enum_value
                self.val2nam[i.enum_value] = i.displayname


class astFunction(object):
    class param(object):
        def __init__(self, node):
            self.type = node.type.spelling
            self.name = node.spelling

    def __init__(self, node):
        self.top = node
        self.name = node.spelling
        self.ret = node.result_type.spelling
        self.params = []
        for i in node.get_children():
            if i.kind == CursorKind.PARM_DECL:
                param = astFunction.param(i)
                self.params.append(param)


class astClass(object):
    def __init__(self, node):
        self.top = node
        self.name = node.spelling
        self.methods = []
        self.structs = []
        self.enums = []
        for i in node.get_children():
            if i.kind == CursorKind.CXX_METHOD:
                parsefunction(i, self.methods)
            if CursorKind.ENUM_DECL == i.kind:
                parseenum(i, self.enums)
            elif i.kind == CursorKind.STRUCT_DECL or i.kind == CursorKind.UNION_DECL:
                parsestruct(i, self.structs)

class astFile(object):
    def __init__(self, node):
        self.gEnums = []
        self.gStructs = []
        self.gVars = []
        self.gClasses = []
        self.gEFuncs = []
        self.gIFuncs = []
        self.gTypedef = []
        self.top = node
        self.filename = node.spelling


def printnode(node, indent, f=None):
    text = node.displayname
    kind = str(node.kind)[str(node.kind).index('.')+1:]
    print(' ' * indent, '{} {}'.format(kind, text), file=f)
    for i in node.get_children():
        printnode(i, indent + 2, f=f)


def parsevariable(node, v):
    var = astVariable(node)
    v.append(var)


def parseenum(node, e):
    enum = astEnum(node)
    if len(enum.val2nam) != 0:
        e.append(enum)


def parsestruct(node, s):
    struct = astStruct(node)
    if len(struct.fields) != 0:
        s.append(struct)


def parsetypedef(node, t):
    typedef = astTypedef(node)
    t.append(typedef)


def parsefunction(node, f):
    if node.is_function_inlined() == False:
        function = astFunction(node)
        f.append(function)

def parseclass(node, c):
    clas = astClass(node)
    c.append(clas)

def parseglobal(node, cf):
    for i in node.get_children():
        if CursorKind.ENUM_DECL == i.kind:
            parseenum(i, cf.gEnums)
        elif i.kind == CursorKind.STRUCT_DECL or i.kind == CursorKind.UNION_DECL:
            parsestruct(i, cf.gStructs)
        elif CursorKind.TYPEDEF_DECL == i.kind:
            parsetypedef(i, cf.gTypedef)
        elif CursorKind.FUNCTION_DECL == i.kind:
            if i.linkage == LinkageKind.INTERNAL:
                parsefunction(i, cf.gIFuncs)
            elif i.linkage == LinkageKind.EXTERNAL:
                parsefunction(i, cf.gEFuncs)
        elif CursorKind.VAR_DECL == i.kind:
            parsevariable(i, cf.gVars)
        elif CursorKind.CLASS_DECL == i.kind:
            parseclass(i, cf.gClasses)
        elif CursorKind.UNEXPOSED_DECL == i.kind:
            parseglobal(i, cf)


def dumpnode(node):
    with open('./dumpnode.txt', 'w') as f:
        printnode(node, 0, f=f)

def dump_struct_ostream(cf):
    with open('./struct_ostream.h', 'w') as f:
        print ('#include <sstream>', file=f)
        print ('#include <string>', file=f)
        print ('#include "{}"\n'.format(cf.filename), file=f)
        print ('using std::string;', file=f)
        print ('using std::ostringstream;\n', file=f)
        for s in cf.gStructs:
            print(s.ostream, file=f)

def main():
    index = clang.cindex.Index.create()
    tu = index.parse('nvcuda.cpp',  # '../runtime/runtimeapi/cuda_runtime.cpp',
                     ['-x', 'c++', '-std=c++11', '-D__CODE_GENERATOR__'])

    #dumpnode(tu.cursor)

    cf = astFile(tu.cursor)
    parseglobal(tu.cursor, cf)

    dump_struct_ostream(cf)


if __name__ == '__main__':
    main()
