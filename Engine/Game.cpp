
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	now(std::chrono::steady_clock::now()),
	prev(std::chrono::steady_clock::now()),
	duration(now - prev)
{

	for (int i = 0; i < 5; i++)
	{
		robot_cars[i].initiate(car_pos[i]);
	}

	for (int i = 0; i < 7; i++)
	road_mid_bands[i] = bands(vect(293.0f, 83.0f * i));

	_house = house(vect(70,200));
}

void Game::Go()
{
	gfx.BeginFrame();

	if (distance_covered < total_distance)
	{
		UpdateModel();
	}

	ComposeFrame();
	gfx.EndFrame();
}

void Game::FinishLine()
{
	int i = 0;
	if (distance_covered > total_distance * .7)
	{
		if (pos_final.y > 0)
		{
			int x = ((int(pos_final.x)) / 10) * 10 - 45;
			int y = (int)pos_final.y;

			while (x < 420)
			{
				if ((i % 2 == 0))
					gfx.DrawRect(x, y, 10, 10, Colors::White);
				else
					gfx.DrawRect(x, y, 10, 10, Colors::Black);

				x += 10;
				i++;
			}
		}
	}

	gfx.DrawRect(18, int(560), 29, 2, Colors::White);
	gfx.DrawRect(18, int(40), 29, 2, Colors::White);
}

void Game::UpdateModel()
{
	prev = now;
	now = std::chrono::steady_clock::now();
	duration = now - prev;
	car0.set_dt(duration);

	for (int i = 0; i < 5; i++)
	{
		robot_cars[i].set_dt(duration);
	}

	if (!car0.crashed())
	{
		if (wnd.kbd.KeyIsPressed(VK_LEFT) && wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			//do nothing
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			car0.move_left(.5f);
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
		car0.move_right(.5f);
		}
		if (wnd.kbd.KeyIsPressed(VK_UP) && wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			//do nothing
		}
		else if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			car0.accelerate();
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			car0.deaccelerate();
		}

		car0.drag();
		car0.friction();

		if (car0.on_boundry())
		{
			car0.c1 = Colors::Blue;
		}
		else
		{
			car0.c1 = Colors::Red;
		}

		car0.out_of_boundry();

		for (int i = 0; i < 5; i++)
		{
			robot_cars[i].move_relative(car0.getv());
		}


		for (int i = 0; i < 5; i++)
		{
			car0.collision(robot_cars[i].getp());
		}

	}
	else
	{
	for (int i = 0; i < 5; i++)
	{
		robot_cars[i].move_relative(car0.getv());
	}

	car0.timeout();
	}

	distance_covered += (float)fabs(car0.getv().y * duration.count());

	for (int i = 0; i < 7; i++)
	{
		road_mid_bands[i].move(car0.getv(), (float)duration.count());
	}

	_house.move(car0.getv(), (float)duration.count());

	if (distance_covered > total_distance)
	{
		car0.c1 = Colors::Magenta;
	}

	if (distance_covered > total_distance * .7)
	{
		if (flag2)
		{
			pos_final = (car0.getp() - vect((float)175 / 2, total_distance*.3f));
			flag2 = false;
		}
		pos_final = (pos_final - car0.getv() * (float)duration.count());
	}



	for(int i = 0; i < 5; i++)
	{
		if(robot_cars[i].getp().y > 630 || robot_cars[i].getp().y < -1500)
		{
			robot_cars[i].initiate(car_pos[i]);
		}
	}
}

void Game::ComposeFrame()
{
	
	gfx.DrawTrack();

	for (int i = 0; i < 7; i++)
	{
		road_mid_bands[i].display(gfx);
	}

	FinishLine();
	
	_house.display(gfx);

	car0.disp_car(gfx);

	for (int i = 0; i < 5; i++)
	{
		robot_cars[i].disp_car(gfx);
	}

	// car showing amount of race completed
	gfx.DrawRect(24, int(-520.0f*(distance_covered / total_distance) + 560)-2, 16, 28, Colors::White);
	gfx.DrawRect(26, int(-520.0f*(distance_covered / total_distance) + 560), 12, 24, Colors::Red);
}
