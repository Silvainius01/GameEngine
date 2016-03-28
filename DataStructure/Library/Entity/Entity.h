#pragma once
#include "./Sprite.h"
#include "../Collision/Collider.h"
#include "Components.h"

class Entity
{
public:
	Handle<Transform> transform;
	Handle<Rigidbody> rigidbody;
	Handle<Collider> collider;
};