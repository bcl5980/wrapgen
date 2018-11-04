#include <windows.h>
#include <fstream>
#include "cuda_wrap.h"

using std::ofstream;

#definefp typedef #result(#calltype *p#name)(#params);

class wrap
{
public:
#memfp p#name m_#name;

    wrap()
    {
        HMODULE h = LoadLibrary("nvcuda_orig.dll");
#getfp m_#name = (p#name)GetProcAddress(h, "#name");
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
    oflog << __FUNCTION__ << '\n';
    ret = g.m_#name(#notypeparam);
    return ret;
}
#funcdefend
