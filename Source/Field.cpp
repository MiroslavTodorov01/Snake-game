#include "Field.h"
#include "Snake.h"
#include "PowerUp.h"
#include "raylib.h"
#include <iostream>

Field::Field(float ScreenWidth, float ScreenHight, Sound* PickUpSound)
{
	_PickUpSound = PickUpSound;

	_ScreenWidth = ScreenWidth;
	_ScreenHight = ScreenHight;
	_Score = 0;

	snake = new Snake(ScreenWidth / 2, ScreenHight / 2 , 20.f, 20.f);
	_WaitingSeconds = 0;

	int diffX = (_ScreenWidth * 0.88) - ((_ScreenWidth * 0.12) + 10);
	int diffY = (_ScreenHight * 0.88) - (_ScreenHight * 0.12);

	_xLocationPowerUp = rand() % diffX + ((_ScreenWidth * 0.12) + 10);
	_yLocationPowerUp = rand() % diffY + (_ScreenHight * 0.12);
	powerUp = new PowerUp(_xLocationPowerUp, _yLocationPowerUp, 15);
}

Field::~Field() 
{
	UnloadSound(*_PickUpSound);

	if (powerUp)
	{
		delete powerUp;
	}

	delete snake;
}

void Field::HandleSnakeInput(Input& currentSnakeInput)
{
	if (IsKeyDown(KEY_A))
	{
		currentSnakeInput = Input::LEFT;
		return;
	}

	if (IsKeyDown(KEY_D))
	{
		currentSnakeInput = Input::RIGHT;
		return;
	}

	if (IsKeyDown(KEY_W))
	{
		currentSnakeInput = Input::UP;
		return;
	}

	if (IsKeyDown(KEY_S))
	{
		currentSnakeInput = Input::DOWN;
		return;
	}
}

void Field::SnakeMove() 
{
	if (snake->GetIsAlive())
	{
		HandleSnakeInput(SnakeCurrentInput);

		if (_WaitingSeconds < 0.1)
		{
			_WaitingSeconds += GetFrameTime();
		}
		else
		{
			snake->Move(SnakeCurrentInput);
			_WaitingSeconds = 0.f;
		}

		if (snake->CheckIfWeHitPowerUp(_xLocationPowerUp, _yLocationPowerUp, 15))
		{	
			PlaySound(*_PickUpSound);

			_Score++;

			int diffX = (_ScreenWidth * 0.88) - ((_ScreenWidth * 0.12) + 10);
			int diffY = (_ScreenHight * 0.88) - (_ScreenHight * 0.12);

			_xLocationPowerUp = rand() % diffX + ((_ScreenWidth * 0.12) + 10);
			_yLocationPowerUp = rand() % diffY + (_ScreenHight * 0.12);

			delete powerUp;
			powerUp = nullptr;

			powerUp = new PowerUp(_xLocationPowerUp, _yLocationPowerUp, 15);

			snake->Grow();
		}
	}
}

void Field::GameOver()
{
	Vector2 TextLocation = MeasureTextEx(GetFontDefault(), GAME_OVER_TEXT, 50, 2);

	DrawText(GAME_OVER_TEXT, 66, (GetScreenHeight() / 2) - (TextLocation.y / 2), 50, RED);

	if (IsKeyPressed(KEY_SPACE))
	{
		int diffX = (_ScreenWidth * 0.84) - ((_ScreenWidth * 0.15) + 10);
		int diffY = (_ScreenHight * 0.79) - (_ScreenHight * 0.1);

		_xLocationPowerUp = rand() % diffX + ((_ScreenWidth * 0.15) + 10);
		_yLocationPowerUp = rand() % diffY + (_ScreenHight * 0.1);

		powerUp->Reset(_xLocationPowerUp, _yLocationPowerUp, 15);
		snake->Reset(GetScreenWidth() / 2.f, GetScreenHeight() / 2.f, 20.f, 20.f);

		_Score = 0;
	}
}

void Field::Draw() 
{
	int calculatedX = (_ScreenWidth * 0.12) - 10;
	int calculatedY = _ScreenHight * 0.12;

	//border
	DrawRectangle(calculatedX, (calculatedY) - 10, _ScreenWidth - ((_ScreenWidth * 0.12) * 2) + 20, 10, BLACK);		// up line
	DrawRectangle(calculatedX, calculatedY, 10, _ScreenHight - ((_ScreenHight * 0.12) * 2), BLACK);					// left line
	DrawRectangle(_ScreenWidth * 0.88, calculatedY, 10, _ScreenHight - ((_ScreenHight * 0.12) * 2), BLACK);			// right line
	DrawRectangle(calculatedX, _ScreenHight * 0.88, _ScreenWidth - ((_ScreenWidth * 0.12) * 2) + 20, 10, BLACK);	// down line

	snake->Draw();

	if (!snake->GetIsAlive())
	{
		GameOver();
	}

	if (powerUp)
	{
		powerUp->Draw();
	}
}