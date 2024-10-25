#include "PhysicsEngine.h"

/*PhysicsObject::PhysicsObject(const Point2& center, float x, float y, bool gravity)
	: center(center), lX(x), lY(y), hlX(x / 2.0f), hlY(y / 2.0f), force(0.0f, 0.0f), useGravity(gravity) {}*/



PhysicsObject::PhysicsObject(Rect boxCol, bool gravity)
	: center(boxCol.w / 2, boxCol.h / 2), boxCol(boxCol), lX(boxCol.w), lY(boxCol.h), hlX(boxCol.w / 2.0f), hlY(boxCol.h / 2.0f), force(0.0f, 0.0f), useGravity(gravity) {}
	

bool PhysicsObject::isColliding(const PhysicsObject & other) {
    Rectf r1 = { center.x - hlX, center.y - hlY, lX, lY };
    Rectf r2 = { other.center.x - other.hlX, other.center.y - other.hlY, other.lX, other.lY };

	return r1.intersects(r2);
}



void PhysicsObject::applyForce(const Vector2f & v) {
	force = v;
}

void PhysicsObject::nextPosition() {
	if (force.x != 0 || force.y != 0) {
		this->boxCol.x += force.x;
		this->boxCol.y += force.y;
	}
}

void PhysicsObject::applyGravity(const PhysicsEngine & engine) {
	if (useGravity) center += engine.gravity;
}

void PhysicsObject::applyAntiGravity(const PhysicsEngine & engine) {
	center -= engine.gravity;
}

/* PHYSICS ENGINE */

PhysicsEngine::PhysicsEngine() : gravity(Vector2f(0, DEFAULT_GRAVITY)) {}

void PhysicsEngine::setGravity(float val, float interval) {
	gravity = Vector2f(0, val * interval);
}

void PhysicsEngine::registerObject(std::shared_ptr<PhysicsObject> obj) {
	objects.push_back(obj);
}

void PhysicsEngine::update() {

}