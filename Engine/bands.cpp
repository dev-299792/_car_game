#include "bands.h"
#include "Graphics.h"

bands::bands(vect p)
{
	pos = p;
	c = Colors::White;
	height = 40.0f;
	width = 5.0f;
}

void bands::display(Graphics& gfx)
{
	gfx.DrawRectR((int)pos.x, (int)pos.y, (int)width, (int)height, c);
}

void bands::move(vect v,float dt)
{
	pos = pos - v * dt;
}
