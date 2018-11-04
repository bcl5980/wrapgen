import re

def SplitUnit(strLines, strPrefix):
    units = []
    unit = ''
    for line in strLines:
        line = line.strip()
        if line.startswith('#'):
            continue
        if line.startswith(strPrefix):
            unit = line
            brackets = 0
            if line.endswith('{'):
                brackets = brackets + 1
            if not line.endswith(';'):
                continue
        elif unit.startswith(strPrefix):
            unit = unit + line
            if line.find('{') != -1:
                brackets = brackets + 1
            elif line.find('}') != -1:
                brackets = brackets - 1

            if not line.endswith(';'):
                continue
            if brackets != 0:
                continue
        elif line.find('(') != -1:
            unit = line

        if unit != '':
            units.append(unit)
            unit = ''
    
    return units

class cenum(object):
    def __init__(self, name=''):
        self.name = name
        self.enums = {}
        self.values = {}

    def init(self, unit):
        start = unit.find('{') + 1
        end = unit.rfind('}')
        enummembers = unit[start : end].strip().split(',')
        start = end + 1
        end = unit.find(';')
        self.name = unit[start:end].strip()
        for member in enummembers:
            if member.find('=') != -1:
                name, svalue = member.split('=')
                if svalue.find('x') != -1:
                    value = int(svalue, 16)
                    self.enums[name] = value
                    self.values[value] = name
                elif svalue.find('<<') != -1:
                    value = eval(svalue)
                    self.enums[name] = value
                    self.values[value] = name
                else:
                    value = int(svalue)
                    self.enums[name] = value
                    self.values[value] = name
            else:
                value = value + 1
                name = member
                self.enums[member] = value 
                self.values[value] = name

class cvar(object):
    def __init__(self, vtype='', name=''):
        self.type = vtype
        start = name.find('[')
        if (start) != -1:
            end = name.find(']')
            strarray = name[start + 1:end]
            self.arraycnt = int(strarray)
            name = name[:start]
    
        i = 0
        while name[i] == '*':
            i = i + 1
        self.pcnt = i
        self.name = name[i:]

class cstruct(object):
    def __init__(self, name=''):
        self.name = name
        self.isunion = False
        self.structs = {}
        self.empty = []
        self.varibles = {}
        self.varindex = []

    def init(self, unit):
        unit = unit.replace(';', '; ')
        start = unit.find('{')
        end = unit.rfind('}')
        if start != -1 and end != -1:
            start = start + 1
            members = unit[start : end].strip().split(' ')
            if unit.startswith('typedef'):
                start = end + 1
                end = unit.rfind(';')
                self.name = unit[start:end].strip()
                if unit.startswith('typedef union'):
                    self.isunion = True
            elif unit.startswith('struct') or unit.startswith('union'):
                end = start - 1
                start = unit.find(' ')
                self.name = unit[start:end].strip()
                if unit.startswith('union'):
                    self.isunion = True          

            vtype = ''
            content = ''
            i = 0
            size = len(members)
            while i < size:
                member = members[i].strip()
                if member == '':
                    i = i + 1
                    continue
                elif member == 'struct' or member == 'union':
                    content = member + ' '
                    i = i + 1
                    brackets = 0
                    while True:
                        member = members[i] + ' '
                        content = content + member
                        if member.startswith('{') :
                            brackets = brackets + 1
                        elif member.startswith('}') :
                            brackets = brackets - 1
                            if brackets == 0 :
                                break
                        i = i + 1

                    struct = cstruct()
                    struct.init(content)
                    if struct.name == '':
                        self.empty.append(struct)
                        vtype = '__' + str(len(self.empty))
                        struct.name = vtype
                    else:
                        vtype = struct.name
                        self.structs[struct.name] = struct
                else:
                    if member.endswith(';'):
                        name = member[:-1]
                        var = cvar(vtype, name)
                        self.varibles[var.name] = var
                        self.varindex.append(var.name)
                    elif vtype == 'const' or vtype == 'unsigned':
                        vtype = vtype + ' ' + member
                    else:
                        vtype = member
                
                i = i + 1

class cfuntion(object):
    def __init__(self, name='', ret='', calltype=''):
        self.ret = ret
        self.name = name
        self.calltype = calltype
        self.params = []
        self.strparams = ''
        self.notypeparams = ''
        self.deprecated = False
        
    def init(self, params):
        if params != 'void':
            self.strparams = params
            self.notypeparams = ''
            elements = params.split(',')
            for e in elements:
                spidx = e.rfind(' ')
                stype = e[:spidx]
                name = e[spidx + 1:]
                var = cvar(vtype=stype, name=name)
                self.params.append(var)
                self.notypeparams = self.notypeparams + var.name +','
            self.notypeparams = self.notypeparams[:-1]


gtype = {}
genums = {}
gstructs = {}
gfunctions = {}
gfuncpointer = {}

gtype['size_t'] = 'basic'
gtype['char'] = 'basic'
gtype['unsigned char'] = 'basic'
gtype['short'] = 'basic'
gtype['unsigned short'] = 'basic'
gtype['int'] = 'basic'
gtype['unsigned int'] = 'basic'
gtype['__int32'] = 'basic'
gtype['unsigned __int32'] = 'basic'
gtype['__int64'] = 'basic'
gtype['unsigned __int64'] = 'basic'
gtype['long'] = 'basic'
gtype['unsigned long'] = 'basic'
gtype['long long'] = 'basic'
gtype['unsigned long long'] = 'basic'

with open('cuda_wrap.h', 'r') as f:
    strLines = f.readlines()
    units = SplitUnit(strLines, 'typedef')

    for unit in units:
        if unit.startswith('typedef'):
            if unit.startswith('typedef enum'):
                enum = cenum()
                enum.init(unit)
                genums[enum.name] = enum
                gtype[enum.name] = 'enum'
            elif unit.startswith('typedef struct') or unit.startswith('typedef union'):
                if unit.startswith('typedef struct'):
                    bStruct = True
                else:
                    bStruct = False
                if unit.find('{') != -1:
                    struct = cstruct()
                    struct.init(unit)
                    gstructs[struct.name] = struct
                    gtype[struct.name] = 'struct'
                elif unit.endswith(';'):
                    start = unit.rfind('*')
                    if start != -1:
                        end = unit.rfind(';')
                        ctypename = unit[start + 1:end]
                        if bStruct:
                            gtype[ctypename] = 'struct*'
                        else:
                            gtype[ctypename] = 'union*'
            elif unit.find('(') == -1:
                start = unit.rfind(' ')
                end = unit.rfind(';')
                ctypename = unit[start:end].strip()
                end = start
                start = unit.find(' ')
                gtype[ctypename] = unit[start:end].strip()
            else:
                #function pointer
                unit = unit[7:].strip()
                end = unit.find('(')
                result = unit[:end]
                start = end + 1
                end = unit.find(' ', start)
                calltype = unit[start:end]
                start = end + 2
                end = unit.find(')', start)
                name = unit[start:end]
                start = end + 2
                end = unit.find(')', start)
                params = unit[start:end]
                func = cfuntion(name=name, ret=result, calltype=calltype)
                func.init(params)
                gfuncpointer[func.name] = func
                gtype[func.name] = 'function*'
        elif unit.find('__stdcall') != -1:
            #function
            deprecated = False
            if unit.startswith('__declspec(deprecated)'):
                deprecated = True
                unit = unit[unit.find(' '):].strip()

            end = unit.find(' ')
            result = unit[:end].strip()
            start = end + 1
            end = unit.find(' ', start)
            calltype = unit[start:end]
            start = end + 1
            end = unit.find('(', start)
            name = unit[start:end]
            func = cfuntion(name=name, ret =result, calltype=calltype)
            start = end + 1
            end = unit.find(')', start)
            params = unit[start:end]
            func.init(params)
            func.deprecated = deprecated
            gfunctions[func.name] = func

    with open('template.h', 'r') as f2:
        strLines = f2.readlines() 
        output = []
        logcontent = False
        content = ''
        for line in strLines:
            if logcontent:
                content = content + line

            if line.startswith('#definefp'):
                line = line[9:].strip()
                for name in gfunctions:
                    deffp = line.replace('#result', gfunctions[name].ret)
                    deffp = deffp.replace('#calltype', gfunctions[name].calltype)
                    deffp = deffp.replace('#name', name)
                    deffp = deffp.replace('#params', gfunctions[name].strparams)
                    output.append(deffp+'\n')
            elif line.startswith('#memfp') or line.startswith('#getfp'):
                line = line[6:].strip()
                for name in gfunctions:
                    output.append(line.replace('#name', name)+'\n')
            elif line.startswith('#funcdefstart'):
                logcontent = True
                content = ''
            elif line.startswith('#funcdefend'):
                content = content[:content.rfind('#')]
                for name in gfunctions:
                    impfunc = content.replace('#result', gfunctions[name].ret)
                    impfunc = impfunc.replace('#calltype', gfunctions[name].calltype)
                    impfunc = impfunc.replace('#name', name)
                    impfunc = impfunc.replace('#params', gfunctions[name].strparams)
                    impfunc = impfunc.replace('#notypeparam', gfunctions[name].notypeparams)
                    output.append(impfunc+'\n')
            elif logcontent == False:
                output.append(line)

        defout = "LIBRARY nvcuda\nEXPORTS\n"
        for name in gfunctions:
            defout = defout + '\t' + name + '\n'

        with open('nvcuda.cpp', 'w') as f3:
            f3.writelines(output)

        with open('nvcuda.def', 'w') as f3:
            f3.write(defout)