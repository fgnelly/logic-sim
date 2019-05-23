#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "Graphics.h"
#include "Entity.h"
#include "AssetManager.h"

class Texture : public Entity {

protected:

	enum TEXTURE_TYPE { texture = 0, textTex = 1};
	TEXTURE_TYPE mTexType;

	sf::Texture* mTex;
	sf::Text* mText;

	sf::Color mColor;

	Graphics* mGraphics;

	int mWidth;
	int mHeight;

	//bool mClipped;
	//sf::Sprite &mSprite;

public:

	Texture();
	Texture(std::string filename);
	Texture(std::string text, std::string filename, int size, sf::Color color);
	//Texture(float height, float width, sf::Color color); //MAYBE ADD RECTANGLES FOR GUI
	~Texture();

	sf::Vector2i GetDimentions();

	virtual void Render();
	virtual void RenderTransparent(int t);
};

#endif