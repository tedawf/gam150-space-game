/**********************************************************************************
* \file			aiRetreat.cpp
* \brief		AI retreat state
* \author		Wei Feng,		Ang,		100% Code Contribution
*
*				Long Description
*				- Initalise retreat state of AI
*
* \copyright Copyright (c) 2020 DigiPen Institute of Technology. Reproduction
or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
**********************************************************************************/
#include "../aiState.h"

#include "../../Math/Math.h"
#include "../../Global.h"
#include "../../Tools/Editor.h"

void aiRetreat::OnEnter(aiBlackBoard& bb)
{
	aiBase::OnEnter(bb);

	// Initialise state
	bb.rotationSpeed = bb.baseRotationSpeed / 2.0f;
	_safeDistance = 500.0f + bb.baseAttackRange;
	FindSafePosition(bb);
}

void aiRetreat::OnUpdate(aiBlackBoard& bb)
{
	if (AEVec2Distance(&_safePosition, &trans->_position) > 10.0f)
	{
		Transform::RotateToTarget(trans->_rotation, trans->_position, _safePosition, bb.rotationSpeed * g_dt);
		rb->_velocity += bb.baseAcceleration;

		Steering::SeekTarget(
			rb->_steeringVector,
			trans->_position, _safePosition,
			rb->_velocity * g_dt * TurnToTarget(trans->_rotation, _safePosition),
			rb->_velocityVector);

		Steering::Wander(rb->_steeringVector, rb->_velocityDirection, bb.wanderAngle, 2.0f);
	}
	else
		ChangeState((AERandFloat() > 0.5f) ? STATE_CHASE : STATE_IDLEWANDER);
}

void aiRetreat::OnExit(aiStateList& var) 
{ 
	aiBase::OnExit(var); 
}

void aiRetreat::FindSafePosition(const aiBlackBoard& bb)
{
	AEVec2 desired = bb.directionToPlayerN;
	AEVec2Neg(&desired, &desired);
	AEVec2Scale(&desired, &desired, _safeDistance);
	AEVec2Add(&_safePosition, &trans->_position, &desired);
}

float aiRetreat::TurnToTarget(const float& self, const AEVec2& target)
{
	AEVec2 selfRot{ cosf(self), sinf(self) };
	AEVec2 targetRot{ target };

	AEVec2Normalize(&selfRot, &selfRot);
	AEVec2Normalize(&targetRot, &targetRot);

	float dotAngle = AEVec2DotProduct(&selfRot, &targetRot);

	return (dotAngle < 0.0f ? 0.25f : dotAngle);
}
