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

using std::map;
using std::mutex;
using std::ofstream;
using std::string;

#definefp typedef #result(#calltype *p#name)(#params);

#if WIN32
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

void GetExcName(char *processname)
{
    GetModuleFileName(NULL, szExePath, sizeof(szExePath));
    PathRemoveFileSpec(szExePath);
}

#else
#include <string.h>
#include <unistd.h>
void GetExcName(char *processname)
{
    char *path_end;
    char path[256];
    if (readlink("/proc/self/exe", path, 256) <= 0)
        return;
    path_end = strrchr(path, '/');
    if (path_end == NULL)
        return;
    ++path_end;
    strcpy(processname, path_end);
    *path_end = '\0';
}
#endif

class wrap
{
  public:
#memfp p#name m_#name;

#esdef map< int, string > m_mapES#name;

    bool m_bLog;
    ofstream m_oflog;

    wrap()
    {
        m_bLog = getenv("LOG_CUDA") != nullptr;
        if (m_bLog)
        {
            char processName[256];
            GetExcName(processName);
            char fileName[256] = {};
            sprintf(fileName, "log_%s.txt", processName);
            m_oflog.open(fileName, std::ios::out);
            m_oflog.setf(std::ios::showbase);
            m_oflog.setf(std::ios_base::hex, std::ios_base::basefield);
        }

#ifdef WIN32
        HMODULE h = LoadLibrary("nvcuda_orig.dll");
#define GetFunction(h, x) GetProcAddress(h, x)
#else
        void *h = dlopen("libcuda_orig.so", RTLD_LAZY);
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
        g.m_oflog << "#result: " << g.m_mapES#result[ret] << '\n';
#fparams g.m_oflog << #paramlog;
        g.m_oflog << __FUNCTION__ << " end:\n\n";
        gm.unlock();
    }

    return ret;
}
#funcdefend
