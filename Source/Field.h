#ifndef FIELD_H
#define FIELD_H

#include "Enums.h"

class Snake;
class PowerUp;

class Field 
{
public:
	Field(float ScreenWidth, float ScreenHight, class Sound* PickUpSound);
	~Field();

	void HandleSnakeInput(Input& currentSnakeInput);
	void SnakeMove();
	void Draw();

	inline Snake* GetSnake() const { return snake; };
	inline int GetScore() const { return _Score; };

private:
	
	float _ScreenWidth;
	float _ScreenHight;
	int _Score;

	//Snake properties
	Snake* snake;
	Input SnakeCurrentInput = Input::NO_PRESS;
	float _WaitingSeconds;
	
	//PowerUp properties
	PowerUp* powerUp;
	int _xLocationPowerUp;
	int _yLocationPowerUp;
	class Sound* _PickUpSound;

	void GameOver();
};

#endif // !FIELD_H