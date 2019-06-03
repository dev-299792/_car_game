#pragma once

#include "Colors.h"
#include "Graphics.h"
#include "Vect.h"

class bands
{
	vect pos;
	Color c;
	float height;
	float width;
public:
	bands() = default;
	bands(vect pos);
	void display(Graphics& gfx);
	void move(vect v,float dt);
};