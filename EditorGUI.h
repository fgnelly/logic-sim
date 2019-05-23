#ifndef _EDITORGUI_H
#define _EDITORGUI_H

#include "Texture.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "MovableGUIComponent.h"

class EditorGUI : public Entity {

private:

	static EditorGUI* sInstance;

	int CURRENT_SCREEN_HEIGHT;
	int CURRENT_SCREEN_WIDTH;

	InputManager* mInputMgr;
	CollisionManager* mCollisionManager;

	//put all textures here

	std::string mGateNames[9] = {"not", "and", "or", "nor", "xor", "nand", "xnor", "input", "output"};
	Texture* mGateBackgrounds[9];
	Texture* mGates[9];
	Texture* mGateNameTextures[9];
	MovableGUIComponent* mMovableGates[9];

	Texture* mInputGate;
	Texture* mOutputGate;

	Texture* leftGUITexture;
	Texture* mGUIInventory;
	Texture* mGUILogicOptions;
	Texture* topGUITexture;

	//storing choosen gate to place - picked up.
	int mChosenGate = -1;

	bool mAbleToPlaceGate = false;

	Texture* mLogoTexture;
	Texture* mGuiButtonSpace;

	Texture* mRunTestButton;
	Texture* mRunTestButtonActive;

	Texture* mRunTestButtonText;
	Texture* mRunTestButtonTextActive;

	Texture* mStandardCursorButton;
	Texture* mStandardCursorButtonActive;

	Texture* mHighlightCursorButton;
	Texture* mHighlightCursorButtonActive;

	Texture* mRemoveCursorButton;
	Texture* mRemoveCursorButtonActive;
	Texture* mRemoveCursor;

	Texture* mWiringCursorButton;
	Texture* mWiringCursorButtonActive;

	bool mRunTestActive = false;

	int mActiveCursor = 1;

	void SetActiveCursor(int ac);

public:

	static EditorGUI* Instance();
	static void Release();

	void UpdateCurrentRes();
	//void DealWithButtonAndSuch(); //put all button clicking and dragging here
	void UpdateTexturePositions();
	void AdjustGUIScale();

	void AllowPlace(bool b);

	int GetChosenGate();
	int GetActiveCursor();

	void Update();
	void Render();

private:

	EditorGUI();
	~EditorGUI();

};

#endif