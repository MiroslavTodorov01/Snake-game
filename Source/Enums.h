#ifndef ENUMS_H
#define ENUMS_H

#define GAME_OVER_TEXT "Game over. You hit your own body!\n      Press Space to restart."

enum class Input
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NO_PRESS
};

enum class PowerUpAnimationState 
{
	STATE_1,
	STATE_2,
	STATE_3
};

enum class StartMenuButtonPressed 
{
	MAIN_MANU,
	START_BUTTON,
	CONTROLS_BUTTON,
	BACK_BUTTON,
};

#endif // !ENUMS_H