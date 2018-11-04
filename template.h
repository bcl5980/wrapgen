#include <windows.h>
#include "cuda_wrap.h"

#definefp typedef #result(#calltype *p#name)(#params);

class wrap
{
public:
#memfp p#name m_#name;

    wrap()
    {
        HMODULE h = LoadLibrary("nvcuda.dll");
#getfp m_#name = (p#name)GetProcAddress(h, "#name");
    }
};

static wrap g;

#funcdefstart
#result #calltype #name(#params)
{
    #result ret;
    ret = g.m_#name(#notypeparam);
    return ret;
}
#funcdefend
