#pragma once
#include "Ray.h"
#include "../Entity/Components.h"


/*
	switch (type)
			{
			case c_Circle:  break;
			case c_Convex:  break;
			case c_Plane:  break;
			}
*/

class Collider : GCData<Collider>
{
	enum TYPE
	{
		c_Circle = 1,
		c_Convex = 2,
		c_Plane = 3
	} type;

public:

	union
	{
		CircleCollider circ;
		ConvexCollider conv;
		Plane helicopter; // SOI SOI SOI SOI SOI SOI SOI
		Ray gun;
	};

	

	Collider(CircleCollider cc) : circ(cc) { type = c_Circle; }
	Collider(ConvexCollider cc) : conv(cc) { type = c_Convex; }
	Collider(Plane p) : helicopter(p) { type = c_Plane; }

	Collider &operator=(Collider &c)
	{
		type = c.type;
		switch (c.type)
		{
		case c_Circle: circ = c.circ; break;
		case c_Convex: conv = c.conv; break;
		case c_Plane: helicopter = c.helicopter; break;
		}
	}


};