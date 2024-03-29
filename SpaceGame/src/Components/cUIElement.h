#pragma once
#include "Component.h"
#include "../Global_Graphics.h"

enum class UI_TYPE
{
	NONE,
	TEXT,
	BUTTON,
	IMAGE
};

enum class UI_ROLE
{
	NONE,
	HEALTH,
	SHIELD,
	SHIELDBUBBLE,
	THRUSTER,
	C3_FRAME,
	C3_FAKEUPGRADE,
	C3_UPGRADE,
	C3_TEXT,
	DAMAGE_FLOAT,
	INDICATE_AI,
	INDICATE_COLLECT,
	GAMEOVER,
	GAMEWIN,
	PAUSE,
	INGAMEOPTIONS,
	BEGIN_BTN,
	CREDITS_BTN,
	OPTIONS_BTN,
	QUIT_BTN, 
	LOW_HEALTH_UI,
	SHIELD_DOWN_UI,
	BOSS_INCOMING_UI,
	TICKBOX,
	TICK,
	OBJECTIVES,
	QUIT,
	DEFEATBOSS_UI,
	OUTGUNNED_UI
};

class cUIElement :public Component
{
public:
	//Data
	UI_TYPE _type = UI_TYPE::NONE;
	UI_ROLE _role = UI_ROLE::NONE;
	unsigned int _roleIndex = 0;			//Normally map to ui Role or its entity

	unsigned int _roleIndex2 = 0;
	float _timer = 0.0f;					//For floating damage
	//Text
	TextInfo _text;

	bool _isHovered;
	bool _isClicked;
	bool _isSelectable;
	bool _isActive = true;
	void (*_updateFP)(void);

	// Constructor with parameter
	cUIElement() = delete;
	cUIElement(UI_TYPE type, UI_ROLE role, unsigned int roleIndex = 0);
	cUIElement(const char* text, ColorInfo tint = {1,1,1,1}, ColorInfo blend = {1,1,1,1}, TEXT_ANCHOR anchor = TEXT_ANCHOR::CENTERLEFT);
	~cUIElement();										// Virtual Destructor

};