#include "../Math/TemplateMath.h"
#include "../Math/Matrix4.h"
#include "../Entity/Transform.h"
using namespace cml;

struct CollisionData
{
	bool collided;
	float depth;
	Vec2 normal;
};
#define CD_NoCollide CollisionData{false, -1, Vec2{-1, -1}}

class ConvexCollider;
class Plane;
class Ray;

class CircleCollider
{
private:
	Transform *p;
	float rad;
public:
	CircleCollider(Transform &parent, float radius);

	Transform* getParent();
	//Returns the closest point on the CIRCUMFERENCE
	Vec2 getClosestPointTo(Transform *t);
	//Returns the closest point on the CIRCUMFERENCE
	Vec2 getClosestPointTo(Transform &t);
	//Returns the closest point on the CIRCUMFERENCE
	Vec2 getClosestPointTo(Vec2 &v2);
	float getRadius();

	void setRadius(float r);

	CollisionData collided(CircleCollider &c);
	CollisionData collided(ConvexCollider &c);
	CollisionData collided(Plane &p);
};