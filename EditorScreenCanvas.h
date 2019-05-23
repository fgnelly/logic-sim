#ifndef _EDITORSCREENCANVAS_H
#define _EDITORSCREENCANVAS_H
#include "LogicGate.h"
#include "CollisionManager.h"
#include "LineTexture.h"
#include "GateCable.h"

class EditorScreenCanvas : public Entity {

private:

	enum BACKGROUND_TYPE {checked, plain};
	BACKGROUND_TYPE mBackgroundType = plain;

	CollisionManager* mCollisionManager;
	InputManager* mInputMgr;

	std::vector<LogicGate*> mLogicGateVec;

	LineTexture* mBackLine[50];
	LineTexture* mBackLine2[30];

	sf::Vector2i mOffset; //this holds the value of offset to update
	sf::Vector2i mOffsetValue; //this holds the value of final offset (summed)

public:

	EditorScreenCanvas();
	~EditorScreenCanvas();

	void ChangeBackgroundType(BACKGROUND_TYPE bt);

	void ZoomIn(float val);
	void ZoomOut(float val);

	void AddGate(int gateType, sf::Vector2f position);

	void AddOffset(int x, int y);
	sf::Vector2i GetOffsetValue();

	void SetOffset(int x, int y);

	void UpdateOffset();

	void UpdateGateClick();

	bool CheckIfCanPlaceGate(sf::Vector2f position);

	void RemoveGate(); //gonna change that to checking for collisions with mouse 

	void HighlightColliding(); //for the mass highlighting tool

	void RemoveHightlighted();

	std::vector<LogicGate*> GetGateVector();

	void Update();
	void Render();

};

#endif