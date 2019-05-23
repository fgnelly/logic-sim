#include "EditorGUI.h"

EditorGUI* EditorGUI::sInstance = NULL;

EditorGUI* EditorGUI::Instance()
{
	if (sInstance == nullptr)
		sInstance = new EditorGUI();

	return sInstance;
}

void EditorGUI::Release()
{
	delete sInstance;
	sInstance = NULL;
}

void EditorGUI::UpdateCurrentRes()
{
	CURRENT_SCREEN_HEIGHT = Graphics::Instance()->GetWindowResolution().y;
	CURRENT_SCREEN_WIDTH = Graphics::Instance()->GetWindowResolution().x;

	//std::cout << "curreent res y: " << Graphics::Instance()->GetWindowResolution().y << "\n";

	Pos(sf::Vector2f(CURRENT_SCREEN_WIDTH*0.5f, CURRENT_SCREEN_HEIGHT*0.5f)); //center the gui

}

void EditorGUI::UpdateTexturePositions()
{
	//mText->Pos(sf::Vector2f(CURRENT_SCREEN_WIDTH*0.5f, CURRENT_SCREEN_HEIGHT*0.5f));
}

void EditorGUI::AdjustGUIScale()
{
	leftGUITexture->Scale(sf::Vector2f(1.0f, CURRENT_SCREEN_HEIGHT*1.0f / (leftGUITexture->GetDimentions().y*1.0f)));
	topGUITexture->Scale(sf::Vector2f(CURRENT_SCREEN_WIDTH*1.0f / topGUITexture->GetDimentions().x*1.0f, 1.0f));
	mGuiButtonSpace->Scale(sf::Vector2f(CURRENT_SCREEN_WIDTH *1.0f / mGuiButtonSpace->GetDimentions().x * 1.0f, 1.0f));
	//leftGUIChild->Scale(sf::Vector2f(1.0f, leftGUITexture->Scale(world).y*0.25f));
}

void EditorGUI::AllowPlace(bool b)
{
	mAbleToPlaceGate = b;
}

EditorGUI::EditorGUI()
{
	UpdateCurrentRes();
	//create textures and stuff here, maybe some timer members or graphic or input or whatever

	mInputMgr = InputManager::Instance();
	mCollisionManager = CollisionManager::Instance();

	//generating backgrounds for gate buttons
	int offset = 0;
	for (unsigned int i = 0; i < 9; i++)
	{
		mGateBackgrounds[i] = new Texture("gate-background.png");
		if (i % 2 == 0)
			mGateBackgrounds[i]->Pos(sf::Vector2f(50.0f, 240.0f + 90.0f * offset));
		else
		{
			mGateBackgrounds[i]->Pos(sf::Vector2f(130.0f, 240.0f + 90.0f * offset));
			offset++;
		}
	}

	//placing gate buttons

	offset = 0;
	for (unsigned int i = 0; i < 9; i++)
	{
		mGates[i] = new Texture(mGateNames[i]+".png");
		if (i % 2 == 0)
			mGates[i]->Pos(sf::Vector2f(50.0f, 240.0f + 90.0f * offset));
		else
		{
			mGates[i]->Pos(sf::Vector2f(130.0f, 240.0f + 90.0f * offset));
			offset++;
		}
	}

	//placing gate name textures

	offset = 0;
	for (unsigned int i = 0; i < 9; i++)
	{
		mGateNameTextures[i] = new Texture(mGateNames[i], "main.ttf", 20, sf::Color::Black);
		if (i % 2 == 0)
			mGateNameTextures[i]->Pos(sf::Vector2f(50.0f, 190.0f + 90.0f * offset));
		else
		{
			mGateNameTextures[i]->Pos(sf::Vector2f(130.0f, 190.0f + 90.0f * offset));
			offset++;
		}
	}

	//placing movables on gates

	offset = 0;
	for (unsigned int i = 0; i < 9; i++)
	{
		mMovableGates[i] = new MovableGUIComponent(mGates[i]);
		if (i % 2 == 0)
			mMovableGates[i]->Pos(sf::Vector2f(50.0f, 240.0f + 90.0f * offset));
		else
		{
			mMovableGates[i]->Pos(sf::Vector2f(130.0f, 240.0f + 90.0f * offset));
			offset++;
		}
	}

	//input and output block textures

	leftGUITexture = new Texture("gui-left.png");
	leftGUITexture->Pos(sf::Vector2f(leftGUITexture->GetDimentions().x / 2, leftGUITexture->GetDimentions().y / 2));

	mGUIInventory = new Texture("INVENTORY", "main.ttf", 30, sf::Color::Black);
	mGUIInventory->Pos(sf::Vector2f(leftGUITexture->GetDimentions().x / 2, 150.0f));
	//leftGUIChild->Parent(leftGUITexture);

	mGUILogicOptions = new Texture("LOGIC OPTIONS", "main.ttf", 30, sf::Color::Black);
	mGUILogicOptions->Pos(sf::Vector2f(leftGUITexture->GetDimentions().x / 2, 680.0f));

	topGUITexture = new Texture("gui-top.png");
	topGUITexture->Pos(sf::Vector2f(topGUITexture->GetDimentions().x / 2 + leftGUITexture->GetDimentions().x - 1.0f, topGUITexture->GetDimentions().y / 2));

	mLogoTexture = new Texture("logo.png");
	mLogoTexture->Pos(sf::Vector2f(90.0f, 50.0f));

	mGuiButtonSpace = new Texture("gui-buttons.png");
	mGuiButtonSpace->Pos(sf::Vector2f(mGuiButtonSpace->GetDimentions().x / 2, 125.0f));

	//mRunTestButton = new Texture("RUN TEST", "main.ttf", 30, sf::Color::Black);
	mRunTestButton = new Texture("run.png");
	mRunTestButton->Pos(sf::Vector2f(mRunTestButton->GetDimentions().x / 2 + 179.0f, 125.0f));

	mRunTestButtonText = new Texture("RUN", "main.ttf", 30, sf::Color::Black);
	mRunTestButtonText->Pos(sf::Vector2f(mRunTestButton->GetDimentions().x / 2 + 179.0f + 20.0f, 119.0f));

	mRunTestButtonActive = new Texture("run-active.png");
	mRunTestButtonActive->Pos(sf::Vector2f(mRunTestButton->GetDimentions().x / 2 + 179.0f, 125.0f));

	mRunTestButtonTextActive = new Texture("RUN", "main.ttf", 30, sf::Color::Green);
	mRunTestButtonTextActive->Pos(mRunTestButtonText->Pos(world));

	mStandardCursorButton = new Texture("standard-cursor.png");
	mStandardCursorButton->Pos(sf::Vector2f(mStandardCursorButton->GetDimentions().x / 2 + 179.0f + mRunTestButton->GetDimentions().x, 125.0f));

	mStandardCursorButtonActive = new Texture("standard-cursor-active.png");
	mStandardCursorButtonActive->Pos(mStandardCursorButton->Pos(world));

	mHighlightCursorButton = new Texture("highlight-cursor.png");
	mHighlightCursorButton->Pos(sf::Vector2f(mStandardCursorButton->GetDimentions().x / 2 + 179.0f + mRunTestButton->GetDimentions().x + mStandardCursorButton->GetDimentions().x, 125.0f));

	mHighlightCursorButtonActive = new Texture("highlight-cursor-active.png");
	mHighlightCursorButtonActive->Pos(mHighlightCursorButton->Pos(world));

	mRemoveCursorButton = new Texture("remove-cursor-button.png");
	mRemoveCursorButton->Pos(sf::Vector2f(mStandardCursorButton->GetDimentions().x / 2 + 179.0f + mRunTestButton->GetDimentions().x + mStandardCursorButton->GetDimentions().x + mHighlightCursorButton->GetDimentions().x, 125.0f));
	mRemoveCursorButtonActive = new Texture("remove-cursor-button-active.png");
	mRemoveCursorButtonActive->Pos(mRemoveCursorButton->Pos(world));

	mRemoveCursor = new Texture("remove-cursor.png");

	mWiringCursorButton = new Texture("wiring-cursor.png");
	mWiringCursorButton->Pos(sf::Vector2f(mRemoveCursorButton->Pos(world).x + mWiringCursorButton->GetDimentions().x, 125.0f));

	mWiringCursorButtonActive = new Texture("wiring-cursor-active.png");
	mWiringCursorButtonActive->Pos(mWiringCursorButton->Pos(world));

	Pos(sf::Vector2f(CURRENT_SCREEN_WIDTH*0.5f, CURRENT_SCREEN_HEIGHT*0.5f));

	//lastly update the scale to fit the window 
	AdjustGUIScale();

}

EditorGUI::~EditorGUI()
{
	//delete and null all textures here



}

int EditorGUI::GetChosenGate()
{
	return mChosenGate;
}

int EditorGUI::GetActiveCursor()
{
	return mActiveCursor;
}

void EditorGUI::SetActiveCursor(int ac)
{
	mActiveCursor = ac;
}

void EditorGUI::Update()
{
	UpdateCurrentRes();
	UpdateTexturePositions();
	AdjustGUIScale();

	for (unsigned int i = 0; i < 9; i++)
	{
		if (mInputMgr->KeyPressed(sf::Keyboard::Escape) && mChosenGate != -1)
		{
			mMovableGates[mChosenGate]->Drop();
			mMovableGates[mChosenGate]->Pos(mGates[mChosenGate]->Pos(world));
			mChosenGate = -1;
			break;
		}
		if (mCollisionManager->checkMouseCollision(mGates[i]) && mInputMgr->MouseButtonPressed(sf::Mouse::Left))
		{
			if (!mMovableGates[i]->PickedUp())
			{
				if (mChosenGate != -1 && mMovableGates[mChosenGate]->PickedUp())
				{
					mMovableGates[mChosenGate]->Drop();
					mMovableGates[mChosenGate]->Pos(mGates[mChosenGate]->Pos(world));
				}
				mMovableGates[i]->PickUp();
				mChosenGate = i;
				mActiveCursor = 1;
			}
			else if (mMovableGates[i]->PickedUp())
			{
				mMovableGates[i]->Pos(sf::Vector2f(mInputMgr->MousePos()));
			}
			else if(!mMovableGates[i]->PickedUp() && mChosenGate != i)
			{
				mMovableGates[mChosenGate]->Drop();
				mMovableGates[mChosenGate]->Pos(mGates[mChosenGate]->Pos(world));
				mMovableGates[i]->PickUp();
				mChosenGate = i;
				mActiveCursor = 1;
			}
		}
		else if (mMovableGates[i]->PickedUp())
		{
			mMovableGates[i]->Pos(sf::Vector2f(mInputMgr->MousePos()));
		}
	}

	if (mInputMgr->KeyPressed(sf::Keyboard::Escape) && mActiveCursor != 1)
	{
		mActiveCursor = 1;
	}

	//updating cursor choices
	if (mInputMgr->MousePos().y < 140 && mInputMgr->MouseButtonPressed(sf::Mouse::Left))
	{
		if (mCollisionManager->checkMouseCollision(mRunTestButton))
		{
			if (mRunTestActive == false)
			{
				mRunTestActive = true;
			}
			else if (mRunTestActive == true)
			{
				mRunTestActive = false;
			}
		}
		if (mCollisionManager->checkMouseCollision(mStandardCursorButton))
		{
			mActiveCursor = 1;
			if (mChosenGate != -1)
			{
				mMovableGates[mChosenGate]->Drop();
				mMovableGates[mChosenGate]->Pos(mGates[mChosenGate]->Pos(world));
				mChosenGate = -1;
			}
		}
		else if (mCollisionManager->checkMouseCollision(mHighlightCursorButton))
		{
			mActiveCursor = 2;
			if (mChosenGate != -1)
			{
				mMovableGates[mChosenGate]->Drop();
				mMovableGates[mChosenGate]->Pos(mGates[mChosenGate]->Pos(world));
				mChosenGate = -1;
			}
		}
		else if (mCollisionManager->checkMouseCollision(mRemoveCursorButton))
		{
			mActiveCursor = 3;
			if (mChosenGate != -1)
			{
				mMovableGates[mChosenGate]->Drop();
				mMovableGates[mChosenGate]->Pos(mGates[mChosenGate]->Pos(world));
				mChosenGate = -1;
			}
		}
		else if (mCollisionManager->checkMouseCollision(mWiringCursorButton))
		{
			mActiveCursor = 4;
			if (mChosenGate != -1)
			{
				mMovableGates[mChosenGate]->Drop();
				mMovableGates[mChosenGate]->Pos(mGates[mChosenGate]->Pos(world));
				mChosenGate = -1;
			}
		}
	}

	
}

void EditorGUI::Render()
{
	leftGUITexture->Render();
	mGUIInventory->Render();
	topGUITexture->Render();
	mLogoTexture->Render();
	mGuiButtonSpace->Render();
	if (mRunTestActive)
	{
		mRunTestButtonActive->Render();
		mRunTestButtonTextActive->Render();
	}
	else
	{
		mRunTestButton->Render();
		mRunTestButtonText->Render();
	}

	if (mActiveCursor == 1)
	{
		mStandardCursorButtonActive->Render();
	}
	else
	{
		mStandardCursorButton->Render();
	}
	if (mActiveCursor == 2)
	{
		mHighlightCursorButtonActive->Render();
	}
	else
	{
		mHighlightCursorButton->Render();
	}
	if (mActiveCursor == 3)
	{
		mRemoveCursorButtonActive->Render();
		mRemoveCursor->Pos(sf::Vector2f(mInputMgr->MousePos()));
		mRemoveCursor->Render();
	}
	else
	{
		mRemoveCursorButton->Render();
	}
	if(mActiveCursor == 4)
	{
		mWiringCursorButtonActive->Render();
	}
	else
	{
		mWiringCursorButton->Render();
	}

	mGUILogicOptions->Render();
	for (unsigned int i = 0; i < 9; i++)
	{
		mGateBackgrounds[i]->Render();
	}
	for (unsigned int i = 0; i < 9; i++)
	{
		mGates[i]->Render();
	}
	for (unsigned int i = 0; i < 9; i++)
	{
		mGateNameTextures[i]->Render();
	}
	for (unsigned int i = 0; i < 9; i++)
	{
		if(mMovableGates[i]->PickedUp())
			mMovableGates[i]->Render();
	}
}