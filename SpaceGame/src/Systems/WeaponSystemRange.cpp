#include "WeaponSystemRange.h"
#include "SpaceShipLogicSystem.h"
#include "../ECS/Core.h"
#include "../Global.h"
#include <iostream>

#include "../ECS/Factory.h"
/******************************************************************************/
/*!
	Global Variables
*/
/******************************************************************************/

void WeaponSystemRange::Init()
{
	SIGNATURE signature;
	signature.set(Core::Get().GetComponentType<cTransform>());
	signature.set(Core::Get().GetComponentType<cRangeWeapon>());
	Core::Get().SetSystemSignature<WeaponSystemRange>(signature);
}

void WeaponSystemRange::Update()
{
	cTransform* transform;
	cRangeWeapon* rangeweapon;

	for (auto const& entity : entitiesList)
	{
		transform = Core::Get().GetComponent<cTransform>(entity);
		rangeweapon = Core::Get().GetComponent<cRangeWeapon>(entity);

		if (!rangeweapon->_isShooting) continue;
		{
			//if (/*spaceship->_currWeaponMode == WeaponMode::range &&*/
			//	rangeweapon->_isShooting /*&& spaceship->_shootDelay > rangeweapon->_fireCooldownTimer*/)
			//{
			//	switch (rangeweapon->_currWeapon)
			//	{
			//	case WeaponType::pistol:
			//		rangeweapon->_fireCooldownTimer = 0.0f;
			//		NormalShoot(transform);
			//		break;
			//	case WeaponType::machineGun:
			//		rangeweapon->_fireCooldownTimer = 0.0f;
			//		MachineGunShoot(transform);
			//		break;
			//	case WeaponType::grenadeGun:
			//		break;
			//	case WeaponType::laser:
			//		break;
			//	}
			//}
		}

		// Decrement timer if on cooldown
		if (rangeweapon->_attackCooldownTimer > 0.0f)
		{
			rangeweapon->_attackCooldownTimer -= g_dt;

			if (rangeweapon->_attacksLeft > 0)
			{
				// Currently attacking, set delay between attacks
				if (rangeweapon->_delayTimer > 0.0f)
					rangeweapon->_delayTimer -= g_dt;
				else
				{
					// Set delay
					rangeweapon->_delayTimer = rangeweapon->_delayBetweenAttacks;

					// Fire
					NormalShoot(transform,rangeweapon->_tag);
					--rangeweapon->_attacksLeft;
					rangeweapon->_isShooting = false;
				}
			}
		}
		else
		{
			// Set cooldown
			rangeweapon->_attackCooldownTimer = rangeweapon->_attackCooldown;
			rangeweapon->_attacksLeft = rangeweapon->_numberOfAttacks;
		}
	}
}

void NormalShoot(cTransform* transform, OWNERTAG tag)
{
	AEVec2 bulletDirection;
	AEVec2 bulletVelocity;

	// Setting the direction of bullet spawn
	AEVec2Set(&bulletDirection, AECos(transform->_rotation), AESin(transform->_rotation));
	// Bullet velocity
	AEVec2Scale(&bulletVelocity, &bulletDirection, 600.0f);
	// Spawn the bullet at the tip of player
	if (tag == OWNERTAG::PLAYER)
		Factory::CreateBullet(transform->_position.x + AECos(transform->_rotation) * (transform->_scale.x/2.0f),
			transform->_position.y + AESin(transform->_rotation) * (transform->_scale.y/2.0f), bulletVelocity, bulletDirection, transform->_rotation + PI / 2, OWNERTAG::PLAYER);
	else if (tag == OWNERTAG::AI)
		Factory::CreateBullet(transform->_position.x + AECos(transform->_rotation) * (transform->_scale.x / 2.0f),
			transform->_position.y + AESin(transform->_rotation) * (transform->_scale.y / 2.0f), bulletVelocity, bulletDirection, transform->_rotation + PI / 2, OWNERTAG::AI);
}

void HomingShoot(cTransform* transform)
{
	(void)transform;
}

void MachineGunShoot(cTransform* transform)
{
	AEVec2 bulletDirection;
	AEVec2 bulletVelocity;

	// Setting the direction of bullet spawn
	AEVec2Set(&bulletDirection, AECos(transform->_rotation), AESin(transform->_rotation));
	// Bullet velocity
	AEVec2Scale(&bulletVelocity, &bulletDirection, 600.0f);
	// Spawn the bullet at the tip of player
	Factory::CreateBullet(transform->_position.x + AECos(transform->_rotation) * 100.0f,
		transform->_position.y + AESin(transform->_rotation) * 100.0f, bulletVelocity, bulletDirection, transform->_rotation + PI / 2, OWNERTAG::PLAYER);
}

//void TripleShot(cTransform* transform)
//{
//	AEVec2 bulletDirection;
//	AEVec2 bulletVelocity;
//
//	// Setting the direction of bullet spawn
//	AEVec2Set(&bulletDirection, AECos(transform->_rotation), AESin(transform->_rotation));
//	// Bullet velocity
//	AEVec2Scale(&bulletVelocity, &bulletDirection, 600.0f);
//	// Spawn the bullet at the tip of player
//	Factory::CreateBullet(transform->_position.x + AECos(transform->_rotation) * 100.0f,
//		transform->_position.y + AESin(transform->_rotation) * 100.0f, bulletVelocity, transform->_rotation + PI / 2);
//}
