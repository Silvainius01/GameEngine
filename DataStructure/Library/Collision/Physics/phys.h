#pragma once
#include "../Collider.h"
#include "../../Entity/Entity.h"


//Yes, I made way more functions than neccesary. This is simply for ease of use.
//Only three or four functions actually have calcuations.

extern CollisionData getData(CircleCollider &a, CircleCollider &b);
extern CollisionData getData(CircleCollider &a, ConvexCollider &b);
extern CollisionData getData(CircleCollider &a, Plane &b);

extern CollisionData getData(ConvexCollider &a, CircleCollider &b);
extern CollisionData getData(ConvexCollider &a, ConvexCollider &b);
extern CollisionData getData(ConvexCollider &a, Plane &b);

extern CollisionData getData(Plane &a, CircleCollider &b);
extern CollisionData getData(Plane &a, ConvexCollider &b);
extern CollisionData getData(Plane &a, Plane &b);

//Transfer momentum from one object to another 
void transMome(Entity &a, Entity &b);
//Bounces an entity off another
void bounce(Entity &a, Entity &b);


