#pragma once
#include "Rigidbody.h"

class Lifespan
{
protected:
	float t_Life = 0.0f;
	float t_Left;
public:
	Lifespan(float time);
	//Set how long this entity has to live
	void setTimeLeft(float time);
	//Reset the Life on this entity to it's orginal lifespan.
	void resetLifeTime();
	void update();
	//Return how much longer this entity will be alive
	float getTimeLeft();
	//Return the original lifespan this entity was given.
	float getOriginalLifespan();
};