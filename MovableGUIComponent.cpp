#include "MovableGUIComponent.h"

MovableGUIComponent::MovableGUIComponent(Texture* mTex)
{
	mTexture = *mTex;
	mPickedUp = false;
}

MovableGUIComponent::~MovableGUIComponent()
{
	
}

void MovableGUIComponent::PickUp()
{
	mPickedUp = true;
}

void MovableGUIComponent::Drop()
{
	mPickedUp = false;
}

bool MovableGUIComponent::PickedUp()
{
	return mPickedUp;
}

void MovableGUIComponent::Render()
{
	mTexture.Pos(Pos(world));
	if (mPickedUp == true)
		mTexture.RenderTransparent(150);
	else
		mTexture.Render();
}

void MovableGUIComponent::Update()
{
	
}