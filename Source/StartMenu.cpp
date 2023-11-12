#include "StartMenu.h"
#include "raylib.h"
#include <string>

StartMenu::StartMenu()
{
	_PressedButton = StartMenuButtonPressed::MAIN_MANU;

	_StartButtonPixelsLocation = new int[4];
	_StartButtonPixelsLocation[0] = (GetScreenWidth() / 2) - 50;
	_StartButtonPixelsLocation[1] = _StartButtonPixelsLocation[0] + 100;
	_StartButtonPixelsLocation[2] = GetScreenHeight() / 2;
	_StartButtonPixelsLocation[3] = _StartButtonPixelsLocation[2] + 40;

	_ControlsButtonPixelLocation = new int[4];
	_ControlsButtonPixelLocation[0] = (GetScreenWidth() / 2) - 50;
	_ControlsButtonPixelLocation[1] = _ControlsButtonPixelLocation[0] + 100;
	_ControlsButtonPixelLocation[2] = (GetScreenHeight() / 2) + 55;
	_ControlsButtonPixelLocation[3] = _ControlsButtonPixelLocation[2] + 40;

	_BackButtonPixelLocation = new int[4];
	_BackButtonPixelLocation[0] = 50;
	_BackButtonPixelLocation[1] = _BackButtonPixelLocation[0] + 130;
	_BackButtonPixelLocation[2] = GetScreenHeight() - 90;
	_BackButtonPixelLocation[3] = _BackButtonPixelLocation[2] + 40;
}

StartMenu::~StartMenu() 
{
	if (_StartButtonPixelsLocation)
	{
		delete[] _StartButtonPixelsLocation;
	}

	if (_ControlsButtonPixelLocation)
	{
		delete[] _ControlsButtonPixelLocation;
	}

	if (_BackButtonPixelLocation)
	{
		delete[] _BackButtonPixelLocation;
	}
}

bool StartMenu::CheckIfWeClickStartButton()
{
	if (_PressedButton == StartMenuButtonPressed::START_BUTTON)
	{
		return true;
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		int MouseX = GetMouseX();
		int MouseY = GetMouseY();

		if (CheckIfWeAreInsideBox(MouseX, MouseY, _StartButtonPixelsLocation[0], _StartButtonPixelsLocation[1], _StartButtonPixelsLocation[2], _StartButtonPixelsLocation[3]))
		{
			_PressedButton = StartMenuButtonPressed::START_BUTTON;

			return true;
		}
	}

	return false;
}

bool StartMenu::CheckIfWeClickControlsButton() 
{
	if (_PressedButton == StartMenuButtonPressed::CONTROLS_BUTTON)
	{
		return true;
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		int MouseX = GetMouseX();
		int MouseY = GetMouseY();

		if (CheckIfWeAreInsideBox(MouseX, MouseY, _ControlsButtonPixelLocation[0], _ControlsButtonPixelLocation[1], _ControlsButtonPixelLocation[2], _ControlsButtonPixelLocation[3]))
		{
			_PressedButton = StartMenuButtonPressed::CONTROLS_BUTTON;

			return true;
		}
	}

	return false;
}

bool StartMenu::CHeckIfWeClickBackButton() 
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		int MouseX = GetMouseX();
		int MouseY = GetMouseY();

		if (CheckIfWeAreInsideBox(MouseX, MouseY, _BackButtonPixelLocation[0], _BackButtonPixelLocation[1], _BackButtonPixelLocation[2], _BackButtonPixelLocation[3]))
		{
			_PressedButton = StartMenuButtonPressed::MAIN_MANU;

			return true;
		}
	}

	return false;
}

bool StartMenu::CheckIfWeAreInsideBox(int MouseX, int MouseY, int WidthPixelStart, int WidthPixelEnd, int HightPixelStart, int HightPixelEnd)
{
	if (MouseX >= WidthPixelStart && MouseX <= WidthPixelEnd)
	{
		if (MouseY >= HightPixelStart && MouseY <= HightPixelEnd)
		{
			return true;
		}
	}

	return false;
}

void StartMenu::DrawStartButton() 
{
	Rectangle r;
	r.x = (GetScreenWidth() / 2) - 50;
	r.y = GetScreenHeight() / 2;
	r.width = 100;
	r.height = 40;

	DrawRectangleLinesEx(r, 5, BLACK);

	DrawText("Start", (GetScreenWidth() / 2) - 30, (GetScreenHeight() / 2) + 10, 22, BLACK);
}

void StartMenu::DrawControlsButton() 
{
	Rectangle r;
	r.x = (GetScreenWidth() / 2) - 50;
	r.y = (GetScreenHeight() / 2) + 55;
	r.width = 100;
	r.height = 40;

	DrawRectangleLinesEx(r, 5, BLACK);

	DrawText("Controls", (GetScreenWidth() / 2) - 38, (GetScreenHeight() / 2) + 67, 19, BLACK);
}

void StartMenu::DrawButton(Rectangle* rec, int lineThick, Color* c, int textXLocation, int textYLocation, int font, const char* key, const char* description = "")
{
	DrawRectangleLinesEx(*rec, lineThick, *c);
	DrawText(key, textXLocation, textYLocation, font, *c);

	if (description == "")
	{
		return;
	}
	DrawText(description, rec->x + 45, rec->y + 9, 20, *c);
}

void StartMenu::DrawControlsMenu() 
{

	const int xLocation = (GetScreenWidth() / 2) - 60;
	const int distanceBetweenTwoRectangles = 20;

	Color c = BLACK;

	//DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 10, BLACK);

	Rectangle w;
	w.x = xLocation;
	w.y = (GetScreenHeight() / 2) - ((distanceBetweenTwoRectangles + 70)+10);
	w.width = 35;
	w.height = 35;
	DrawButton(&w, 5, &c, w.x + 11, w.y + 10, 18, "W", "Move up");

	Rectangle s;		// center
	s.x = xLocation;
	s.y = w.y + w.height + distanceBetweenTwoRectangles;
	s.width = 35;
	s.height = 35;
	DrawButton(&s, 5, &c, s.x + 11, s.y + 10, 18, "S", "Move down");

	Rectangle a;
	a.x = xLocation;
	a.y = s.y + s.height + distanceBetweenTwoRectangles;
	a.width = 35;
	a.height = 35;
	DrawButton(&a, 5, &c, a.x + 11, a.y + 10, 18, "A", "Move left");

	Rectangle d;
	d.x = xLocation;
	d.y = a.y + a.height + distanceBetweenTwoRectangles;
	d.width = 35;
	d.height = 35;
	DrawButton(&d, 5, &c, d.x + 11, d.y + 10, 18, "D", "Move right");

	Rectangle backButton;
	backButton.x = 50;
	backButton.y = GetScreenHeight() - 90;
	backButton.width = 130;
	backButton.height = 40;
	DrawButton(&backButton, 5, &c, backButton.x + 10, backButton.y + 12, 18, "Back to menu");
}

void StartMenu::HandleStartMenu()
{
	if (_PressedButton == StartMenuButtonPressed::MAIN_MANU)
	{
		CheckIfWeClickStartButton();
		CheckIfWeClickControlsButton();
	}
	else if (_PressedButton == StartMenuButtonPressed::CONTROLS_BUTTON)
	{
		CHeckIfWeClickBackButton();
	}

	Draw();
}

void StartMenu::Draw() 
{
	if (_PressedButton == StartMenuButtonPressed::MAIN_MANU) {
		DrawStartButton();
		DrawControlsButton();
	}
	else if (_PressedButton == StartMenuButtonPressed::CONTROLS_BUTTON)
	{
		DrawControlsMenu();
	}
}

void StartMenu::DrawMoveDescription()
{
	DrawRectangle(GetScreenWidth() / 2 - 30, (GetScreenHeight() / 2) + 7, 20, 6, BLACK);
}