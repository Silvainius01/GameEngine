#include "Ray.h"

#include "../../Rendering/sfwdraw.h"
using namespace sfw;
unsigned colour = clr_WHITE;

void drawVictor(const Vec2 &a, const Vec2 &b)
{
	drawLine(a.x, a.y, b.x, b.y, colour);
}


CircleCollider::CircleCollider(Transform &parent, float radius) { p = &parent, rad = radius; }
Transform* CircleCollider::getParent() { return p; }
Vec2 CircleCollider::getClosestPointTo(Transform *t)
{
	return getClosestPointTo(t->getPosition());
}
Vec2 CircleCollider::getClosestPointTo(Transform &t)
{
	return getClosestPointTo(t.getPosition());
}
Vec2 CircleCollider::getClosestPointTo(Vec2 &v2)
{
	float angle = (getParent()->getPosition().getAngleBetween(v2)) * DEG2RAD;
	if (isnan(angle)) { return v2; }
	return getParent()->getPosition() - (Vec2{ cos(angle), sin(angle) } *getRadius());
}
float CircleCollider::getRadius() { return rad; }
void CircleCollider::setRadius(float r) { rad = r; }
CollisionData CircleCollider::collided(CircleCollider &c)
{
	Vec2 blerg = getClosestPointTo(c.getParent());

	if (getParent()->getPosition().getDistBetween(blerg) <= c.getRadius())
	{
		return CollisionData{ true, blerg.getDistBetween(c.getClosestPointTo(blerg)), (getParent()->getPosition() - c.getParent()->getPosition()).getNormal() };
	}
	return CD_NoCollide;
}
CollisionData CircleCollider::collided(ConvexCollider &c)
{
	return c.collided(*this);
}
CollisionData CircleCollider::collided(Plane &pl)
{
	//Mx = Nx + c
	// c / (M - N) = x

	Vec2 test;
	float step = getParent()->getPosition().y + getRadius();
	float result = getParent()->getPosition().y - getRadius();
	float save = -1;

	if (step < pl.getEndPoint().y && step < pl.getStartPoint().y)
		return CD_NoCollide;
	else if (result > pl.getStartPoint().y && result > pl.getEndPoint().y)
		return CD_NoCollide;

	step = (2 * PI) / 24;
	result = -1;
	
	//The point on the plane with the same X as the circle
	float pwsx = pl.getSlope() * (getParent()->getPosition().x);


	//find the deepest point of penetration ... giggity.
	if (pwsx < 0)
	{
		for (int a = 0; a < 24; a++)
		{
			test = Vec2{ cos(a * step), sin(a * step) } + getParent()->getPosition();
			result = pl.getSlope() * test.x;
			if (test.y > result) { continue; }
			result = abs(test.y - result);
			if (result > save) { save = result; }
		}
	}
	else
	{
		for(int a = 0; a < 24; a++)
		{
			test = Vec2{ cos(a * step), sin(a * step) } +getParent()->getPosition();
			result = pl.getSlope() * test.x;
			if (test.y < result) { continue; }
			result = abs(test.y - result);
			if (result < save) { save = result; }
			else { a = 24; }
		}
	}
	float sirSlope = (test.y - getParent()->getPosition().y) / (test.x - getParent()->getPosition().x);
	result = save / (sirSlope - pl.getSlope());
	return CollisionData{ true, result, (getParent()->getPosition() - pl.getParent()->getPosition()) };
}

ConvexCollider::ConvexCollider(Transform &parent) { p = &parent; }
ConvexCollider::ConvexCollider(Transform &parent, int verticies, float distanceToVert)
{
	p = &parent;
	this->makeRegularPolygon(distanceToVert, verticies);
}
Vec2 ConvexCollider::getLeftVertOf(int vert)
{
	if (vert <= 0) { return vertex[vertexCount - 1]; }
	else if (vert >= vertexCount)
	{
		if (vertexCount <= 1) { return vertex[0]; }
		return vertex[vertexCount - 2]; 
	}
	return vertex[vert - 1];
}
Vec2 ConvexCollider::getRightVertOf(int vert)
{
	if (vert < 0) { return vertex[1]; }
	else if (vert >= vertexCount - 1) { return vertex[0]; }
	return vertex[vert + 1];
}
void ConvexCollider::makeRegularPolygon(float distToVert, int vertices)
{
	float ver = (2 * PI) / vertices;
	for (int a = 0; a < vertices; a++)
	{
		vertex[a] = Vec2{ distToVert * cos(a * ver), distToVert * sin(a * ver) };
		vertex[a] *= p->getTransMatrix();
	}
	vertexCount = vertices;
	dtv = distToVert;
	update();
}
void ConvexCollider::makeRegularPolygon(int vertices, float sideLength)
{
	float scaler;
	if (vertices % 2 == 0) { scaler = 0.309015f; }
	else { scaler = 0.32416f; }

	makeRegularPolygon(scaler * (int)(vertices / 2), vertices);
}
void ConvexCollider::setVertex(int v, Vec2 pos)
{
	if (v > 9) { v = 9; }		else if (v < 0) { v = 0; }
	vertex[v] = p->getPosition() + pos;
	if (v + 1 > vertexCount) { vertexCount = v + 1; }
}
void ConvexCollider::print()
{
	cout << "Position: ";
	p->getPosition().print();
	cout << endl;
	for (int a = 0; a < vertexCount; a++)
	{
		cout << "Vertex " << a << ": ";
		vertex[a].print();
		cout << endl;
	}
}
void ConvexCollider::update()
{
	float ver = (2 * PI) / vertexCount;
	for (int a = 0; a < vertexCount; a++)
	{
		vertex[a] = Vec2{ dtv * cos(a * ver), dtv * sin(a * ver) };
		vertex[a] *= p->getTransMatrix();
	}
}
CollisionData ConvexCollider::collided(CircleCollider &c)
{
	Vec2 blerg = c.getClosestPointTo(p->getPosition()), aa, bb, cc, dd;
	int cv, scv;
	float test, sc = (cml::abs(vertex[0] - blerg) + Vec2{ 1, 1 }).getMag();

	//Find the closest vertex to blerg.
	for (int a = 0; a < vertexCount; a++)
	{
		Vec2 blerg2 = cml::abs(vertex[a] - blerg);
		if (blerg2 < sc) { cv = a, sc = blerg2.getMag(); }
	}

	//Find the second closest vertex to blerg
	if (cv != 0) { sc = (cml::abs(vertex[0] - blerg) + Vec2{ 1, 1 }).getMag(); }
	else { sc = (cml::abs(vertex[1] - blerg) + Vec2{ 1, 1 }).getMag(); }
	for (int a = 0; a < vertexCount; a++)
	{
		if (a == cv) { continue; }
		Vec2 blerg2 = cml::abs(vertex[a] - blerg);
		if (blerg2 < sc) { scv = a, sc = blerg2.getMag(); }
	}

	//We pretend "vertex[scv]" is the origin
	aa = vertex[cv] - vertex[scv];
	bb = blerg - vertex[scv];
	cc = p->getPosition() - vertex[scv];
	dd = c.getParent()->getPosition() - vertex[scv];

	/****************************************************************************\
	 *	Using our pretend origin, the line between "cv" and "scv" is just		*
	 *	"y = mx". This makes the relationship between the closest point on		*
	 *	the circle and the circle's transform "y = nx + c."						*
	 *		To check collision, we only need to check orientation. For depth,	*
	 *	it's more tricky. If the two coilliders... collide, then we know the	*
	 *	two	relationships above intersect, and thus have a shared Vec2. As		*
	 *	such, since we made "vertex[scv]" our origin, we know this shared point *
	 *  is:																		*
	 *																			*
	 *		y = mx = nx + c		which reduces to	mx = nx + c					*
	 *																			*
	 *	Since both equations will give us the same y with the right	x, we only  *
	 *	need to find that x. With a bit of algerbra, we find that:				*
	 *																			*
	 *		x = c / (m - n)														*
	 *																			*
	 *	To finish this off, we need to find c, which is super simple.			*
	 *																			*
	 *		c = (vertex[scv].x * n) - vertex[scv].y								*
	\****************************************************************************/
	test = aa.y / aa.x;
	sc = (bb.y - dd.y) / (bb.x - dd.x);

	float C = (vertex[scv].x * sc) - vertex[scv].y;
	float depth = blerg.getDistBetween(Vec2{ C / (test - sc), (C / (test - sc)) * test });

	if (test * cc.x > cc.y) { if (test * bb.x > bb.y) { return CollisionData{ true, C, Vec2{ 0,0 } };; } }
	else if (test * bb.x < bb.y) { return CollisionData{ true, C, Vec2{0,0} }; }
	return CD_NoCollide;
}
CollisionData ConvexCollider::collided(ConvexCollider &c)
{
	Vec2 aa, bb;
	int cv, sv, sv2;
	float test;
	float sc = p->getPosition().getDistBetween(c.vertex[0]) + 1;

	//Find closest vertex on c
	for (int a = 0; a < c.vertexCount; a++)
	{
		test = p->getPosition().getDistBetween(c.vertex[a]);
		if (test < sc) { sc = test, cv = a; }
	}

	//Find the closest to cv on this
	sc = vertex[0].getDistBetween(c.vertex[cv]) + 1;
	for (int a = 0; a < vertexCount; a++)
	{
		test = vertex[a].getDistBetween(c.vertex[cv]);
		if (test < sc) { sc = test, sv = a; }
	}

	//find the second closest vertex to c on this
	if (sv == 0) { sc = vertex[1].getDistBetween(c.vertex[cv]) + 1; }
	else { sc = vertex[0].getDistBetween(c.vertex[cv]) + 1; }
	for (int a = 0; a < vertexCount; a++)
	{
		if (a == sv) { continue; }
		float test = vertex[a].getDistBetween(c.vertex[cv]);
		if (test < sc) { sc = test, sv2 = a; }
	}

	aa = vertex[sv] - vertex[sv2]; test = (aa.y / aa.x);
	aa = c.vertex[cv] - vertex[sv2];
	bb = p->getPosition() - vertex[sv2];

	
	if (test * bb.x > bb.y) { if (test * aa.x > aa.y) { return CD_NoCollide; } }
	else if (test * aa.x < aa.y) { return CD_NoCollide; }

	if (c.sent) { c.sent = false; return CD_NoCollide; } //false
	else { sent = true; return c.collided(*this); }
}
CollisionData ConvexCollider::collided(Plane &pl)
{
	Vec2 aa, bb, cc;
	int cv, scv;
	float sc, test;
	bool nextLow = false, nextHigh = false;

	//find closest vertex to plane
	for (int a = 0; a < vertexCount; a++)
	{
		if (abs(vertex[a].x - pl.getStartPoint().x) < abs(pl.getStartPoint().x - pl.getEndPoint().x))
		{
			test = vertex[a].y * pl.getSlope();

			if (nextLow) { if (test > vertex[a].y) { return CD_NoCollide; } }
			else if (nextHigh) { if (test < vertex[a].y) { return CD_NoCollide; } }
			else if (test < vertex[a].y) { nextLow = true; }
			else if (test > vertex[a].y) { nextHigh = true; }
		}
	}

	/*test = pl.getSlope();
	aa = vertex[cv] - pl.getEndPoint();*/
	return CD_NoCollide; //false
}

Plane::Plane(Transform &parent, Vec2 start, Vec2 end)
{
	p = &parent;
	vertex[0] = start * p->getTransMatrix();
	vertex[1] = end * p->getTransMatrix();
	slope = (vertex[1].y - vertex[0].y) / (vertex[1].x - vertex[0].x);
}
Vec2 Plane::getStartPoint() { return vertex[0]; }
Vec2 Plane::getEndPoint() { return vertex[1]; }
float Plane::getAngularSlope() { return (vertex[1] - vertex[0]).getAngle(); }
float Plane::getSlope() { return slope; }
void Plane::print()
{
	cout << "Start Point: "; vertex[0].print(); cout << endl;
	cout << "End   Point: "; vertex[1].print(); cout << endl;
	cout << "Slope: " << slope << " Anglular: " << getAngularSlope();
}
void Plane::reset()
{
	vertex[0] *= p->getTransMatrix().getInverse();
	vertex[1] *= p->getTransMatrix().getInverse();
}
void Plane::update()
{
	vertex[0] *= p->getTransMatrix();
	vertex[1] *= p->getTransMatrix();
	slope = (vertex[1].y - vertex[0].y) / (vertex[1].x - vertex[0].x);
}
void Plane::setStartPoint(Vec2 location)
{
	vertex[0] = location * p->getTransMatrix();
	slope = (vertex[1].y - vertex[0].y) / (vertex[1].x - vertex[0].x);
}
void Plane::setEndPoint(Vec2 location)
{
	vertex[1] = location * p->getTransMatrix();
	slope = (vertex[1].y - vertex[0].y) / (vertex[1].x - vertex[0].x);
}
void Plane::setAngularSlope(float angle)
{
	float length = vertex[0].getDistBetween(vertex[1]);
	vertex[1] = (Vec2{ cos(angle), sin(angle) } * length) + vertex[0];
}
CollisionData Plane::collided(CircleCollider &c)
{
	return c.collided(*this);
}
CollisionData Plane::collided(ConvexCollider &cc)
{
	return cc.collided(*this);
}
CollisionData Plane::collided(Plane &p)
{
	if (abs(p.vertex[0].x - vertex[0].x) < abs(p.vertex[0].x - p.vertex[1].x))
	{
		float test = vertex[0].y * p.getSlope();
		float test2 = vertex[1].y * p.getSlope();
		if (test > vertex[0].y)
		{
			if (test2 < vertex[1].y) { return CD_NoCollide; }
		}
		else if(test < vertex[0].y)
		{
			if (test2 > vertex[1].y) { return CD_NoCollide; }
		}
		else if (test2 == vertex[1].y) { return CD_NoCollide; }
		else { return CD_NoCollide; }
	}
	return CD_NoCollide; //false
}
