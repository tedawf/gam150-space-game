#pragma once

#include "AEEngine.h"

class cRigidBody
{
public:
	float mass;                              // Mass of the ship
	float inertia;                           // Inertia
	float acceleration;						 // Acceleration
	float inertiaInverse;                    // Inverse Inertia
	float velocity;
	AEVec2 position;						 // Position of the spaceship
	AEVec2 velocityVector;					// Velocity of the ship
	AEVec2 angularVelocity;					 // Angular Velocity of the ship (not sure if needed)

	// Constructor
	cRigidBody();

	// Destructor
	~cRigidBody() = default;
};