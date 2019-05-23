#include "GateCable.h"
#include <iostream>

GateCable::GateCable()
{

}

GateCable::GateCable(LogicGate* connectFrom, LogicGate* connectTo)
{
	mConnectingFrom = connectFrom;

	mConnectingTo = connectTo;
	
	mLineTexture = new LineTexture(connectFrom->GetTexture()->Pos(world), connectTo->GetTexture()->Pos(world), sf::Color::Black);

	mCableExists = true;

}

GateCable::~GateCable()
{
	delete mConnectingTo;
	mConnectingFrom = NULL;

	delete mConnectingFrom;
	mConnectingTo = NULL;

	delete mLineTexture;
	mLineTexture = NULL;

	std::cout << "Cable safely deleted." << std::endl;
}

void GateCable::ConnectTo(LogicGate* ct)
{
	mConnectingTo = ct;
	//update the positions here
	mLineTexture->SetDestination(ct->GetTexture()->Pos(world));
}

void GateCable::SetState(bool b)
{
	mActive = b;
}

bool GateCable::GetState()
{
	return mActive;
}

bool GateCable::RequestsDeletion()
{
	return mRequestsDeletion;
}

void GateCable::RequestDeletion()
{
	mRequestsDeletion = true;
}

void GateCable::Update()
{
	if (mActive)
		mLineTexture->SetColor(sf::Color::Green);
	else
		mLineTexture->SetColor(sf::Color::Black);

	//std::cout << mConnectingFrom->GetTexture()->Pos(world).x;

	if (mConnectingFrom->IsDestroyed() == true || mConnectingTo->IsDestroyed() == true)
	{
		mCableExists = false;
		RequestDeletion(); //let the program know, the cable object is safe to delete
		if (mConnectingFrom->IsDestroyed())
		{
			mConnectingFrom->RequestDeletion();
			mConnectingTo->RemoveConnection(mConnectingFrom);
		}
		else if (mConnectingTo->IsDestroyed())
		{
			mConnectingTo->RequestDeletion();
			mConnectingFrom->RemoveConnection(mConnectingTo);
		}
	}

}

void GateCable::Render()
{
	if(mCableExists)
	{
		mLineTexture->SetDestination(mConnectingTo->GetTexture()->Pos(world));
		mLineTexture->SetOrigin(mConnectingFrom->GetTexture()->Pos(world));
		mLineTexture->Render();
	}
}