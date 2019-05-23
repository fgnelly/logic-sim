#ifndef _MATHHELPER_H
#define _MATHHELPER_H
#include <math.h>
#include <SFML/Graphics.hpp>

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f

const sf::Vector2f VEC2_ZERO = { 0.0f, 0.0f };
const sf::Vector2f VEC2_ONE = { 1.0f, 1.0f };
const sf::Vector2f VEC2_UP = { 0.0f, 1.0f };
const sf::Vector2f VEC2_RIGHT = { 1.0f, 0.0f };

inline sf::Vector2f RotateVector(const sf::Vector2f& vec, float angle) { //Vector2& does not work
	float radAngle = (float)(angle*DEG_TO_RAD);

	return sf::Vector2f((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}

inline sf::Vector2f CountVectorOffset(const sf::Vector2f& startVec, const sf::Vector2f& endVec)
{
	if (startVec.x > endVec.x && startVec.y > endVec.y)
	{
		return sf::Vector2f(startVec.x - endVec.x, startVec.x - endVec.x);
	}
}

inline sf::Vector2i TranslateGlobalToGrid(const sf::Vector2f& globalPos)
{
	if (fmod(globalPos.x, 70.0f) >= 0.5f)
	{
		if (fmod(globalPos.y, 70.0f) >= 0.5f)
		{
			return sf::Vector2i(static_cast<int>((globalPos.x / 70.0f)+0.5f), static_cast<int>((globalPos.y / 70.0f)+0.5f));
		}
		else if (fmod(globalPos.y, 70.0f) < 0.5f)
		{
			return sf::Vector2i(static_cast<int>((globalPos.x / 70.0f) + 0.5f), static_cast<int>(globalPos.y / 70.0f));
		}
	}
	else if (fmod(globalPos.x, 70.0f) < 0.5f)
	{
		if (fmod(globalPos.y, 70.0f) >= 0.5f)
		{
			return sf::Vector2i(static_cast<int>(globalPos.x / 70.0f), static_cast<int>((globalPos.y / 70.0f) + 0.5f));
		}
		else if (fmod(globalPos.y, 70.0f) < 0.5f)
		{
			return sf::Vector2i(static_cast<int>(globalPos.x / 70.0f), static_cast<int>(globalPos.y / 70.0f));
		}
	}
}

inline sf::Vector2f TranslateGridToGlobal(const sf::Vector2i& gridPos)
{
	return sf::Vector2f((gridPos.x * 70.0f), (gridPos.y * 70.0f));
}

inline sf::Vector2f TranslateGridToGlobalGate(const sf::Vector2i& gridPos)
{
	return sf::Vector2f((gridPos.x * 70.0f) + 35.0f, (gridPos.y * 70.0f) + 35.0f);
}


#endif