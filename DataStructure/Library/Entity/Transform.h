#pragma once
#include "../Math/Matrix3.h"
using namespace cml;

class Transform
{
protected:
	Matrix3 *parent;
	Matrix3 trans;
	Vec2 position;
	Vec2 scale;
	float rotation = 0;
	void updateTrans();
public:

	Transform(void);
	Transform(Transform &p, Vec2 pos = Vec2{ 0, 0 }, Vec2 scale = Vec2{ 1, 1 });
	Transform(Vec2 pos, Vec2 scl, float rot);

	//Returns the parent of this transform;
	Matrix3 *getParent();
	//Returns the transformation matrix of this transform.
	Matrix3 getTransMatrix();
	//Returns the postion of the transform
	Vec2 getPosition();
	//Returns the scale of the transform
	Vec2 getScale();
	Vec2 getRotationVector();
	//Return the rotation of the transform.
	float getRotationDegrees();
	//Return the distance between this transform and another
	float getDist(Transform *t);

	//Sets the parent of this transform
	void setParent(const Transform &p);
	//Rotate the transform by X degrees
	void rotate(float degrees);
	//Move the transform by { x, y } units
	void move(Vec2 dist);
	//Set the transform to be at { x, y }
	void setPosition(Vec2 pos);
	//Scale the size of the transform by { x, y }
	//NOTE: to preserve the same scale on an axis, you must use '1', not '0'
	void scaleBy(Vec2 scale);

	Transform &operator=( Transform &t);
	Transform *operator=( Transform *t);
};