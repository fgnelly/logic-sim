#ifndef _PROGRAMMANAGER_H
#define _PROGRAMMANAGER_H
#include "ScreenManager.h"

class ProgramManager {

private:

	static ProgramManager* sInstance;

	const int FRAME_RATE = 60;

	bool mQuit;
	Graphics* mGraphics;

	Timer* mTimer;
	InputManager* mInputMgr;

	ScreenManager* mScreenMgr;

	sf::Event mEvents;

public:

	static ProgramManager* Instance();
	static void Release();

	void Run();

private:

	ProgramManager();
	~ProgramManager();

	void EarlyUpdate();
	void Update();
	void LateUpdate();

	void Render();

};

#endif