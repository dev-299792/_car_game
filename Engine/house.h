#pragma once

#include "Colors.h"
#include "Graphics.h"
#include "Vect.h"

class house
{
	vect pos;

public:
	house() = default;
	house(vect pos);
	void display(Graphics& gfx);
	void move(vect v, float dt);
};