#include "ThickLineTexture.h"

ThickLineTexture::ThickLineTexture()
{
	
}

ThickLineTexture::ThickLineTexture(ThickLineTexture::DIRECTION direction, float length, float thickness, sf::Color color)
{
	mGraphics = Graphics::Instance();

	mDirection = direction;

	mColor = color;

	switch (direction)
	{
		case horizontal:
			mLength = length;
			mThickness = thickness;
			break;
		case vertical:
			mLength = thickness;
			mThickness = length;
			break;
	}
	
	mRectangle = new sf::RectangleShape(sf::Vector2f(mLength, mThickness));
	mRectangle->setFillColor(mColor);

}

ThickLineTexture::~ThickLineTexture()
{

}

void ThickLineTexture::SetThickness(float thick)
{
	if (mDirection == horizontal)
		mThickness = thick;
	else if (mDirection == vertical)
		mLength = thick;
}

void ThickLineTexture::SetLength(float len)
{
	if (mDirection == horizontal)
		mLength = len;
	else if (mDirection == vertical)
		mThickness = len;
}

float ThickLineTexture::GetThickness()
{
	if (mDirection == horizontal)
		return mThickness;
	else if (mDirection == vertical)
		return mLength;
}

float ThickLineTexture::GetLength()
{
	if (mDirection == horizontal)
		return mLength;
	else if (mDirection == vertical)
		return mThickness;
}

void ThickLineTexture::SetColor(sf::Color col)
{
	mColor = col;
	mRectangle->setFillColor(col);
}

void ThickLineTexture::Update()
{

}

void ThickLineTexture::Render()
{
	sf::Vector2f pos = Pos(world);
	mGraphics->DrawRectangleTexture(mRectangle, pos.x - mLength / 2, pos.y - mThickness / 2);
}