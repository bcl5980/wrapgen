#include <windows.h>
#include <fstream>
#include <map>
#include <string>
#include "cuda_wrap.h"

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
        HMODULE h = LoadLibrary("nvcuda_orig.dll");
#getfp m_#name = (p#name)GetProcAddress(h, "#name");

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
