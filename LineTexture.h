#ifndef _LINETEXTURE_H
#define _LINETEXTURE_H
#include "Graphics.h"
#include "Entity.h"

class LineTexture : public Entity {

protected:

	sf::Vertex* mLineVertex[2];

	sf::Color mColor;

	Graphics* mGraphics;

public:

	LineTexture();
	LineTexture(sf::Vector2f startPos, sf::Vector2f endPos, sf::Color color);
	~LineTexture();

	void SetOrigin(sf::Vector2f newOriginPos);
	void SetDestination(sf::Vector2f newDestPos);

	sf::Vector2f GetOrigin();
	sf::Vector2f GetDestination();

	void MoveVector(sf::Vector2f moveVector);

	void SetColor(sf::Color color);

	virtual void Render();

};

#endif