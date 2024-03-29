/**********************************************************************************
* \file			Math.cpp
* \brief		Abstraction of math functions
* \author		Jun Yi,			Chong,		50% Code Contribution
*				Farzaana Binte, Roslan,		50% Code Contribution
*
*				Long Description
*				- Smooth increment (lerp, step) 
*				- Vector2D maths
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "Math.h"
#include <cmath>
#include "AEEngine.h"

// for the floating point 
static const float TOLERANCE_FLOAT = 0.0001f;

float MBMath_Lerp(float a, float b, float time)
{
	return a + ((b - a) * time);
}

float MBMath_LerpRotation(float a, float b, float time)
{
    //Angle will be in radian (-PI to PI)
    float magnitude = b - a;

    if (magnitude > PI)                 //Clockwise
    {
        a += 2 * PI;
    }
    else if (magnitude < -PI)           //Anti-Clockwise
    {
        a -= 2 * PI;
    }
    return  a + ((b - a) * time);
}

float MBMath_Smoothstep(float edge0, float edge1, float x) 
{
    // Scale, bias and saturate x to 0..1 range
    x = MBMath_Clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    // Evaluate polynomial
    return x * x * (3 - (2 * x)); //(3-2x)x^2
}

// Keep x within lowerLimit and upperLimit...if exceed will set x to the min and max
float MBMath_Clamp(float x, float lowerlimit, float upperlimit) 
{
    if (x < lowerlimit)
        x = lowerlimit;
    if (x > upperlimit)
        x = upperlimit;
    return x;
}

float MBMath_SmoothDamp(float current, float target, float* currentVelocity, float smoothTime, float baseMaxSpeed, float deltaTime)
{
    smoothTime = AEMax(0.0001f, smoothTime);                                        //smoothTime cant be too small
    float num = 2.0f / smoothTime;                                                  //         
    float num2 = num * deltaTime;                                                   //
    float num3 = 1.0f /                                                             //
        (1.0f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);          //
    float num4 = current - target;                                                  //
    float num5 = target;                                                            //
    float num6 = baseMaxSpeed * smoothTime;                                             //
    num4 = AEClamp(num4, -num6, num6);                                              //
    target = current - num4;                                                        //
    float num7 = (*currentVelocity + num * num4) * deltaTime;                        //
    *currentVelocity = (*currentVelocity - num * num7) * num3;                        //
    float num8 = target + (num4 + num7) * num3;                                     //
    if (num5 - current > 0.0f == num8 > num5)                                       //
    {
        num8 = num5;
        *currentVelocity = (num8 - num5) / deltaTime;
    }
    return num8;
}

float MBMath_DotProduct(const AEVec2& vec1, const AEVec2& vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

// May have floating point error; Use this if you really need to
float MBMath_getLengthofVector(const AEVec2& vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

// Getting the normalized vector 
AEVec2 MBMath_getNormalizedVector(const AEVec2& vector)
{
    float lengthofVector = MBMath_getLengthofVector(vector);

    if (lengthofVector < TOLERANCE_FLOAT)
    {
        return vector; 
    }

    return AEVec2{ (vector.x / lengthofVector), (vector.y / lengthofVector) };
}

// Getting the normals of the Vector
AEVec2 MBMath_getNormalofVector(const AEVec2& vector)
{
    return AEVec2{ -vector.y, vector.x };
}