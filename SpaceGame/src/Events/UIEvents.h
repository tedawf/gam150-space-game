#pragma once
#include "Events.h"

namespace Events
{
	struct OnHealthChange :public EventsBase
	{
		OnHealthChange(float newHP) :_newHealth{ newHP }{};
		float _newHealth;
	};

	struct OnLowHealth :public EventsBase
	{
		OnLowHealth(bool state) : _state{ state } {};
		bool _state;
	};

	struct OnBossIncoming :public EventsBase
	{
		OnBossIncoming(bool state) : _state{ state } {};
		bool _state;
	};

	struct OnShieldDown :public EventsBase
	{
		OnShieldDown(bool state) : _state{ state } {};
		bool _state;
	};

	struct OnShieldChange :public EventsBase
	{
		OnShieldChange(float newShield) :_newShield{ newShield } {};
		float _newShield;
	};

	struct OnShieldActivate :public EventsBase
	{
		OnShieldActivate(){};
	};

	struct OnThrusterChange : public EventsBase
	{
		OnThrusterChange(float newVelocity, float capVelocity, float overheat, float overheatLimit)
			: _newVelocity{ newVelocity }, _capVelocity{ capVelocity }, _overheatTime{ overheat }, _overheatLimit{ overheatLimit } {}
		float _newVelocity;
		float _capVelocity;
		float _overheatTime;
		float _overheatLimit;
	};

	struct OnMouseClick :public EventsBase
	{
		OnMouseClick(float x, float y) :_xPos{ x }, _yPos{ y } {};
		float _xPos;
		float _yPos;
	};

	struct OnMouseHover :public EventsBase
	{
		OnMouseHover(float x, float y) :_xPos{ x }, _yPos{ y } {};
		float _xPos;
		float _yPos;
	};

	struct TogglePause :public EventsBase
	{
		TogglePause(bool show) :_show{ show } {};
		bool _show;
	};

	// Selected 1 upgrade and decrementing reroll
	struct OnUpgradeReroll :public EventsBase
	{
		OnUpgradeReroll(int& rerollInfo) :_rerollInfo{rerollInfo} {};
		int& _rerollInfo;
	};

	struct OnUpgradeDescpChange :public EventsBase
	{
		OnUpgradeDescpChange(int upgradeIndex, int slot) :_upgradeIndex{ upgradeIndex }, _slot{slot} {};
		int _upgradeIndex;		//-1 is no desption
		int _slot;				//Left to Right
	};
}
