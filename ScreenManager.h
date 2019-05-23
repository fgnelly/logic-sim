#ifndef _SCREENMANAGER_H
#define _SCREENMANAGER_H
#include "StartScreen.h"
#include "EditorScreen.h"

class ScreenManager {
private:

	enum SCREENS {start, editor};

	static ScreenManager* sInstance;

	InputManager* mInput;
	StartScreen* mStartScreen;
	EditorScreen* mEditorScreen;

	SCREENS mCurrentScreen = start;

public:

	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

private:

	ScreenManager();
	~ScreenManager();
};

#endif