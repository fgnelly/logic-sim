#include "EditorScreen.h"
#include <iostream>

EditorScreen::EditorScreen()
{
	mTimer = Timer::Instance();
	mInputMgr = InputManager::Instance();
	mCollisionMgr = CollisionManager::Instance();
	mEditorGUI = EditorGUI::Instance();

	mEditorCanvas = new EditorScreenCanvas();
	mEditorCanvas->Pos(sf::Vector2f(Graphics::Instance()->GetWindowResolution().x / 2, Graphics::Instance()->GetWindowResolution().y / 2));

	mText = new Texture("EDITOR SCREEN", "main.ttf", 40, sf::Color{ 0, 255, 0, 255 });
	mText->Pos(sf::Vector2f(Graphics::Instance()->SCREEN_WIDTH*0.5f, 50.0f));

	mFileManager = new FileManager();

	mMoveCursor = new Texture("move-cursor.png");
	//mText->Scale(sf::Vector2f(5.0f, 2.0f));

	//GAME PLAN: create a background / playground class capable of creating gates and palcing them, zooming them out and moving in any direction 

}

EditorScreen::~EditorScreen()
{
	//delete and NULL all textures and shit here
	delete mText;
	mText = NULL;

	mEditorGUI->Release();

	delete mEditorCanvas;
	mEditorCanvas = NULL;
}

void EditorScreen::Update()
{

	if (mInputMgr->MousePos().x > 180 && mInputMgr->MousePos().y > 140)
	{
		if (mInputMgr->MouseButtonDown(sf::Mouse::Middle))
		{
			mEditorCanvas->Pos(sf::Vector2f(mInputMgr->MousePos()));
			//std::cout << "lol";
		}
		if (mInputMgr->MouseButtonPressed(sf::Mouse::Left) && mEditorGUI->GetChosenGate() != -1)
		{
			if (mEditorCanvas->CheckIfCanPlaceGate(sf::Vector2f(mInputMgr->MousePos())))
			{
				//std::cout << "placed";
				mEditorGUI->AllowPlace(true);
				mEditorCanvas->AddGate(mEditorGUI->GetChosenGate(), sf::Vector2f(mInputMgr->MousePos()));
			}
		}
		else if (mInputMgr->MouseButtonPressed(sf::Mouse::Left) && mEditorGUI->GetActiveCursor() == 3)
		{
			mEditorCanvas->RemoveGate();
		}
	}

	if (mInputMgr->KeyDown(sf::Keyboard::Left))
	{
		mEditorCanvas->AddOffset(-1, 0);
	}
	else if (mInputMgr->KeyDown(sf::Keyboard::Right))
	{
		mEditorCanvas->AddOffset(1, 0);
	}
	else if (mInputMgr->KeyDown(sf::Keyboard::Up))
	{
		mEditorCanvas->AddOffset(0, -1);
	}
	else if (mInputMgr->KeyDown(sf::Keyboard::Down))
	{
		mEditorCanvas->AddOffset(0, 1);
	}

	if (mInputMgr->MouseButtonDown(sf::Mouse::Right))
	{
		mMovingCursor = true;
		mEditorCanvas->AddOffset(mInputMgr->GetMouseOffset().x, mInputMgr->GetMouseOffset().y);
		mMoveCursor->Pos(sf::Vector2f(mInputMgr->MousePos()));
	}
	else
	{
		mMovingCursor = false;
	}

	if (mInputMgr->KeyPressed(sf::Keyboard::F10))
	{
		mEditorCanvas->SetOffset(0, 0);
	}

	if (mInputMgr->KeyPressed(sf::Keyboard::Delete))
	{
		mEditorCanvas->RemoveHightlighted();
	}
	
	mEditorGUI->Update();

	mEditorGUI->AllowPlace(false);
	
	if (mInputMgr->MouseButtonDown(sf::Mouse::Left) && mEditorGUI->GetActiveCursor() == 2) //add a highlighting tool to check here for.
	{
		mEditorCanvas->HighlightColliding();
	}

	if(mEditorGUI->GetChosenGate() == -1 && mEditorGUI->GetActiveCursor() == 1) //for highlighting gates
		mEditorCanvas->UpdateGateClick();

	if (mEditorGUI->GetActiveCursor() == 4 && mInputMgr->MouseButtonPressed(sf::Mouse::Left))
	{
		if (mInputMgr->MousePos().x > 180 && mInputMgr->MousePos().y > 140)
		{
			std::vector<LogicGate*> tempVec = mEditorCanvas->GetGateVector();
			if (tempVec.size() > 0)
			{
				bool foundStared = false;
				LogicGate* whichStarted = NULL;

				for (auto gate : tempVec)
				{
					if (gate->IsConnecting())
					{
						foundStared = true;
						whichStarted = gate;
						break;
					}
				}

				if (foundStared)
				{
					for (auto gate : tempVec)
					{
						if(!gate->IsDestroyed())
						if (mCollisionMgr->getMouseCollisionSideLR(gate->GetTexture()) == CollisionManager::left)
						{
							whichStarted->EndConnection();
							gate->AddConnected(whichStarted);
							whichStarted->ConnectTo(gate);
							mCableVec.push_back(new GateCable(whichStarted, gate));
							mCableVec.back()->SetState(true);
							std::cout << "connecting ended" << std::endl;
							break;
						}
					}
				}
				else
				{
					for (auto gate : tempVec)
					{
						if(!gate->IsDestroyed())
						if (mCollisionMgr->getMouseCollisionSideLR(gate->GetTexture()) == CollisionManager::right)
						{
							gate->StartConnection();
							std::cout << "connecting started" << std::endl;
							break;
						}
					}
				}
			}
		}
	}

	/*for (auto tex = mCableVec.begin(); tex != mCableVec.end();) //updates cables
	{
		if (mCableVec.at(mCableVec.begin() + tex)->RequestsDeletion())
		{
			mCableVec.erase(tex);
			delete tex;
		}
		else
			tex->Update();
	}*/

	for (int i = 0; i < mCableVec.size(); i++)
	{
		if (mCableVec[i]->RequestsDeletion())
		{
			//delete mCableVec[i];
			mCableVec.erase(mCableVec.begin() + i);
			i--;
		}
		else
		{
			mCableVec[i]->Update();
		}
	}

	mEditorCanvas->Update();

	mInputMgr->ResetMouseInput();
	
	//std::cout << "SIZE: " << mCableVec.size() << std::endl;

	//std::cout << mInputMgr->GetMouseOffset().x << " " << mInputMgr->GetMouseOffset().y << "\n";
}

void EditorScreen::Render()
{
	mText->Render();
	mEditorCanvas->Render();

	for (auto tex : mCableVec)
	{
		tex->Render();
	}

	if (mMovingCursor)
		mMoveCursor->Render();
	mEditorGUI->Render();
}