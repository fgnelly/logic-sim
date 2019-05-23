#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H
#include "Graphics.h"
#include <map>

class AssetManager {
private:

	static AssetManager* sInstance;

	std::map <std::string, sf::Texture*> mTextures;
	std::map <std::string, sf::Text*> mText;
	std::map <std::string, sf::Font*> mFonts;
	//add music here later

public:

	static AssetManager* Instance();
	static void Release();

	sf::Texture* GetTexture(std::string filename);
	sf::Text* GetText(std::string text, std::string filename, int size, sf::Color color);

	//add music here later

private:

	AssetManager();
	~AssetManager();

	sf::Font* GetFont(std::string filename);

};

#endif