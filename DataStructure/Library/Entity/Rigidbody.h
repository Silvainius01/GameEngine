#pragma once
#include "Transform.h"

class Rigidbody
{
protected:
	Transform *p;
	Vec2 velocity = { 0.0f, 0.0f };
	Vec2 drag;
	float mass;
	bool gravity;
public:
	Rigidbody(Transform &parent, float MASS, bool useGravity);
	Rigidbody(Transform &parent, float MASS, Vec2 DRAG, bool useGravity);
	Rigidbody(Transform &parent, float MASS, float DRAG, bool useGravity);

	//Return the mass of this RB
	float getMass();
	//Returns the (X, Y) velocity of this RB
	Vec2 getAxelVelocity();
	//Returns the total velocity of this RB
	float getVelocity();
	//Returns the (X, Y) drag of this RB
	Vec2 getAxelDrag();
	//Returns the total drag on this RB
	//NOTE: this is only useful for omnidirectional drag.
	float getDrag();
	//Is this Rigidbody using gravity?
	bool isUsingGravity();

	//Set the mass of this RB.
	//Mass affects how much force is needed to accelrate an object.
	void setMass(float m);
	//Set the total velocity of the object in the given direction
	void setVelocity(float v, float angle);
	//Manually set the velocity across both axies.
	void setVelocity(Vec2 v);
	//Set the drag this object experiences.
	//This will be applied omnidirectionally.
	void setDrag(float d);
	//Manually set the drag for both axies
	void setDrag(Vec2 d);
	//Set whether this RB is using gravity
	void useGravity(bool g);
	//update the rigidbody
	void update();
};