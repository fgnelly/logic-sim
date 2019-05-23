#ifndef _GATECABLE_H
#define _GATECABLE_H
#include "LineTexture.h"
#include "LogicGate.h"

class GateCable : public Entity {

private:

	LogicGate* mConnectingFrom; //pointer to the source gate texture
	LogicGate* mConnectingTo; //pointer to the destination gate texture

	bool mActive = false; //dependent of output state of "mConnectingFrom" gate

	LineTexture* mLineTexture;

	bool mCableExists = false;

	bool mRequestsDeletion = false;

public:

	GateCable();
	GateCable(LogicGate* connectFrom, LogicGate* connectTo);

	~GateCable();

	void ConnectTo(LogicGate* connectTo);

	void SetState(bool active);

	bool GetState(); //returns the state

	void RequestDeletion();
	bool RequestsDeletion();

	void Update();
	void Render();

};

#endif