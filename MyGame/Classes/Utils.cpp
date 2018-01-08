#include "Utils.h"

USING_NS_CC;


//floor() 方法可对一个数进行下舍入。
//random() 方法可返回介于 0 ~ 1 之间的一个随机数。
float Utils::RandomRange(int min, int max)
{
    return min + (max - min) * std::rand();
}

int Utils::RandomRangeInt(int e, int t) 
{
    return std::floor(std::rand() * (t - e + 1)) + e;
}
/*
std::string Utils::IntToTimeString(int e)
{
    var t = std::floor(e / 60),
        n = t.toString(),
        r = e % 60,
        i;
    return r < 10 ? i = "0" + r : i = r.toString(), n + "d" + i;
}
*/
float Utils::RadToGrad(float e)
{
    return e * 180 / M_PI;
}

float Utils::GradToRad(float  e) 
{
    return e * M_PI / 180;
}
/*
std::string Utils::GetScoreString(int e) 
{
    var t = e.toString();
    switch (t.length) {
        case 1:
            t = "00000" + t;
            break;
        case 2:
            t = "0000" + t;
            break;
        case 3:
            t = "000" + t;
            break;
        case 4:
            t = "00" + t;
            break;
        case 5:
            t = "0" + t
    }
    return t;
}
*/
