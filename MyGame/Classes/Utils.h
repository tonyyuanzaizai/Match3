#ifndef __Match3_Utils_LAYER_H__
#define __Match3_Utils_LAYER_H__

#include "cocos2d.h"

//#define M_PI 3.14159265358979323846

class Utils
{

// public static function
public:
    static float RandomRange(int min, int max);
    static int RandomRangeInt(int e, int t);
    //static std::string IntToTimeString(int e);
    static float RadToGrad(float e);
    static float GradToRad(float  e);
    //static std::string GetScoreString(int e);

};

#endif // __Match3_Utils_LAYER_H__

//////


