#ifndef _THICKLINETEXTURE_H
#define _THICKLINETEXTURE_H
#include "Graphics.h"
#include "Entity.h"

class ThickLineTexture : public Entity {

public:

	enum DIRECTION {horizontal = 0, vertical = 1};

protected:

	sf::Color mColor;

	DIRECTION mDirection;

	Graphics* mGraphics;

	float mThickness;
	float mLength;

	sf::RectangleShape* mRectangle;

public:

	ThickLineTexture();
	ThickLineTexture(DIRECTION direction, float length, float thickness, sf::Color color);
	~ThickLineTexture();

	void SetThickness(float thickness);
	void SetLength(float length);

	float GetThickness();
	float GetLength();

	void SetColor(sf::Color col);

	virtual void Update();
	virtual void Render();

};

#endif