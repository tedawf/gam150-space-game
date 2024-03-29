/**********************************************************************************
* \file			aiIdleWander.h
* \brief		AI idle wander state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise idle wander of AI
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#pragma once

#include "aiBase.h"

class aiIdleWander : public aiBase
{
private:
	void OnEnter(aiBlackBoard&) override;
	void OnUpdate(aiBlackBoard&) override;
	void OnExit(aiStateList&) override;

	// Extra components this state needs

	// State variables
	float _distance;
	AEVec2 _randomPosition;

	void FindRandomPosition();
	float TurnToTarget(const float& self, const AEVec2& target);
};