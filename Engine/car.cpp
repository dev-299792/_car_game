#include "car.h"



car::car()
{

	pos = vect(297, Graphics::ScreenHeight * .80);
	v = vect(1.0, 0.0);						//	m/s
	a = vect(100.0, .0);					//	m/s^2
	density = 1.295;						//	kg/m^3
	area = 2;								//	m^2
	static_f_coeff = 3.28;
	rolling_f_coeff = 0.05;
	mass = 1200;							//	kg
	cd = 5;
	g = 9.8;								//	m/s^2
	theta = M_PI_2;							//	radians
	v.set_angle(theta);
	a.set_angle(theta);
	d_a = vect(cd*area*.5f*v.mag_squared() / mass, .0f);
	f_a = vect(rolling_f_coeff*g, 0);
	d_a.set_angle(theta);
	f_a.set_angle(theta);
	car_width = 25;
	car_height = 50;
	c1 = Colors::Red;
	vy_max = 500;
}


car::car(vect v1)
{


	pos = vect(100,100);
	v = v1;						//	m/s
	a = vect(.0, .0);						//	m/s^2
	density = 1.295;						//	kg/m^3
	area = 2;								//	m^2
	static_f_coeff = 3.28;
	rolling_f_coeff = 0.15;
	mass = 1200;							//	kg
	cd = 50;
	g = 9.8;								//	m/s^2
	theta = M_PI_2;							//	radians
	v.set_angle(theta);
	a.set_angle(theta);
	d_a = vect(cd*area*.5f*v.mag_squared() / mass, .0f);
	f_a = vect(rolling_f_coeff*g, 0);
	d_a.set_angle(theta);
	f_a.set_angle(theta);
	car_width = 25;
	car_height = 50;
	c1 = Colors::Cyan;
}
void car::move_car()
{
	pos = pos + v * (dt);

	if (pos.y > Graphics::ScreenHeight - 20)
		pos.y = 20;
	else if (pos.y < 20)
	{
		pos.y = Graphics::ScreenHeight - 20;
	}
}

void car::move_relative(vect v1)
{
	pos = pos + (v-v1) * (dt);

	/*if (pos.y > Graphics::ScreenHeight - 20)
		pos.y = 20;
	else if (pos.y < 20)
	{
		pos.y = Graphics::ScreenHeight - 20;
	}*/
}



void car::disp_car(Graphics& gfx)
{
	if (pos.y>-30&&pos.y<600-car_height/2)
	{
		Color c2 = Colors::Black;
		if (crash)
		{
			gfx.DrawRect((int)150 - car_width / 2, (int)500 - car_height / 2, car_width, car_height, c1); //main rect big
			gfx.DrawRect((int)150 - car_width / 3, (int)500 - car_height / 3, 2 * car_width / 3, car_height / 5, c2);
		}
		else
		{
			gfx.DrawRect((int)pos.x - car_width / 2, (int)pos.y - car_height / 2, car_width, car_height, c1); //main rect big
			gfx.DrawRect((int)pos.x - car_width / 3, (int)pos.y - car_height / 3, 2 * car_width / 3, car_height / 5, c2);
		}
	}
}

void car::accelerate()
{
	a.set_angle(theta);
	v = v + a * dt;
	if (v.y > vy_max)
	{
		v.y = vy_max;
	}
}

void car::deaccelerate()
{
	a.set_angle(theta);
	if (v.magnitude() > a.magnitude()*dt)
		v = v - a * dt;
	else
		v = vect(0, 0);
}

void car::friction()
{
	f_a = vect(rolling_f_coeff*g, 0);
	f_a.set_angle(theta);
	if (v.magnitude() > f_a.magnitude()*dt)
		v = v - f_a * dt;
	else
		v = vect(0, 0);
}

void car::drag()
{
	d_a = vect(cd*area*.5f*v.mag_squared() / mass, .0f);
	d_a.set_angle(theta);
	if (v.magnitude() > d_a.magnitude()*dt)
		v = v - d_a * dt;
	else
		v = vect(0, 0);
}

void car::set_dt(std::chrono::duration<double> duration)
{
	dt = (float)duration.count();
}

void car::move_left(float x)
{
	pos.x -= x;
}

void car::move_right(float x)
{
	pos.x += x;
}

bool car::on_boundry()
{

	return (pos.x<(175 + car_width / 2) || pos.x>(175 + 245 - 5 - car_width / 2));
}


void car::out_of_boundry()
{
	if ((pos.x < (175 - 5 + car_width / 2)) || (pos.x > (175 + 245 - car_width / 2)))
	{
		crash = true;
		crash_time = std::chrono::steady_clock::now();
		v = vect(0, 0);
	}
}

void car::restart()
{
	pos = vect(297, Graphics::ScreenHeight * .80);
	v = vect(1.0, 0.0);						//	m/s
	a = vect(100.0, .0);						//	m/s^2
	v.set_angle(theta);
	a.set_angle(theta);
	d_a = vect(cd*area*.5f*v.mag_squared() / mass, .0f);
	f_a = vect(rolling_f_coeff*g, 0);
	d_a.set_angle(theta);
	f_a.set_angle(theta);
	crash = false;
}

vect car::getv()
{
	return v;
}

void car::collision(vect p)
{
	if (fabs(pos.x - p.x) < car_width && fabs(pos.y - p.y) < car_height)
	{
		crash = true;
		crash_time = std::chrono::steady_clock::now();
		v = vect(0, 0);
	}
}

bool car::crashed()
{
	return crash;
}

void car::timeout()
{
	std::chrono::steady_clock::duration d = std::chrono::steady_clock::now() - crash_time;
	if (d.count() > 3 * pow(10, 9))
		restart();
}

vect car::getp()
{
	return pos;
}

void car::initiate(vect p)
{
	
	pos = p;
	v = vect(.0f, -70.0f);					//	m/s
	a = vect(.0, .0);						//	m/s^2
	//v.set_angle(theta);
	//a.set_angle(theta);
	d_a = vect(.0f, .0f);
	f_a = vect(.0f, 0);
	//d_a.set_angle(theta);
	//f_a.set_angle(theta);
	car_width = 25;
	car_height = 50;
	c1 = Colors::Cyan;
}




