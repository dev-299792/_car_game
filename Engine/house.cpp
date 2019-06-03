#include "house.h"

house::house(vect p)
{
	pos = p;
}


void house::display(Graphics& gfx)
{
	gfx.DrawRectR((int)pos.x, (int)pos.y, 40, 25, Colors::MakeRGB(255u, 25u, 25u));
	gfx.DrawRectR((int)pos.x, (int)pos.y+25, 40, 25, Colors::MakeRGB(255u, 125u, 125u));
	gfx.DrawRectR((int)pos.x, (int)pos.y+50, 40, 50, Colors::MakeRGB(255u, 25u, 25u));
	gfx.DrawRectR((int)pos.x, (int)pos.y + 100, 40, 50, Colors::MakeRGB(255u, 125u, 125u));
	

	//gfx.DrawRotatedTriangleR(pos.x +13, pos.y -7, 50, 15, pos.x + 68, pos.y-7, 0, Colors::Black);
	
	gfx.DrawRectR((int)pos.x + 40, (int)pos.y, 15, 150, Colors::Black);
	//gfx.DrawRotatedTriangleR(pos.x + 13+15, pos.y - 7 + 50+50, 100, 30, pos.x + 68+15, pos.y - 7 + 50+50, 0, Colors::Black);
}

void house::move(vect v, float dt)
{
	pos = pos - v * dt;
}