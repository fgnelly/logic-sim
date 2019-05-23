#include "Texture.h"

Texture::Texture()
{
	mGraphics = Graphics::Instance();

	mTexType = texture;

	mTex = NULL;

	mHeight = 100;
	mWidth = 100;
}

Texture::Texture(std::string fname)
{
	mGraphics = Graphics::Instance();

	mTexType = texture;

	mTex = AssetManager::Instance()->GetTexture(fname);

	mHeight = mTex->getSize().y;
	mWidth = mTex->getSize().x;

}

Texture::Texture(std::string text, std::string filename, int size, sf::Color color)
{
	mGraphics = Graphics::Instance();

	mTexType = textTex;

	mText = AssetManager::Instance()->GetText(text, filename, size, color);

	mHeight = mText->getLocalBounds().height;
	mWidth = mText->getLocalBounds().width;
}

sf::Vector2i Texture::GetDimentions()
{
	return sf::Vector2i(mWidth, mHeight);
}

Texture::~Texture()
{
	mTex = NULL;
	mText = NULL;
	mGraphics = NULL;
	//TODO
}

void Texture::Render()
{
	sf::Vector2f pos = Pos(world);
	sf::Vector2f scale = Scale(local); //TODO? used to be Scale(world) but then it would strech the child of a texture
	float rotation = Rotation(world);
	if (mTexType == texture)
		mGraphics->DrawTexture(mTex, (pos.x - mWidth / 2), (pos.y - mHeight / 2), scale, rotation);
	else if (mTexType == textTex)
		mGraphics->DrawTextTexture(mText, (pos.x - mWidth / 2), (pos.y - mHeight / 2), scale);
}

void Texture::RenderTransparent(int t)
{
	sf::Vector2f pos = Pos(world);
	sf::Vector2f scale = Scale(local);
	mGraphics->DrawTextureTransparent(mTex, (pos.x - mWidth / 2), (pos.y - mHeight / 2), scale, t);
}
