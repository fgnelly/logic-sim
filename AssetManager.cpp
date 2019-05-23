#include "AssetManager.h"

AssetManager* AssetManager::sInstance = NULL;

AssetManager* AssetManager::Instance()
{
	if (sInstance == NULL)
		sInstance = new AssetManager();

	return sInstance;
}

void AssetManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
	for (auto tex : mTextures)
	{
		if (tex.second != NULL)
		{
			delete tex.second;
			tex.second = NULL;
		}
	}
	mTextures.clear();

	for (auto text : mText)
	{
		if (text.second != NULL)
		{
			delete text.second;
			text.second = NULL;
		}
	}
	mText.clear();

	for (auto font : mFonts)
	{
		if (font.second != NULL)
		{
			delete font.second;
			font.second = NULL;
		}
	}

	//destroy music here
}

sf::Texture* AssetManager::GetTexture(std::string filename)
{
	std::string fullPath = "Assets/" + filename;

	if (mTextures[fullPath] == nullptr)
	{
		mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);
	}

	return mTextures[fullPath];
}

sf::Font* AssetManager::GetFont(std::string filename)
{
	//do some stuff here
	std::string key;
	key.append("Assets/" + filename);
	if (mFonts[key] == nullptr)
	{
		mFonts[key] = new sf::Font();
		mFonts[key]->loadFromFile(key);
	}
	return mFonts[key];
}

sf::Text* AssetManager::GetText(std::string text, std::string filename, int size, sf::Color color)
{
	//do some creating here
	sf::Font* font = GetFont(filename);
	std::string fontKey = text + filename + (char)size + (char)color.r + (char)color.b + (char)color.g;

	if (mText[fontKey] == nullptr)
		mText[fontKey] = Graphics::Instance()->CreateTextTexture(font, text, size, color);

	return mText[fontKey];
}

