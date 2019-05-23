#ifndef _EDITORSCREEN_H
#define _EDITORSCREEN_H
#include "Timer.h"
#include "CollisionManager.h"
#include "EditorGUI.h"
#include "EditorScreenCanvas.h"
#include "GateCable.h"
#include "FileManager.h"

class EditorScreen : public Entity {

private:

	Timer* mTimer;
	InputManager* mInputMgr;
	CollisionManager* mCollisionMgr;
	EditorScreenCanvas* mEditorCanvas;

	Texture* mMoveCursor;
	bool mMovingCursor = false;

	EditorGUI* mEditorGUI;

	Texture* mText;

	std::vector<GateCable*> mCableVec;

	FileManager* mFileManager;

public:

	EditorScreen();
	~EditorScreen();

	void Render();
	void Update();

};

#endif