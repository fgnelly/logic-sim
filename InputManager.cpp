#include "InputManager.h"

InputManager* InputManager::sInstance = NULL;

InputManager* InputManager::Instance() {
	if (sInstance == NULL)
		sInstance = new InputManager();

	return sInstance;
}

void InputManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

InputManager::InputManager() {
	mGraphics = Graphics::Instance();
	mMouse = new sf::Mouse();
	mKeyboard = new sf::Keyboard();
	//mEvent = new sf::Event();
}

InputManager::~InputManager()
{
	Graphics::Release();
	mGraphics = NULL;
	delete mMouse;
	mMouse = NULL;
	delete mKeyboard;
	mKeyboard = NULL;

	//delete mEvent;
	//mEvent = NULL;
}

bool InputManager::KeyDown(sf::Keyboard::Key key)
{
	return mKeyboard->isKeyPressed(key);
}

bool InputManager::KeyPressed(sf::Keyboard::Key key)
{
	//this is fucked
	if (mKeyboard->isKeyPressed(key))
	{
		mKeyboardPressed = true;
		mPrevKeyboard = 1;
		mPrevKeyboardKey = key;
	}
	else if (mPrevKeyboard == 0 && !sf::Keyboard::isKeyPressed(key) && mPrevKeyboardKey == key)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;

}

bool InputManager::KeyReleased(sf::Keyboard::Key key)
{
	//this probably doesnt work but whatever since i dont need it
	//if (mPrevKey != NULL && mPrevKey == key && mStateKey != key)
	//{
		//return true;
	//}
	//else
		return false;
}

bool InputManager::IsWindowClosed()
{
	if (mEvent.type == sf::Event::Closed)
		return true;
	else
		return false;
}

bool InputManager::IsWindowResized()
{
	if (mEvent.type == sf::Event::Resized)
		return true;
	else
		return false;
}

sf::Vector2i InputManager::MousePos()
{
	return mMouse->getPosition(*mGraphics->GetRenderWindow());
}

sf::Vector2i InputManager::GetMouseOffset()
{
	return mMouseOffset;
}

void InputManager::UpdateMouseOffset()
{
	mMouseOffset = MousePos() - mPrevMousePos;
}

bool InputManager::MouseButtonDown(sf::Mouse::Button button)
{
	return mMouse->isButtonPressed(button);
}

bool InputManager::MouseButtonPressed(sf::Mouse::Button button) //TODO: FIX THIS PIECE OF SHIT kind of fixed for now.
{
	//this is fucked
	if (mMouse->isButtonPressed(button))
	{
		mMousePressed = true;
		mPrevMouse = 1;
		mPrevMouseButton = button;
	}
	else if (mPrevMouse == 0 && !sf::Mouse::isButtonPressed(button) && mPrevMouseButton == button)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;
}

bool InputManager::MouseButtonReleased(sf::Mouse::Button button)
{
	return false;
}

void InputManager::Update()
{
	//mGraphics->GetRenderWindow()->pollEvent(*mEvent);
	//mResetDone = false;
	mEvent = Graphics::Instance()->GetWindowEvent();
	UpdateMouseOffset();
	mPrevMousePos = MousePos();
}

void InputManager::UpdatePrevInput()
{
	
}

void InputManager::ResetMouseInput()
{
	mMousePressed = false;
	mPrevMouse--;
	if (mPrevMouse < -5)
	{
		mPrevMouse = -1;
	}
	mKeyboardPressed = false;
	mPrevKeyboard--;
	if (mPrevKeyboard < -5)
	{
		mPrevKeyboard = -1;
	}
}