#ifndef POWER_UP
#define POWER_UP

#include "Enums.h"

class PowerUp
{
public:
	PowerUp(int& XLocation, int& YLocation, float DrawSize);

	bool CheckIfIsOutsideBorder();
	void HandleBorder();
	void Draw();
	void Reset(int& newXLocation, int& newYLocation, float newRadius);

private:
	float _XLocation;
	float _YLocation;
	float _Radius;
	PowerUpAnimationState State;

	float _TimeBeforNextDraw;

	int _OneThirdOfRadius;

	void GetNextAnumState(PowerUpAnimationState& State);
};

#endif // !POWER_UP