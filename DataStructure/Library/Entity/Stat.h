#pragma once
#include "Lifespan.h"


//Easily keep track of a stat.
//This struct also holds data for an associated name and color.
//Note: when comparing two stats, it checks the names and colors, not values.
struct Stat
{
	float value;
	string name;
	unsigned color;

	Stat() { value = 0, name = "Defualt", color = clr_WHITE; }
	Stat(float val, string _name) : value(val), name(_name) { color = clr_WHITE; }
	Stat(float val, string _name, unsigned _color) : value(val), name(_name), color(_color) {}

	Stat operator+(float a);
	Stat &operator+=(float a);
	Stat operator-(float a);
	Stat &operator-=(float a);
	Stat operator*(float a);
	Stat &operator*=(float a);
	Stat operator/(float a);
	Stat &operator/=(float a);

	bool operator==(float a);
	bool operator!=(float a);
	bool operator>=(float a);
	bool operator<=(float a);
	bool operator>(float a);
	bool operator<(float a);
	bool operator==(Stat a);
	bool operator!=(Stat a);
};
