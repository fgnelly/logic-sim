#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <SFML/Graphics.hpp>

class Graphics
{
public:

	static int const SCREEN_WIDTH = 1000;
	static const int SCREEN_HEIGHT = 1000;
	const char* WINDOW_TITLE = "Demo";
	const sf::Color WINDOW_COLOR = sf::Color::White;

private:

	static Graphics* sInstance;
	static bool sInitialized;

	sf::RenderWindow* mWindow;
	sf::RenderTexture* mRenderer;

	sf::Event mEvents;

public:

	static Graphics* Instance();
	static void Release();
	static bool Initalized();

	void ClearBackBuffer();

	sf::Window* GetRenderWindow();
	void AdaptToNewResolution();

	sf::Texture* LoadTexture(std::string filename);
	sf::Text* CreateTextTexture(sf::Font* font, std::string text, int size, sf::Color color);
	void DrawTexture(sf::Texture* tex, float x, float y, sf::Vector2f scale, float rot);
	void DrawTextTexture(sf::Text*, float x, float y, sf::Vector2f scale);
	void DrawTextureTransparent(sf::Texture* tex, float x, float y, sf::Vector2f scale, int transparency);
	void DrawVertexLine(sf::Vertex* line1, sf::Vertex* line2, sf::Color color);
	void DrawRectangleTexture(sf::RectangleShape* rect, float x, float y);
	sf::Vector2u GetWindowResolution();
	sf::Event GetWindowEvent();

	void Render();

private:

	Graphics();
	~Graphics();

	bool Init();

};

#endif