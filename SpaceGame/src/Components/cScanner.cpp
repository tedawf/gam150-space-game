#include "cScanner.h"		//Component class declaration


cScanner::cScanner(const char* text, ScannerType type, ColorInfo tint, ColorInfo blend, TEXT_ANCHOR anchor) 
	: _classification{ type }, _displayTime {0.0f}, _currTime{ 0.0f }
{
	sprintf_s(_textToDisplay._textBuffer, text);
	_textToDisplay._colorTint = tint;
	_textToDisplay._colorBlend = blend;
	_textToDisplay._anchor = anchor;
	_textToDisplay._bufferCount = strlen(text);
	_textToDisplay._usingScreenSpace = false;
}

void cScanner::SetRecieverTime(float displayTime)
{
	_displayTime = _currTime = displayTime;
}