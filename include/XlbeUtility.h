#ifndef __XLBE_UTILITY_H__
#define __XLBE_UTILITY_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

//////////////////////////////////////////////////////////////////////////////////////
const float M_PI = 3.14159265358979323846f;
const float M_PI_2 = 1.57079632679489661923f;
const float M_PI_4 = 0.785398163397448309616f;
const float M_1_PI = 0.318309886183790671538f;
const float M_2_PI = 0.636619772367581343076f;

//////////////////////////////////////////////////////////////////////////////////////
namespace xlbe_utility {

//////////////////////////////////////////////////////////////////////////////////////
struct fast_less_compare
{
    bool operator() (const std::string& a, const std::string& b) const
    {
        const size_t la = a.size();
        const size_t lb = b.size();

        if (la == lb)
            return (std::memcmp(a.c_str(), b.c_str(), la*sizeof(char)) < 0);

        return (la < lb);
    }
};

static unsigned int g_seed=0;
static void random_seed(int seed)
{
	if(!seed) g_seed = time(0);
	else g_seed = seed;
}

static int random_int(int min, int max)
{
	g_seed = 214013 * g_seed + 2531011;
	return min + (g_seed ^ g_seed>>15) % (max - min + 1);
}

static float random_float(float min, float max)
{
	g_seed = 214013 * g_seed + 2531011;

	return min + (g_seed >> 16) * (1.0f / 65535.0f) * (max - min);
}

static std::string wstring2string(const std::wstring& ws)
{
    std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";
    setlocale(LC_ALL, "chs");
    const wchar_t* _Source = ws.c_str();
    size_t _Dsize = 2 * ws.size() + 1;
    char *_Dest = new char[_Dsize];
    memset(_Dest,0,_Dsize);
    wcstombs(_Dest,_Source,_Dsize);
    std::string result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}

static std::wstring string2wstring(const std::string& s)
{
    setlocale(LC_ALL, "chs"); 
    const char* _Source = s.c_str();
    size_t _Dsize = s.size() + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest,_Source,_Dsize);
    std::wstring result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, "C");
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////
}
#endif