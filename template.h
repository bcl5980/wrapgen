#ifdef WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <mutex>
#include <fstream>
#include <map>
#include <string>
#include <cuda.h>
#include <stdlib.h>

using std::ofstream;
using std::map;
using std::string;
using std::mutex;


#definefp typedef #result(#calltype *p#name)(#params);

class wrap
{
public:
#memfp p#name m_#name;

#esdef map<int, string> m_mapES#name;

    bool m_bLog;
    ofstream m_oflog;

    wrap()
    {
        m_bLog = getenv("LOG_CUDA") != nullptr;
        if (m_bLog)
        {
            m_oflog.open("log.txt", std::ios::out);
        }

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
static mutex gm;

#funcdefstart
#result #calltype #name(#params)
{
    #result ret;
    ret = g.m_#name(#notypeparam);

    if (g.m_bLog)
    {
        gm.lock();
        g.m_oflog << __FUNCTION__ << " start:\n";
        g.m_oflog << "#result:" << g.m_mapES#result[ret] << '\n';
#fparams g.m_oflog << #paramlog;
        g.m_oflog << __FUNCTION__ << " end:\n\n";
        gm.unlock();
    }

    return ret;
}
#funcdefend
