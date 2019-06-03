#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "car.h"
#include "bands.h"
#include <chrono>
#include "house.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
	void FinishLine();
private:
	void ComposeFrame();
	void UpdateModel();

	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	std::chrono::steady_clock::time_point now, prev;
	std::chrono::duration<double> duration;
	/********************************/
	/*  User Variables              */
	car car0;
	car robot_cars[5];

	vect car_pos[5] = { vect(230,-500),vect(200,-100), vect(290,-1200), vect(330,-900), vect(400,-300) };

	bands road_mid_bands[7];
	house _house;
	bool flag2 = true;
	float total_distance=10000;
	float distance_covered = 0;
	vect pos_final;

	/********************************/
};
