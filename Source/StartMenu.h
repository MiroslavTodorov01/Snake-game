#ifndef START_MENU_H
#define START_MENU_H

#include "Enums.h"

class StartMenu 
{
public:
	StartMenu();
	~StartMenu();

	void HandleStartMenu();
	bool CheckIfWeClickStartButton();
	bool CheckIfWeClickControlsButton();
	bool CHeckIfWeClickBackButton();
	void Draw();

	inline StartMenuButtonPressed GetPressedButton() const { return _PressedButton; };

private:

	int* _StartButtonPixelsLocation;	// holding start and end pixel location for the button. First two are start width and end width, second two are start hight and end hight locations
	int* _ControlsButtonPixelLocation;	// 
	int* _BackButtonPixelLocation;		//

	StartMenuButtonPressed _PressedButton;

	void DrawStartButton();
	void DrawControlsButton();
	void DrawControlsMenu();
	void DrawButton(class Rectangle* rec, int lineThick, class Color* c, int textXLocation, int textYLocation, int font, const char* key, const char* description);
	bool CheckIfWeAreInsideBox(int MouseX, int MouseY, int WidthPixelStart, int WidthPixelEnd, int HightPixelStart, int HightPixelEnd);
	void DrawMoveDescription();
};

#endif // !START_MENU_H