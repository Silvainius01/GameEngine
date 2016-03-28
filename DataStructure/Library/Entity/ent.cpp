#include "./Entity.h"

Transform::Transform(void) : parent(nullptr)
{
	position = Vec2{ 0, 0 };
	scale = Vec2{ 1, 1 };
	rotation = 0.0f;
	updateTrans();
}
Transform::Transform(Vec2 pos, Vec2 scl, float rot) : parent(nullptr)
{
	position = pos;
	scale = scl;
	rotation = rot;
	updateTrans();
}
Transform::Transform( Transform &p, Vec2 pos, Vec2 scl)
{
	*parent =* p.parent;
	trans = *parent;
	position = pos + (Vec2{ 1, 1 } * p.trans);
	//scale = (scl * p.scale);
}
void Transform::updateTrans()
{
	if (parent != nullptr) { trans = *parent; }
	else { trans = Matrix3(); }

	
	{
		Matrix3 scl;
		scl.data[0][0] = scale.y;
		scl.data[1][1] = scale.x;
		trans *= scl;
	}

	{
		Matrix3 rot;
		float rad = rotation * DEG2RAD;
		rot.setRow(0, Vec3{ cos(rad), -sin(rad), 0 });
		rot.setRow(1, Vec3{ sin(rad),  cos(rad), 0 });
		trans *= rot;
		//cout << "Rot Dif:\n"; rot.print(); cout << endl;
	}

	{
		Matrix3 pos;
		pos.data[2][0] = position.x;
		pos.data[2][1] = position.y;
		trans *= pos;
	}
}
Matrix3		*Transform::getParent() { return parent; }
Matrix3		 Transform::getTransMatrix() { return trans; }
Vec2		 Transform::getPosition() { return position; }
Vec2		 Transform::getScale() { return scale; }
Vec2 Transform::getRotationVector()
{
	Matrix3 rot; 
	rot.setRow(0, Vec3{ trans.data[0][0], trans.data[1][0], rot.data[2][0] });
	rot.setRow(1, Vec3{ trans.data[0][1], trans.data[1][1], rot.data[2][1] });
	return Vec2{ 1 , 1 } * rot;
}
float Transform::getRotationDegrees() { return rotation; }
float Transform::getDist(Transform *t)
{
	Vec2 dist = t->position - this->position;
	return dist.getMag();
}
void		 Transform::setParent(const Transform &p) { *parent = p.trans; }
void		 Transform::rotate(float degrees)
{
	rotation += degrees;
	if (rotation >= 180.0f) { rotation -= 360.0f; }
	else if (rotation <= -180.0f) { rotation += 360.0f; }
	updateTrans();
}
void		 Transform::move(Vec2 dist) 
{
	position += dist; updateTrans();
}
void		Transform::setPosition(Vec2 pos)
{ 
	position = pos; updateTrans();
}
void		 Transform::scaleBy(Vec2 scl) 
{
	scale += scl; updateTrans();
}
Transform	&Transform::operator=( Transform &t)
{
	*parent = *t.parent;
	trans = t.trans;
	scale = t.scale;
	position = t.position;
	return *this;
}
Transform *Transform::operator=( Transform *t)
{
	parent = t->parent;
	trans = t->trans;
	scale = t->scale;
	position = t->position;
	return this;
}

Rigidbody::Rigidbody(Transform &parent, float MASS, bool grav)
{
	p = &parent;
	mass = MASS;
	gravity = grav;
	drag = Vec2{ 0 , 0 };
}
Rigidbody::Rigidbody(Transform &parent, float MASS, Vec2 DRAG, bool grav)
{
	p = &parent;
	mass = MASS;
	gravity = grav;
	drag = DRAG;
}
Rigidbody::Rigidbody(Transform &parent, float MASS, float DRAG, bool grav)
{
	p = &parent;
	mass = MASS;
	gravity = grav;
	drag = Vec2{ DRAG, DRAG };
}
float	Rigidbody::getMass() { return mass; }
Vec2	Rigidbody::getAxelVelocity() { return velocity; }
float	Rigidbody::getVelocity() { return velocity.getMag(); }
Vec2	Rigidbody::getAxelDrag() { return drag; }
float	Rigidbody::getDrag() { return drag.getMag(); }
bool Rigidbody::isUsingGravity() { return gravity; }
void	Rigidbody::setMass(float m) { mass = m; }
void	Rigidbody::setVelocity(float v, float angle) { velocity = Vec2{ cos(angle) / v, sin(angle) / v }; }
void	Rigidbody::setVelocity(Vec2 v) { velocity = Vec2{ v.x, v.y }; }
void	Rigidbody::setDrag(float d) { drag = Vec2{ d, d }; }
void	Rigidbody::setDrag(Vec2 d) { drag = Vec2{ d.x, d.y }; }
void Rigidbody::useGravity(bool g) { gravity = g; }
void Rigidbody::update()
{
	if (velocity.x > 0.0001f) { velocity[0] -= drag.x * getDeltaTime(); }
	else if (velocity.x < -0.0001f) {velocity.x += drag.x * getDeltaTime(); }
	else { velocity[0] = 0.000f; }
	if (velocity.y > 0.0001f) { velocity[1] -= drag.y * getDeltaTime(); }
	else if (velocity.y < -0.0001f) { velocity.y += drag.y * getDeltaTime(); }
	else { velocity[1] = 0.000f; }
	if (gravity)
	{
		float termVel = 50.0f;
		termVel += mass / 10;
		termVel -= drag.y;
		if (velocity.y > termVel) { velocity[1] -= GRAVITY * getDeltaTime(); }
	}
	if (velocity.x > -0.0001f && velocity.x < 0.0001f) { p->move((velocity * getDeltaTime())); }
	else { p->move((velocity - (mass / 4)) * getDeltaTime()); }
}

Lifespan::Lifespan(float time) { t_Left = time; if (t_Life == 0.0f) { t_Life = time; } }
void Lifespan::setTimeLeft(float time) { t_Left = time; }
void Lifespan::resetLifeTime() { t_Left = t_Life; }
float Lifespan::getTimeLeft() { return t_Left; }
float Lifespan::getOriginalLifespan() { return t_Life; }

Stat Stat::operator+(float a) { return Stat{ value + a, name }; }
Stat &Stat::operator+=(float a) { value += a; return *this; }
Stat Stat::operator-(float a) { return Stat{ value - a, name }; }
Stat &Stat::operator-=(float a) { value -= a; return *this; }
Stat Stat::operator*(float a) { return Stat{ value * a, name }; }
Stat &Stat::operator*=(float a) { value *= a; return *this; }
Stat Stat::operator/(float a) { return Stat{ value / a, name }; }
Stat &Stat::operator/=(float a) { value /= a; return *this; }
bool Stat::operator==(float a) { return value == a; }
bool Stat::operator!=(float a) { return value != a; }
bool Stat::operator>=(float a) { return value >= a; }
bool Stat::operator<=(float a) { return value <= a; }
bool Stat::operator>(float a) { return value > a; }
bool Stat::operator<(float a) { return value < a; }
bool Stat::operator==(Stat a) { if (name == a.name) { return color == a.color; } }
bool Stat::operator!=(Stat a) { if (name != a.name) { return color != a.color; } }