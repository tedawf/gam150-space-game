/*********************************************************************************
* \file			SystemManager.cpp
* \brief		Manager for all systems in the game
* \author		Jun Yi, Chong, 50% Code Contribution
*        		Wei Feng, Ang, 50% Code Contribution
*
*				Register all systems and set their signatures.
*				The system manager is also responsible for updating the systems.
*
*
* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "SystemManager.h"
#include "../Systems/SystemList.h"

void SystemManager::Init()
{
	// Register systems
	
	// Logic 
	RegisterSystem<WeaponSystemRange>();
	RegisterSystem<WeaponSystemMelee>();
	RegisterSystem<SpaceShipLogicSystem>();
	RegisterSystem<WarpingSystem>();
	RegisterSystem<PhysicsSystem>();
	RegisterSystem<CollisionSystem>();
	RegisterSystem<AISystem>();
	RegisterSystem<BossSystem>();
	RegisterSystem<HealthSystem>();
	RegisterSystem<ProjectileSystem>();
	RegisterSystem<ParticleEmitterSystem>();
	RegisterSystem<TimelineSystem>();
	RegisterSystem<ScannerSystem>();

	// Rendering
	RegisterSystem<RenderSystem>();
	RegisterSystem<ParticleSystem>();
	RegisterSystem<UISystem>();
	RegisterSystem<DebugToolsSystem>();

	for (auto const& system : _systemMap)
	{
		system->Init();
	}
}

void SystemManager::Update()
{
	for (auto const& system : _systemMap)
	{
		system->Update();
	}
}

void SystemManager::Render()
{
	for (auto const& system : _systemMap)
	{
		system->Render();
	}
}

void SystemManager::EntityDestroyed(ENTITY entity)
{
	// Erase an entity from all system lists
	for (auto const& system : _systemMap)
	{
		if (system->entitiesList.find(entity) != system->entitiesList.end())
		{
			// The first of the pair is the system name
			// The second of the pair is the shared pointer to the system
			system->OnComponentRemove(entity);				//Remove the entity from the system tracking (Sprite Layers)
			system->entitiesList.erase(entity);
		}

	}
}

void SystemManager::UpdateEntitySignature(ENTITY entity, SIGNATURE entitySignature, SIGNATURE oldentitySignature)
{
	for (auto const& system : _systemMap)
	{
		// The first of the pair is the system name
		// The second of the pair is the shared pointer to the system
		const char* systemName = typeid(*system).name();
		auto const& systemSignature = _signaturesMap[systemName];

		// Do bitwise comparison of the signatures
		// The & operator returns a result for us to compare against
		// 01001101 & 00001100 = 00001100
		// 01000101 & 00001100 = 00000100 (Wrong entity)
		if ((entitySignature & systemSignature) == systemSignature)
		{
			// Entity signature matches system signature, add into set
			system->entitiesList.insert(entity);
			system->OnComponentAdd(entity);
		}
		else if((oldentitySignature & systemSignature) == systemSignature)
		{
			// Entity signature does not match system signature, erase from set
			// Will run erase on all systems 
			system->OnComponentRemove(entity);
			system->entitiesList.erase(entity);
		}
	}
}
