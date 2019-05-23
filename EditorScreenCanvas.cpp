#include "EditorScreenCanvas.h"
#include <math.h>
#include <iostream>

EditorScreenCanvas::EditorScreenCanvas()
{
	mCollisionManager = CollisionManager::Instance();
	mInputMgr = InputManager::Instance();

	mOffset = {0,0};
	mOffsetValue = mOffset;

	for (int i = 0; i < 50; i++)
	{
		mBackLine[i] = new LineTexture(sf::Vector2f(i*70.0f + 5.0f + 210.0f, 30.0f + 140.0f), sf::Vector2f(i*70.0f + 5.0f + 210.0f, 2070.0f + 140.0f), sf::Color::Black);
	}
	for (int i = 0; i < 30; i++)
	{
		mBackLine2[i] = new LineTexture(sf::Vector2f(210.0f, i*70.0f + 35.0f + 140.0f), sf::Vector2f(70.0f * 49 + 10.0f + 210.0f, i*70.0f + 35.0f + 140.0f), sf::Color::Black);
	}

}

EditorScreenCanvas::~EditorScreenCanvas()
{
	for (auto tex : mLogicGateVec)
	{
		if (tex != NULL)
		{
			delete tex;
			tex = NULL;
		}
	}
	mLogicGateVec.empty();
}

void EditorScreenCanvas::ChangeBackgroundType(BACKGROUND_TYPE bt)
{
	mBackgroundType = bt;
}

void EditorScreenCanvas::ZoomIn(float val)
{
	//scale -= val;
}

void EditorScreenCanvas::ZoomOut(float val)
{
	//scale += val
}

void EditorScreenCanvas::AddGate(int gateType, sf::Vector2f position)
{
	mLogicGateVec.push_back(new LogicGate(gateType, position, mOffsetValue)); //TODO: add passing a value of offset to new LogicGate
	//mLogicGateVec.back()->ChangeDirection(LogicGate::west);
	//mouse position needs to be adjusted to canvas scale
}

void EditorScreenCanvas::UpdateOffset()
{
	for (auto tex : mLogicGateVec)
	{
		tex->Pos(sf::Vector2f(tex->Pos(world).x + mOffset.x, tex->Pos(world).y + mOffset.y));
	}
	for (auto tex : mBackLine)
	{
		tex->MoveVector(sf::Vector2f(mOffset.x, mOffset.y));
	}
	for (auto tex : mBackLine2)
	{
		tex->MoveVector(sf::Vector2f(mOffset.x, mOffset.y));
	}
	//also add updating offset to gates here
}

void EditorScreenCanvas::UpdateGateClick()
{
	if (mInputMgr->MousePos().x > 180 && mInputMgr->MousePos().y > 140)
	{
		if (mInputMgr->MouseButtonPressed(sf::Mouse::Left))
		{
			for (auto tex : mLogicGateVec)
			{
				if (mCollisionManager->checkMouseCollision(tex->GetTexture()))
				{
					//std::cout << "gate highlighted";
					tex->ToggleHightlight();
				}
			}
		}
	}
}

void EditorScreenCanvas::AddOffset(int x, int y)
{
	mOffset = sf::Vector2i(mOffset.x + x, mOffset.y + y);
	mOffsetValue += mOffset;
	if (mOffsetValue.x > 187)
	{
		//mOffsetValue.x = 187;
		//mOffset.x = 0;
	}
	if (mOffsetValue.y > 75)
	{
		//mOffsetValue.y = 75;
		//mOffset.y = 0;
	}
	/*if (mBackLine[0]->GetOrigin().x <= 185.0f)
	{
		mBackLine[0]->SetOrigin(sf::Vector2f(mBackLine[0]->GetOrigin().x - mOffset.x, mBackLine[0]->GetOrigin().y));
		mOffsetValue.x -= mOffset.x;
		mOffset.x = 0;
	}*/
	UpdateOffset();
	mOffset = sf::Vector2i(0, 0);
	//std::cout << mOffsetValue.x << " " << mOffsetValue.y << "\n";
}

sf::Vector2i EditorScreenCanvas::GetOffsetValue()
{
	return mOffsetValue;
}

void EditorScreenCanvas::SetOffset(int x, int y)
{
	AddOffset(-mOffsetValue.x + x, -mOffsetValue.y + y);
	mOffsetValue = sf::Vector2i(x, y);
}

bool EditorScreenCanvas::CheckIfCanPlaceGate(sf::Vector2f position)
{
	//position.x = position.x - 180.0f - fmod(mOffsetValue.x, 70.0f) - mOffsetValue.x;
	//position.y = position.y - 140.0f - fmod(mOffsetValue.y, 70.0f) - mOffsetValue.y;
	//sf::Vector2i GridPos = TranslateGlobalToGrid(position);
	if (mLogicGateVec.size() == 0)
	{
		return true;
	}
	else
	{
		/*for (auto tex : mLogicGateVec)
		{
			if (tex->GetGridPos().x == GridPos.x && tex->GetGridPos().y == GridPos.y)
			{
				std::cout << "FOUND COLLISION: " << tex->GetGridPos().x << " == " << GridPos.x << "\n";
				return false;
			}
		}*/
		for (auto tex : mLogicGateVec) //taken to the next level lol
		{
			if(!tex->IsDestroyed())
			if (mInputMgr->MousePos().x >= tex->Pos(world).x)
			{
				if (mInputMgr->MousePos().y >= tex->Pos(world).y)
				{
					if (mInputMgr->MousePos().y - tex->Pos(world).y <= 35.0f && mInputMgr->MousePos().x - tex->Pos(world).x <= 35.0f)
					{
						//std::cout << "found";
						return false;
					}
				}
				else
				{
					if (tex->Pos(world).y - mInputMgr->MousePos().y <= 35.0f && mInputMgr->MousePos().x - tex->Pos(world).x <= 35.0f)
					{
						//std::cout << "found";
						return false;
					}
				}
			}
			else
			{
				if (mInputMgr->MousePos().y < tex->Pos(world).y)
				{
					if (tex->Pos(world).y - mInputMgr->MousePos().y <= 35.0f && tex->Pos(world).x - mInputMgr->MousePos().x <= 35.0f)
					{
						//std::cout << "found";
						return false;
					}
				}
				else
				{
					if (mInputMgr->MousePos().y - tex->Pos(world).y <= 35.0f && tex->Pos(world).x - mInputMgr->MousePos().x <= 35.0f)
					{
						//std::cout << "found";
						return false;
					}
				}
			}
		}
		return true;
	}
}

void EditorScreenCanvas::RemoveGate()
{
	for (int i = 0; i < mLogicGateVec.size(); i++)
	{
		if (mCollisionManager->checkMouseCollision(mLogicGateVec[i]->GetTexture()))
		{
			//delete mLogicGateVec[i];
			//mLogicGateVec[i] = NULL;
			//mLogicGateVec.erase(mLogicGateVec.begin() + i);
			if (!mLogicGateVec[i]->IsDestroyed())
			{
				std::cout << "Destroying gate no: " << i << std::endl;
				mLogicGateVec[i]->Destroy();
			}
			//i--;
		}
	}
	//search which gate collides with cursor or which are highlighted and remove them.
}

void EditorScreenCanvas::HighlightColliding()
{
	for (auto tex : mLogicGateVec)
	{
		if (mCollisionManager->checkMouseCollision(tex->GetTexture()))
		{
			if(!tex->IsDestroyed())
				tex->HightlightGate(true);
		}
	}
}

void EditorScreenCanvas::RemoveHightlighted()
{
	if (mInputMgr->MousePos().x > 180 && mInputMgr->MousePos().y > 140)
	{
		for (int i = 0; i < mLogicGateVec.size(); i++)
		{
			if (mLogicGateVec[i]->IsHightlighted() && !mLogicGateVec[i]->IsDestroyed())
			{
				mLogicGateVec[i]->Destroy();
				//mLogicGateVec.erase(mLogicGateVec.begin() + i);
				//i--;
			}
		}
	}
}

std::vector<LogicGate*> EditorScreenCanvas::GetGateVector()
{
	return mLogicGateVec;
}

void EditorScreenCanvas::Update()
{
	//loop through gates and update them and their connections
	
	/*if (mInputMgr->KeyPressed(sf::Keyboard::F11))
	{
		mGateCable = new GateCable(mLogicGateVec[0], mLogicGateVec[1]);
		mGateCable->SetState(true);
		activeLOL = true;
		mGateCable->Update();
	}*/

	for (int i = 0; i < mLogicGateVec.size(); i++)
	{
		if (mLogicGateVec[i]->RequestsDeletion())
		{
			delete mLogicGateVec[i];
			mLogicGateVec.erase(mLogicGateVec.begin() + i);
			std::cout << "usuwam mLogicGateVec[" << i << "]\n";
		}
	}
	
	//std::cout << "LOGIC SIZE: " << mLogicGateVec.size() << std::endl;

	for (auto tex : mLogicGateVec)
	{
		if(!tex->IsDestroyed())
			tex->Update();
	}

}

void EditorScreenCanvas::Render()
{
	//loop through gates and render them
	for (auto tex : mLogicGateVec)
	{
		if (!tex->IsDestroyed())
		{
			tex->Render();
		}
	}
	for (auto tex : mBackLine)
	{
		tex->Render();
	}
	for (auto tex : mBackLine2)
	{
		tex->Render();
	}
}