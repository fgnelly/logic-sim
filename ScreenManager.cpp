#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = NULL;

ScreenManager* ScreenManager::Instance()
{
	if (sInstance == NULL)
		sInstance = new ScreenManager();

	return sInstance;
}

void ScreenManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

ScreenManager::ScreenManager()
{

	mInput = InputManager::Instance();

	mStartScreen = new StartScreen();
	mEditorScreen = new EditorScreen();
}

ScreenManager::~ScreenManager()
{
	mInput = NULL;

	delete mStartScreen;
	mStartScreen = NULL;

	delete mEditorScreen;
	mEditorScreen = NULL;
}

void ScreenManager::Update()
{
	switch (mCurrentScreen)
	{
	case start:

		mStartScreen->Update();
		if (mStartScreen->SelectedMode() == 1) //add a function to startscreen that tells whether any option in menu was pressed, if so switch to see which screen to activate
		{
			mCurrentScreen = editor;
			mStartScreen->ChangeSelectedMode(-1);
			//mCurrentScreen = play;
			//mStartScreen->ResetAnimation();
			//mStartScreen->StartNewGame();
		}
		break;

	case editor:

		/*mPlayScreen->Update();
		if (mPlayScreen->GameOver())
		{
			mCurrentScreen = start;
		}*/

		mEditorScreen->Update();
		if (mInput->KeyPressed(sf::Keyboard::Return))
		{
			mCurrentScreen = start;
		}

		break;
	}
}

void ScreenManager::Render()
{

	switch (mCurrentScreen)
	{
	case start:

		mStartScreen->Render();
		break;
	case editor:

		mEditorScreen->Render();
		break;
	}
}