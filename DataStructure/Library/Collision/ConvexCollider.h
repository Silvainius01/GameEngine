#pragma once
#include "CircleCollider.h"

//Note: ConvexColliders holds data for 10 verticies, regardless of how many you use.
//You cannot have more than 10 vertices. 
class ConvexCollider
{
private:
	Transform *p;
	float dtv;
	bool sent = false;
public:
	int vertexCount;
	Vec2 vertex[10];

	ConvexCollider(Transform &parent);
	//Note: by default this constructor makes centered collider.
	ConvexCollider(Transform &parent, int vertices, float distanceToVert);

	//Return the vertex to the left of the passed vertex;
	Vec2 getLeftVertOf(int vert);
	//Return the vertex to the right of the passed vertex;
	Vec2 getRightVertOf(int vert);

	Transform* getParent() { return p; }

	//Make this convex a regular polygon collider
	//Note: this is a centered collider. distToVert is the measure from the transform to any vertex 
	void makeRegularPolygon(float distToVert, int vertices);
	//Make this convex a regular polygon collider
	//Note: this is a centered collider. sideLength is the measure from a vertedx to the next vertex 
	void makeRegularPolygon(int vertices, float sideLength);
	//Manually set a location of a vertex.	void setVertex(int vertex, Vec2 pos);
	void setVertex(int vertex, Vec2 pos);
	//Print the location of all vertices to the console
	void print();
	void update();


	CollisionData collided(CircleCollider &c);
	CollisionData collided(ConvexCollider &c);
	CollisionData collided(Plane &p);
};