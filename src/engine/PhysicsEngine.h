#ifndef __PHYSICS_ENGINE_H__
#define __PHYSICS_ENGINE_H__

#include <vector>
#include <memory>
#include <iostream>

#include "GameMath.h"

static const float DEFAULT_GRAVITY = -1.0f;

class PhysicsObject;

class PhysicsEngine {
	friend class XCube2Engine;
	friend class PhysicsObject;
	private:
		Vector2f gravity;
		PhysicsEngine();

		std::vector<std::shared_ptr<PhysicsObject>> objects;

	public:
		/**
		* Note that gravity is naturally a negative value
		* update interval in seconds
		*/
		void setGravity(float gravityValue, float worldUpdateInterval);
		void update();

		void registerObject(std::shared_ptr<PhysicsObject>);
};

class PhysicsObject {
	friend class PhysicsEngine;
	protected:
		Point2 center;
		float lX, lY, hlX, hlY;	// lengths and half lengths
		Rect boxCol;

		bool useGravity;

		Vector2f force;

		
	public:
		PhysicsObject(const Point2 & center, float x, float y, bool gravity);
		PhysicsObject(Rect box, bool gravity);

		void applyForce(const Vector2f&);

		Point2 getCenter() { return center; }
		Rect getBoxCol() { return boxCol; }
		float getLengthX() { return lX; }
		float getLengthY() { return lY; }
		float getHalfLengthX() { return hlX; }
		float getHalfLengthY() { return hlY; }
		bool getGravity() { return useGravity; }
		Vector2f getForce() { return force; }

		bool isColliding(const PhysicsObject & other);

		void setBoxCol(Rect col) { boxCol = col; }

		/**
		* If we have different implementations of engines/gravity
		* this can be very useful
		*/
		virtual void applyGravity(const PhysicsEngine & engine);
		virtual void applyAntiGravity(const PhysicsEngine & engine);

		// Calculates objects next position baseon on current force
		void nextPosition();
};

#endif