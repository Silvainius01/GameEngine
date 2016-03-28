#include "phys.h"

#define aPOS a.getParent()->getPosition()
#define bPOS b.getParent()->getPosition()


 CollisionData getData(CircleCollider &a, CircleCollider &b)
{
	Vec2 blerg;
	{
		float angle = (aPOS.getAngleBetween(bPOS)) * DEG2RAD;
		if (isnan(angle)) { return CollisionData{ true, b.getRadius(),  aPOS - bPOS }; }
		blerg = aPOS - (Vec2{ cos(angle), sin(angle) } *a.getRadius());
	}

	if (a.collided(b).collided)
	{
		return CollisionData{ true, bPOS.getDistBetween(blerg), aPOS - bPOS };
	}
	return CollisionData{ false, bPOS.getDistBetween(blerg), aPOS - bPOS };
}
 CollisionData getData(CircleCollider &a, ConvexCollider &b)
{
	Vec2 blerg;
	{
		float angle = (aPOS.getAngleBetween(bPOS)) * DEG2RAD;
		if (isnan(angle)) { return CollisionData{ true, bPOS.getDistBetween(b.vertex[0]) ,  aPOS - bPOS }; }
		blerg = aPOS - (Vec2{ cos(angle), sin(angle) } *a.getRadius());
	}

	if (a.collided(b).collided)
	{
		return CollisionData{ true, bPOS.getDistBetween(blerg), aPOS - bPOS };
	}
	return CollisionData{ false, bPOS.getDistBetween(blerg), aPOS - bPOS };
}
 CollisionData getData(CircleCollider &a, Plane &b)
{
	Vec2 blerg;
	{
		float angle = (aPOS.getAngleBetween(bPOS)) * DEG2RAD;
		if (isnan(angle)) { return CollisionData{ true, 0.0f ,  aPOS - bPOS }; }
		blerg = aPOS - (Vec2{ cos(angle), sin(angle) } *a.getRadius());
	}

	if (a.collided(b).collided)
	{
		return CollisionData{ true, bPOS.getDistBetween(blerg), aPOS - bPOS };
	}
	return CollisionData{ false, bPOS.getDistBetween(blerg), aPOS - bPOS };
}

 CollisionData getData(ConvexCollider &a, CircleCollider &b)
{
	return getData(b, a);
}
 CollisionData getData(ConvexCollider &a, ConvexCollider &b)
{
	if (a.collided(b).collided)
	{
		for (int A = 0; A < a.vertexCount; A++)
		{

		}
	}

	return CD_NoCollide;
}
 CollisionData getData(ConvexCollider &a, Plane &b)
{
	return CD_NoCollide;
}

 CollisionData getData(Plane &a, CircleCollider &b)
{
	return getData(b, a);
}
 CollisionData getData(Plane &a, ConvexCollider &b)
{
	return getData(b, a);
}
 CollisionData getData(Plane &a, Plane &b)
{
	return CD_NoCollide;
}

//Transfer momentum from one object to another 
 void transMome(Entity &a, Entity &b)
 {

 }
//Bounces an entity off another
 void bounce(Entity &a, Entity &b)
 {

 }