#include <iostream>
#include <cstdlib>
#include <cmath>
#include "raylib.h"
#include "Field.h"
#include "Snake.h"
#include "PowerUp.h"
#include "StartMenu.h"
#include "Enums.h"

float InterpolateByValue(float currentLocation, float goalLocation, float DeltaTime)
{
	int distance = goalLocation - currentLocation;

	if (distance > 0)
	{
		if (currentLocation + DeltaTime > goalLocation)
		{
			return goalLocation;
		}

		return currentLocation + DeltaTime;
	}

	if (goalLocation > currentLocation - DeltaTime)
	{
		return goalLocation;
	}

	return currentLocation - DeltaTime;
}

void DrawScore(int count) 
{
	DrawRectangle((GetScreenWidth() / 2) - 50, 30, 100, 5, BLACK );
	DrawRectangle((GetScreenWidth() / 2) - 50, 30, 5, 35, BLACK);
	DrawRectangle((GetScreenWidth() / 2) - 50, 65, 100, 5, BLACK);
	DrawRectangle((GetScreenWidth() / 2) + 45, 30, 5, 35, BLACK);
	
	char text[5];
	sprintf_s(text, "%d", count);

	Vector2 textLocation = MeasureTextEx(GetFontDefault(), text, 20, 2);

	DrawText(text, ((GetScreenWidth() / 2) - 50) + ((100 - textLocation.x) / 2), 40, 25, BLACK);
}

int main() 
{
	InitWindow(1000, 1000, "Snake game");
	InitAudioDevice();

	StartMenu* startMenu = new StartMenu();

	Sound s = LoadSound("Sounds/PickupSound.wav");

	Field* field = new Field(1000, 1000, &s);
	Color ScreenColor = {173, 204, 96, 255};

	SetTargetFPS(60);

	while (true)
	{
		if (WindowShouldClose())
		{
			break;
		}

		BeginDrawing();
		ClearBackground(ScreenColor);

		startMenu->HandleStartMenu();

		if (startMenu->GetPressedButton() != StartMenuButtonPressed::START_BUTTON)
		{
			EndDrawing();

			continue;
		}

		HideCursor();

		field->SnakeMove();

		field->Draw();
		DrawScore(field->GetScore());

		EndDrawing();
	};

	CloseAudioDevice();
	CloseWindow();

	delete startMenu;
	delete field;

	return 0;
}