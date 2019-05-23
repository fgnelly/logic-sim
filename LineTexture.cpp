#include "LineTexture.h"

LineTexture::LineTexture()
{

}

LineTexture::LineTexture(sf::Vector2f originPos, sf::Vector2f destPos, sf::Color color)
{

	mLineVertex[0] = new sf::Vertex(originPos);
	mLineVertex[1] = new sf::Vertex(destPos);

	mColor = color;

	mLineVertex[0]->color = color;
	mLineVertex[1]->color = color;

	mGraphics = Graphics::Instance();

}

LineTexture::~LineTexture()
{

}

void LineTexture::SetOrigin(sf::Vector2f orPos)
{
	mLineVertex[0]->position.x = orPos.x;
	mLineVertex[0]->position.y = orPos.y;
}

void LineTexture::SetDestination(sf::Vector2f destPos)
{
	mLineVertex[1]->position.x = destPos.x;
	mLineVertex[1]->position.y = destPos.y;
}

sf::Vector2f LineTexture::GetOrigin()
{
	return sf::Vector2f(mLineVertex[0]->position.x, mLineVertex[0]->position.y);
}

sf::Vector2f LineTexture::GetDestination()
{
	return sf::Vector2f(mLineVertex[1]->position.x, mLineVertex[1]->position.y);
}

void LineTexture::MoveVector(sf::Vector2f movVec)
{
	mLineVertex[0]->position += movVec;
	mLineVertex[1]->position += movVec;
}

void LineTexture::SetColor(sf::Color color)
{
	mColor = color;
}

void LineTexture::Render()
{
	mGraphics->DrawVertexLine(mLineVertex[0], mLineVertex[1], mColor);
}