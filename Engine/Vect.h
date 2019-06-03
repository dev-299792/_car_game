#pragma once
#include<corecrt_math_defines.h>

class vect
{
public:
	float x;
	float y;
	bool zero;
public:
	vect() = default;
	vect(float a, float b);
	vect(const vect& a);
	vect operator+(vect right);
	vect operator-(vect right);
	vect operator*(float right);
	float get_angle();
	void set_angle(float theta);
	float magnitude();
	float mag_squared();
};

