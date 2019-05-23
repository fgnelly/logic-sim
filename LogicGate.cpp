#include "LogicGate.h"
#include <iostream>

LogicGate::LogicGate()
{

}

LogicGate::LogicGate(int type, sf::Vector2f position, sf::Vector2i offset)
{
	mGateType = mGateTypes[type];
	mConnectedTo = nullptr;
	//std::cout << "Original: " << position.x << " " << position.y << "\n";
	mTexture = new Texture((std::string)mGateType+".png");
	mHighlightTexture = new Texture("gate-highlight.png");
	mHighlightTexture->Parent(this);
	position.x = position.x - 180.0f - fmod(offset.x, 70.0f);
	position.y = position.y - 140.0f - fmod(offset.y, 70.0f);
	mGridPos = TranslateGlobalToGrid(position);
	//std::cout << "Translated " << position.x << " to: " << mGridPos.x << " and " << position.y << " to: " << mGridPos.y << "\n";
	//std::cout << "FMOD x: " << fmod(offset.x, 35.0f) << "FMOD y: " << fmod(offset.y, 35.0f) << "\n";
	Pos(sf::Vector2f(TranslateGridToGlobal(mGridPos).x + 180.0f + fmod(offset.x, 70.0f), TranslateGridToGlobal(mGridPos).y + 140.0f + fmod(offset.y, 70.0f)));

	//mGateCable = NULL;

}

LogicGate::~LogicGate()
{
	std::cout << "GATE DELETED";
	//delete mTexture;
	//mTexture = NULL;
}

void LogicGate::ConnectTo(LogicGate* gate)
{
	mConnectedTo = gate;
	//mGateCable = new GateCable(this, mConnectedTo);
}

void LogicGate::Disconnect()
{
	mConnectedTo = NULL;
}

void LogicGate::ChangeDirection(GATE_HEADING gh)
{
	mHeadingDirection = gh;
	if (gh == north)
	{
		mTexture->Rotation(270.0f);
	}
	else if (gh == south)
	{
		mTexture->Rotation(90.0f);
	}
	else if (gh == east)
	{
		mTexture->Rotation(0.0f);
	}
	else if (gh == west)
	{
		mTexture->Rotation(180.0f);
	}
	else
	{
		mTexture->Rotation(0.0f);
	}
}

void LogicGate::HightlightGate(bool b)
{
	mHighlighted = b;
}

bool LogicGate::IsHightlighted()
{
	return mHighlighted;
}

void LogicGate::ToggleHightlight()
{
	mHighlighted = !mHighlighted;
}

int LogicGate::GetOutputState()
{
	return mOutputState;
}

Texture* LogicGate::GetTexture()
{
	return mTexture;
}

sf::Vector2i LogicGate::GetGridPos()
{
	return mGridPos;
}

void LogicGate::StartConnection()
{
	mConnectingStared = true;
}

bool LogicGate::IsConnecting()
{
	return mConnectingStared;
}

void LogicGate::EndConnection()
{
	mConnectingStared = false;
}

void LogicGate::AddConnected(LogicGate* connected)
{
	if (mConnections[0] == NULL)
	{
		mConnections[0] = connected;
	}
	else if (mConnections[1] == NULL)
	{
		mConnections[1] = connected;
	}
}

void LogicGate::RemoveConnection(LogicGate* connection)
{
	if (mConnections[0] != NULL && mConnections[0]->GetTexture()->Pos(world).x == connection->GetTexture()->Pos(world).x)
	{
		mConnections[0] = NULL;
	}
	else if (mConnections[1] != NULL && mConnections[1]->GetTexture()->Pos(world).x == connection->GetTexture()->Pos(world).x)
	{
		mConnections[1] = NULL;
	}
}

bool LogicGate::IsDestroyed()
{
	return mDeleted;
}

void LogicGate::Destroy()
{
	mDeleted = true;
	if (mConnections[0] == NULL && mConnections[1] == NULL)
	{
		RequestDeletion();
	}
}

bool LogicGate::RequestsDeletion()
{
	return mRequestDeletion;
}

void LogicGate::RequestDeletion()
{
	mRequestDeletion = true;
}

void LogicGate::Update()
{
	//check if components connected to it exist and if are still connected, check logic for output state, check if is connected to an existing object
	//if (mGateCable != NULL)
		//mGateCable->Update();
	if (mDeleted && !mRequestDeletion)
	{
		if (mConnections[0] == NULL && mConnections[1] == NULL)
		{
			RequestDeletion();
		}
	}
}

void LogicGate::Render()
{
	mTexture->Pos(Pos(world));
	mTexture->Scale(Scale(world));
	mTexture->Render();
	if (mHighlighted)
		mHighlightTexture->Render();
	//if (mGateCable != NULL)
		//mGateCable->Render();
}