#pragma once

#include "Component.h"
#include "AEEngine.h"

enum class COLLISIONTAG
{
	PLAYER = 0, 
	BULLET = 1,
	ENEMY = 2,
	PLANET = 3,
	NONE = 4
};

class cRigidBody:public Component
{
public:
	float _mass;
	float _velocity;                          // Velocity Value of the ship
	float _velocityCap;                       // Max velocity Value of the ship
	float _acceleration;					  // Acceleration
	float _rotateVelocity;					  // How fast the ship rotate

	AEVec2 _velocityVector;					  // The current velocity since the last frame (updated by the physics system)
	AEVec2 _velocityChangeVector;             // Velocity change in the current frame (before physics system) 
	AEVec2 _velocityDirection;                // Mainly for normalised Direction at the end of the physics system 
	AEVec2 _angularVelocity;				  // Vector towards rotation direction
	AEVec2 _gravityVelocity;                  // Vector that handles the gravity
	AEVec2 _steeringVector;					  // Target direction that the Ai wants to travel
	AEVec2 _collisionVector;                  // Vector that forces the object to move in that direction when collided
	AEVec2 _rotationVector;                   // Rotation vector to rotate the planet.

	COLLISIONTAG _tag;

	// Constructor
	cRigidBody() = delete;
	cRigidBody(float mass, float velocity, float velocityCap = 2.0f, float acceleration = 0.0f,
		float rotateVelocity = 0.0f, COLLISIONTAG tag = COLLISIONTAG::NONE);


	float CalculateVelwithAcc(float velocity);

	// Destructor
	~cRigidBody() = default;
};