#include "Snake.h"
#include <iostream>

Snake::Snake(float XLocation, float YLocation, float width, float hight)
{
	Reset(XLocation, YLocation, width, hight);
};

void Snake::Reset(float newXLocation, float newYLocation, float newWidth, float newHight)
{
	_HeadXLastLocation = newXLocation;
	_HeadYLastLocation = newYLocation;
	_Width = newWidth;
	_Hight = newHight;
	SnakeColor = { 43, 51, 24, 255 };
	LastInput = Input::NO_PRESS;

	IsAlive = true;

	if (!body.empty())
	{
		body.clear();
	}

	body.push_back(std::pair<float, float>(_HeadXLastLocation, _HeadYLastLocation));
}


void Snake::Draw() 
{

	for (size_t i = 1; i < body.size(); i++)
	{
		DrawRectangle(body[i].first, body[i].second, _Width, _Hight, SnakeColor);
	}

	DrawRectangle(body[0].first, body[0].second, _Width, _Hight, BLACK);
}

void Snake::Grow() 
{
	body.push_back(std::pair<float, float>(_LastTailXLocation, _LastTailYLocation));
}

bool Snake::CheckIfWeHitPowerUp(float PowerUpLocationX, float PowerUpLocationY, float PowerUpRadius)
{
	Vector2 powerUpLocation;

	powerUpLocation.x = PowerUpLocationX;
	powerUpLocation.y = PowerUpLocationY;

	Rectangle self = {_HeadXLastLocation, _HeadYLastLocation, _Width, _Hight};

	return CheckCollisionCircleRec(powerUpLocation, PowerUpRadius, self);
}

void Snake::MoveHead(const Input& currentMove) 
{
	switch (currentMove)
	{
	case Input::UP:

		if (LastInput == Input::DOWN)
		{
			body[0].second += _Hight;
			break;
		}

		body[0].second -= _Hight;
		LastInput = Input::UP;

		break;
	case Input::DOWN:

		if (LastInput == Input::UP)
		{
			body[0].second -= _Hight;
			break;
		}

		body[0].second += _Hight;
		LastInput = Input::DOWN;

		break;
	case Input::LEFT:

		if (LastInput == Input::RIGHT)
		{
			body[0].first += _Hight;
			break;
		}

		body[0].first -= _Hight;
		LastInput = Input::LEFT;

		break;
	case Input::RIGHT:

		if (LastInput == Input::LEFT)
		{
			body[0].first -= _Hight;
			break;
		}

		body[0].first += _Hight;
		LastInput = Input::RIGHT;

		break;
	default:
		break;
	}
}

void Snake::MoveBody() 
{
	std::pair<float, float> previos(_HeadXLastLocation, _HeadYLastLocation);

	for (size_t i = 1; i < body.size(); i++)
	{
		float xCurr = body[i].first;
		float yCurr = body[i].second;

		body[i].first = previos.first; // +nextPosX;
		body[i].second = previos.second; // +nextPosY;

		previos.first = xCurr;
		previos.second = yCurr;
	}

	_LastTailXLocation = previos.first;
	_LastTailYLocation = previos.second;

	_HeadXLastLocation = body[0].first;
	_HeadYLastLocation = body[0].second;
}

void Snake::Move(const Input& currentMove) 
{
	if (!IsAlive)
	{
		return;
	}

	MoveHead(currentMove);

	/*if (CheckIfIsOutsideBorder())
	{
		
	}*/

	HandleBorder();

	MoveBody();

	if (CheckIfWeHitOurBody())
	{
		IsAlive = false;
	}
}

bool Snake::CheckIfWeHitOurBody() 
{
	for (size_t i = 2; i < body.size(); i++)
	{
		Rectangle head = {_HeadXLastLocation, _HeadYLastLocation, _Width, _Hight };
		Rectangle bodyPart = {body[i].first, body[i].second, _Width, _Hight};

		if (CheckCollisionRecs(head, bodyPart))
		{
			return true;
		}
	}

	return false;
}

bool Snake::CheckIfIsOutsideBorder() 
{
	if (body[0].first < (GetScreenWidth() * 0.15) + 10)
	{
		return true;
	}

	if (body[0].first > (GetScreenWidth() * 0.85) - _Width)
	{
		return true;
	}

	if (body[0].second < (GetScreenHeight() * 0.1) + 10)
	{
		return true;
	}

	if (body[0].second > (GetScreenHeight() * 0.8) - _Hight)
	{
		return true;
	}

	return false;
}

void Snake::HandleBorder()
{
	/*std::cout << "Befor XLocSnake: " << body[0].first << '\n';
	std::cout << "Befor YLocSnake: " << body[0].second << '\n';
	std::cout << "X Param Up: " << (GetScreenWidth() * 0.15) + 10 << '\n';*/


	if (body[0].first < (GetScreenWidth() * 0.12))
	{
		body[0].first = (GetScreenWidth() * 0.88) - _Width;
	}

	if (body[0].first > (GetScreenWidth() * 0.88) - _Width)
	{
		body[0].first = (GetScreenWidth() * 0.12);
	}

	if (body[0].second < (GetScreenHeight() * 0.12))
	{
		body[0].second = (GetScreenHeight() * 0.88) - _Hight;
	}

	if (body[0].second > (GetScreenHeight() * 0.88) - _Hight)
	{
		body[0].second = (GetScreenHeight() * 0.12);
	}

	/*std::cout << "After XLocSnake: " << body[0].first << '\n';
	std::cout << "After YLocSnake: " << body[0].second << '\n';*/
};

void Snake::SetHeadXLocation(float location)
{
	_HeadXLastLocation = location;
};

void Snake::SetHeadYLocation(float location)
{
	_HeadYLastLocation = location;
};