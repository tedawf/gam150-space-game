#pragma once

#include "AEEngine.h"							//AEVec2
#include "Component.h"

class cRigidBody:public Component
{
public:
	float _mass;								// Mass of the object
	float _velocity;							// Velocity Value of the ship
	float _velocityCap;							// Velocity Value of the ship
	float _acceleration;						// Rate of change of velocity
	float _rotateVelocity;						// How fast a ship rotate

	AEVec2 _velocityVector;						// Mainly for normalised Direction
	AEVec2 _angularVelocity;					// Vector towards rotation direction

	cRigidBody() = delete;	
	cRigidBody(float mass, float velocity,		// Constructor with initalisation
		float velocityCap = 0.0f, float acceleration = 0.0f, 
		float rotateVelocity = 0.0f);
	~cRigidBody() = default;					// Default Destructor
};

//float inertia;								// Inertia
//float inertiaInverse;							// Inverse Inertia