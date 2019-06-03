#include "Vect.h"
#include <cmath>

vect::vect(float a, float b)
{
	x = a;
	y = b;
}

vect::vect(const vect& a)
{
	x = a.x;
	y = a.y;
}

vect vect::operator+(vect right)
{
	return vect(x+right.x,y+right.y);
}

vect vect::operator-(vect right)
{
	return vect(x - right.x, y - right.y);
}

vect vect::operator*(float right)
{
	return vect(x*right,y*right);
}

float vect::get_angle()
{
	if (x == 0 && y == 0)
	{
		return NAN;
	}
	if (x > 0 && y > 0)
	{
		return -atan(y / x);
	}
	if (x > 0 && y < 0)
	{
		return atan(y / x);
	}
	if (x < 0 && y < 0)
	{
		return  float(M_PI) - atan(y / x);
	}
	if (x < 0 && y > 0)
	{
		return -float(M_PI) + atan(y / x);
	}
	return NAN;
}

void vect::set_angle(float theta)
{
	float mag = magnitude();
	x = mag * cos(theta);
	y = mag * sin(-theta);
}

float vect::magnitude()
{
	return (sqrt(x * x + y * y));
}

float vect::mag_squared()
{
	return(x * x + y * y);
}

