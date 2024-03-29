/**********************************************************************************
* \file			cSpaceShip.h
* \brief		Component for interlligent entity that behave like spaceship
* \author		Jin Kiat, Chong, 100% Code Contribution
*
*				Long Description
*				- Data for thrust movement
*				- Data for weapon capability
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once
#include "Component.h"

enum class WeaponMode
{
	WEAPONMODE_NONE,					//If the spaceship does not have weapon features
	WEAPONMODE_RANGE,
	WEAPONMODE_MELEE,
};

class cSpaceShip :public Component
{
public:
	// Spaceship Thruster (Movements)
	bool	_isThrusting;			// Check for thruster use from player/AI input
	float	_thrustDelayCurr;		// Countdown timer when thruster overheats
	float	_thrustDelay;			// Duration of thruster overheat
	float	_overheatThrusterCurr;	// If player thrust at maxSpeed for too long
	float	_overheatThruster = 2.4f;		// Duration to achieve overheat

	//We can know if the spaceship has any weapon features
	WeaponMode _currWeaponMode;

	cSpaceShip() = default;
	cSpaceShip(bool isThrusting, float thrustDelay, WeaponMode currWeaponMode);
	~cSpaceShip() = default;
};