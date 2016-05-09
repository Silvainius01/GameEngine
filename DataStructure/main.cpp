#include <iostream>
#include "Library/Collision/Collider.h"
#include "Library\Entity\Sprite.h"
#include "./Rendering/sfwdraw.h"
#include "./Rendering/ui.h"
#include "./Rendering/input.h"
#include "./Library/Collision/Collider.h"
#include "./Library/Entity/Components.h"
#include "./Library/Entity/Entity.h"
using namespace sfw;
using namespace std;
using namespace cml;

#define PRINT cout <<
#define _ << ", " <<
#define NL << endl
#define PNL cout << endl
#define STOP system("pause")

unsigned color = clr_WHITE;

void drawVector(const Vec2 &a, const Vec2 &b)
{
	drawLine(a.x, a.y, b.x, b.y, color);
}
void drawVector(const Vec2 &a)
{
	drawLine(0, 0, a.x, a.y);
}

void drawCollider(ConvexCollider &cc)
{
	for (int a = 1; a < cc.vertexCount; a++)
	{
		drawVector(cc.vertex[a], cc.vertex[a - 1]);
	}
	drawVector(cc.vertex[cc.vertexCount - 1], cc.vertex[0]);
	drawVector(cc.getParent()->getPosition(), cc.vertex[0]);
}
void drawCollider(CircleCollider &c)
{
	Vec2 blerg = c.getParent()->getPosition();
	drawCircle(blerg.x, blerg.y, c.getRadius(), 15, color);
}

void drawTransform(Transform &t, float height, float width)
{
	drawChar('X', t.getPosition().x - (width / 2), t.getPosition().y - (height / 2), height, width);
}

Transform p = Transform(Vec2{ 250, 250 }, Vec2{ 1, 1 }, 0.0f);
Transform c = Transform(Vec2{ 250, 250 }, Vec2{ 1, 1 }, 0.0f);

ConvexCollider pent = ConvexCollider(p, 5, 30.0f);
CircleCollider circ = CircleCollider(c, 15.0f);

void rotate()
{
	pent.getParent()->rotate(5.0f * getDeltaTime());
	pent.update();

	color = clr_RED;
	drawCollider(pent);
}
void autoCol()
{
	for (float x = 200; x < 300; x++)
	{
		for (float y = 200; y < 300; y++)
		{
			circ.getParent()->setPosition(Vec2{ x, y });
			if (pent.collided(circ).collided)
			{
				color = clr_WHITE;
				drawVector(Vec2{ x, y }, Vec2{ x - 1, y - 1 });
			}
		}
	}

	color = clr_RED;
	drawCollider(pent);
}
void manCol()
{
	circ.getParent()->setPosition(Vec2{ getMouseX(), getMouseY() });

	color = clr_MAGENTA;
	drawCollider(circ);
	color = clr_CYAN;
	drawCollider(pent);

	CollisionData blerg = pent.collided(circ);

	if (blerg.collided)
	{
		color = clr_GREEN;
		cout << blerg.depth << endl;
	}
	else { color = clr_RED; }


	drawVector(circ.getClosestPointTo(pent.getParent()), circ.getParent()->getPosition());
}


void main()
{
	

	color = clr_WHITE;

	initContext(500, 500, "Testing");

	while (stepContext())
	{
		autoCol();
	}
}