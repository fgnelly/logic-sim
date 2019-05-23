#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H
#include "Timer.h"
#include "CollisionManager.h"

class StartScreen : public Entity {

private:

	Timer* mTimer;
	InputManager* mInputMgr;
	CollisionManager* mCollisionMgr;

	int mSelectedMode;

	Texture* mLogo;

	Texture* mNewFile;
	Texture* mNewFileActive;

	Texture* mLoadFile;
	Texture* mLoadFileActive;

public:

	StartScreen();
	~StartScreen();

	int SelectedMode();

	void ChangeSelectedMode(int change);
	void AdaptToNewRes();

	void Update();
	void Render();

};

#endif