#ifndef _LOGICGATE_H
#define _LOGICGATE_H
#include "Texture.h"

class LogicGate : public Entity {

public:

	enum GATE_HEADING {north = 0, south = 1, east = 2, west = 3};

private:

	GATE_HEADING mHeadingDirection = east; //default is east, so right

	std::string mGateTypes[9] = {"not", "and", "or", "nor", "xor", "nand", "xnor", "input", "output"};

	std::string mGateType;

	sf::Vector2i mGridPos; //canvas is made of whole numbered grid where center is 0,0

	LogicGate* mConnections[2]; //pointers to gates that are connected to the gate

	LogicGate* mConnectedTo;
	Texture* mTexture;
	Texture* mHighlightTexture; //blue texture for displaying highlight

	int mOutputState; //1 or 0 (dependent on gate type and incoming connections)

	bool mHighlighted = false;

	bool mConnectingStared = false;

	bool mDeleted = false;

	bool mRequestDeletion = false; //to let the program know that it's safe to delete the object

	//GateCable* mGateCable;

public:

	LogicGate();
	LogicGate(int type, sf::Vector2f position, sf::Vector2i offset);
	~LogicGate();

	void ConnectTo(LogicGate* gate);

	void Disconnect(); //remove connection to gate

	void ChangeDirection(GATE_HEADING gh);

	void HightlightGate(bool b);
	bool IsHightlighted();
	void ToggleHightlight();

	int GetOutputState();
	Texture* GetTexture();

	sf::Vector2i GetGridPos();

	void StartConnection();

	bool IsConnecting();

	void EndConnection();

	void AddConnected(LogicGate* connected);

	void RemoveConnection(LogicGate* connection);

	void Destroy();
	bool IsDestroyed();

	void RequestDeletion();
	bool RequestsDeletion();

	void Update();
	void Render();

};

#endif