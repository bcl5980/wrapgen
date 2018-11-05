#ifdef WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <fstream>
#include <map>
#include <string>
#include "cudawrap.h"

using std::ofstream;
using std::map;
using std::string;

#definefp typedef #result(#calltype *p#name)(#params);

class wrap
{
public:
#memfp p#name m_#name;

#esdef map<int, string> m_mapES#name;

    wrap()
    {
#ifdef WIN32
        HMODULE h = LoadLibrary("nvcuda_orig.dll");
        #define GetFunction(h, x) GetProcAddress(h, x)
#else
        void* h = dlopen("libcuda_orig.so", RTLD_LAZY);
        #define GetFunction(h, x) dlsym(h, x)
#endif

#getfp m_#name = (p#name)GetFunction(h, "#name");

#esimp m_mapES#name[#paramv] = "#paramn";
    }

    ~wrap()
    {

    }
};

static wrap g;
static ofstream oflog("log.txt");

#funcdefstart
#result #calltype #name(#params)
{
    #result ret;
    ret = g.m_#name(#notypeparam);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "#result:" << g.m_mapES#result[ret] << '\n';
#fparams oflog << #paramlog;
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}
#funcdefend
