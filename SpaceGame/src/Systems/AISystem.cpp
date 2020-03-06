/*********************************************************************************
* \file			AISystem.cpp
* \author		Ang Wei Feng
* \version		2.0
* \date			28/02/2020
* \par			AI Pillar/System Code
* \note			Course: GAM150
* \brief		Controls the behaviour for AI

* \copyright	Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
				or disclosure of this file or its contents without the prior
				written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "AISystem.h"							//Self Header
#include "../ECS/Core.h"						//Work with ECS
#include "../Components/ComponentList.h"		//Get necessary component references
#include "../Global.h"
#include <variant>

/******************************************************************************/
/*!
  \brief	Sets the system signature for this system based on components required
*/
/******************************************************************************/
void AISystem::Init()
{
	SIGNATURE signature;

	//Set the bits for necessary components
	signature.set(Core::Get().GetComponentType<cAI>());

	//Assign the signature for this System
	Core::Get().SetSystemSignature<AISystem>(signature);
}

void AISystem::Update()
{
	cAI* ai;

	// Update all entities that has the components we want
	for (auto const& entity : entitiesList)
	{
		// Get self
		ai = Core::Get().GetComponent<cAI>(entity);

		// Update this ai's blackboard
		UpdateBlackboard(ai->_blackboard, entity);

		// Run this ai's current state
		std::visit([&]( auto& state ) 
		{
			state.Run( ai->_blackboard, ai->_currentState );
		}, ai->_currentState.m_Varient );
	}
}

void AISystem::OnComponentAdd(ENTITY) {};
void AISystem::OnComponentRemove(ENTITY) {};

void AISystem::UpdateBlackboard(aiBlackBoard& bb, ENTITY id)
{
	// Set ids
	bb.id = id;
	const ENTITY pid = PlayerManager::player;

	// Get components
	cTransform* self = Core::Get().GetComponent<cTransform>(id);
	cTransform* player = Core::Get().GetComponent<cTransform>(pid);
	
	// Calculate distance
	bb.distanceFromPlayer = AEVec2Distance(&player->_position, &self->_position);

	// Calculate vector towards player
	AEVec2 temp;
	AEVec2Sub(&temp, &player->_position, &self->_position);
	AEVec2Normalize(&temp, &temp);
	bb.directionToPlayer = temp;
}