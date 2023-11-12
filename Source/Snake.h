#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "Enums.h"
#include "raylib.h"

class Snake 
{
public:
	Snake(float XLocation, float YLocation, float width, float hight);
	~Snake() = default;

	void Move(const Input& currentMove);
	void Grow();
	bool CheckIfWeHitPowerUp(float PowerUpLocationX, float PowerUpLocationY, float Radius);
	void Reset(float newXLocation, float newYLocation, float newWidth, float newHight);

	void Draw();
	void HandleBorder(); // return true if is outside, false if is not

	void SetHeadXLocation(float location);
	void SetHeadYLocation(float location);

	inline float GetHeadXLastLocation() const { return _HeadXLastLocation; };
	inline float GetHeadYLastLocation() const { return _HeadYLastLocation; };
	inline float GetLastTailXLocation() const { return _LastTailXLocation; };
	inline float GetLastTailYLocation() const { return _LastTailYLocation; };
	inline bool GetIsAlive() const { return IsAlive; };

private:
	float _HeadXLastLocation;
	float _HeadYLastLocation;
	float _LastTailXLocation;
	float _LastTailYLocation;
	float _Width;
	float _Hight;

	Input LastInput;
	Color SnakeColor;
	bool IsAlive;

	std::vector<std::pair<float, float>> body;

	void MoveHead(const Input& currentMove);
	void MoveBody();
	bool CheckIfWeHitOurBody();
	bool CheckIfIsOutsideBorder();
};

#endif // !SNAKE_H