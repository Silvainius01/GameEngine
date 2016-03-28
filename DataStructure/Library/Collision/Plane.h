#pragma once
#include "ConvexCollider.h"

/* 
	Planes are a single line in the game world,
	and prevent other colliders from crossing it.
*/
class Plane
{
protected:
	Transform *p;
	Vec2 vertex[2];
	float slope;

	void reset();
public:
	Plane(Transform &transform, Vec2 start, Vec2 end);

	Transform* getParent() { return p; }
	Vec2 getStartPoint();
	Vec2 getEndPoint();
	//Returns the angular relation between the starting and end point of the plane.
	float getAngularSlope();
	//this returns slope 'm' of the plane ('y = mx + b')
	float getSlope();
	void print();
	void update();
	void setStartPoint(Vec2 location);
	void setEndPoint(Vec2 location);
	//Set a desired angular slope to auto adjust the plane without changing it's length.
	//Note: this treats the plane as a temporary circle, using the start point as the center.
	//Note2: The resulting end point DOES NOT respect the parent transform's rotation!
	void setAngularSlope(float angle);

	CollisionData collided(CircleCollider &c);
	CollisionData collided(ConvexCollider &c);
	CollisionData collided(Plane &p);
};