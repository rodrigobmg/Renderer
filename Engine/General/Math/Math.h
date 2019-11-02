#pragma once
#include <DirectXMath.h>

namespace Math
{
	static constexpr float PI = 22.0f / 7.0f;
	static constexpr float DEG2RAD = PI / 180.0f;
	static constexpr float RAD2DEG = 1.0f / DEG2RAD;

	template<class T>
	T Clamp(const T& low, const T& high, const T& value)
	{
		return (value > high) ? high : ((value < low) ? low : value);
	}
}