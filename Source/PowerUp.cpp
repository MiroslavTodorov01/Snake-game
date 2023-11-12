#include "PowerUp.h"
#include "raylib.h"
#include <iostream>
PowerUp::PowerUp(int& XLocation, int& YLocation, float Radius) 
{

	_OneThirdOfRadius = Radius / 3;
	_TimeBeforNextDraw = 2.f;

	State = PowerUpAnimationState::STATE_1;

	Reset(XLocation, YLocation, Radius);
}

bool PowerUp::CheckIfIsOutsideBorder() 
{
	if (_XLocation < _Radius)
	{
		return true;
	}

	if (_XLocation > GetScreenWidth() - _Radius)
	{
		return true;
	}

	if (_YLocation < _Radius)
	{
		return true;
	}

	if (_YLocation > GetScreenHeight() - _Radius)
	{
		return true;
	}

	return false;
}

void PowerUp::HandleBorder() 
{
	if (_XLocation < _Radius)
	{
		_XLocation = _Radius;
	}

	if (_XLocation > GetScreenWidth() - _Radius)
	{
		_XLocation = GetScreenWidth() - _Radius;
	}

	if (_YLocation < _Radius)
	{
		_YLocation = _Radius;
	}

	if (_YLocation > GetScreenHeight() - _Radius)
	{
		_YLocation = GetScreenHeight() - _Radius;
	}
}

void PowerUp::GetNextAnumState(PowerUpAnimationState& State)
{
	if (_TimeBeforNextDraw < 0.3)
	{
		return;
	}

	switch (State)
	{
	case PowerUpAnimationState::STATE_1:

		_Radius = _OneThirdOfRadius;

		State = PowerUpAnimationState::STATE_2;

		break;
	case PowerUpAnimationState::STATE_2:

		_Radius = _OneThirdOfRadius * 2;

		State = PowerUpAnimationState::STATE_3;

		break;
	case PowerUpAnimationState::STATE_3:

		_Radius = _OneThirdOfRadius * 3;

		State = PowerUpAnimationState::STATE_1;

		break;
	default:
		break;
	}

	_TimeBeforNextDraw = 0;
}

void PowerUp::Draw() 
{
	_TimeBeforNextDraw += GetFrameTime();

	GetNextAnumState(State);

	DrawCircle(_XLocation, _YLocation, _Radius, BLACK);
}

void PowerUp::Reset(int& newXLocation, int& newYLocation, float newRadius) 
{
	_XLocation = newXLocation;
	_YLocation = newYLocation;
	_Radius = newRadius;

	if (CheckIfIsOutsideBorder())
	{
		HandleBorder();
		newXLocation = _XLocation;
		newYLocation = _YLocation;
	}
}