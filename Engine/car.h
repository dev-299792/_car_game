#pragma once

#include"Graphics.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vect.h"
#include <chrono>

class car
{
private:
	vect pos;               //position
	vect v;                 //velocity
	vect a;					//acceleration
	float density;          
	float static_f_coeff;	//friction coefficient
	float rolling_f_coeff;
	float cd;               //drag coefficient
	float area;             //frontal area of car
	float dt;              //time between two frame 
	float mass;
	float g;				//acceleration due to gravity
	float theta;
	int car_width;
	int car_height;
	vect f_a;
	vect d_a;
	bool crash=false;
	std::chrono::steady_clock::time_point crash_time;
	float vy_max;
public:
	Color c1;
public:
	car();
	car(vect v1);
	void move_car();
	void move_relative(vect v1);
	void disp_car(Graphics& gfx);
	void accelerate();
	void deaccelerate();
	void friction();
	void drag();
	void set_dt(std::chrono::duration<double> duration);
	void move_left(float x);
	void move_right(float x);
	bool on_boundry();
	void out_of_boundry();
	void restart();
	vect getv();
	void collision(vect p);
	bool crashed();
	void timeout();
	vect getp();
	void initiate(vect pos);
};
