#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H
#include "Graphics.h"

class InputManager {

private:
	static InputManager* sInstance;

	Graphics* mGraphics;

	sf::Mouse* mMouse;
	sf::Keyboard* mKeyboard;
	sf::Event mEvent;

	bool mKeyboardPressed;
	bool mMousePressed;

	sf::Vector2i mPrevMousePos = { 0,0 };
	sf::Vector2i mMouseOffset = { 0, 0};

	int mPrevMouse = -1;
	sf::Mouse::Button mPrevMouseButton;

	int mPrevKeyboard = -1;
	sf::Keyboard::Key mPrevKeyboardKey;

public:
	static InputManager* Instance();
	static void Release();

	bool KeyDown(sf::Keyboard::Key scanCode);
	bool KeyPressed(sf::Keyboard::Key scanCode);
	bool KeyReleased(sf::Keyboard::Key scanCode);

	bool IsWindowClosed();
	bool IsWindowResized();

	bool MouseButtonDown(sf::Mouse::Button button);
	bool MouseButtonPressed(sf::Mouse::Button button);
	bool MouseButtonReleased(sf::Mouse::Button button);

	sf::Vector2i MousePos();
	sf::Vector2i GetMouseOffset();
	void UpdateMouseOffset();

	void Update();
	void UpdatePrevInput();
	void ResetMouseInput();

private:

	InputManager();
	~InputManager();

};

#endif