#pragma once
#include "Plane.h"

class Ray
{
protected:
	Vec2 vertex[2];
	float slope;
	
public:
	Ray(Vec2 start, float length, float angle);
	Ray(Transform &start, Transform &target, float length);

	float getPenetrationDepth();

	auto getIntersectedObject();
};