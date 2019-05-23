#include "StartScreen.h"

StartScreen::StartScreen()
{
	mTimer = Timer::Instance();
	mInputMgr = InputManager::Instance();
	mCollisionMgr = CollisionManager::Instance();

	mLogo = new Texture("logo-full.png");
	mLogo->Pos(sf::Vector2f(Graphics::Instance()->GetWindowResolution().x *0.5f, 150.0f));

	mNewFile = new Texture("NEW FILE", "main.ttf", 70, sf::Color::Black);
	mNewFile->Pos(sf::Vector2f(Graphics::Instance()->SCREEN_WIDTH*0.5f, 400.0f));

	mNewFileActive = new Texture("NEW FILE", "main.ttf", 70, sf::Color::Green);
	mNewFileActive->Pos(sf::Vector2f(Graphics::Instance()->SCREEN_WIDTH*0.5f, 400.0f));

	mLoadFile = new Texture("LOAD FILE", "main.ttf", 70, sf::Color::Black);
	mLoadFile->Pos(sf::Vector2f(Graphics::Instance()->SCREEN_WIDTH*0.5f, 480.0f));

	mLoadFileActive = new Texture("LOAD FILE", "main.ttf", 70, sf::Color::Green);
	mLoadFileActive->Pos(mLoadFile->Pos(world));

}

StartScreen::~StartScreen()
{
	//delete and NULL all entites here

	delete mLogo;
	mLogo = NULL;

	delete mNewFile;
	mNewFile = NULL;

	delete mNewFileActive;
	mNewFileActive = NULL;

	delete mLoadFile;
	mLoadFile = NULL;

	delete mLoadFileActive;
	mLoadFileActive = NULL;

}

int StartScreen::SelectedMode()
{
	return mSelectedMode;
}

void StartScreen::ChangeSelectedMode(int change)
{
	mSelectedMode += change;

	if (mSelectedMode < 0)
		mSelectedMode = 1;
	else if (mSelectedMode > 1)
		mSelectedMode = 0;
	
}

void StartScreen::AdaptToNewRes()
{
	mLogo->Pos(sf::Vector2f(Graphics::Instance()->GetWindowResolution().x * 0.5f, 150.0f));
	mNewFile->Pos(sf::Vector2f(Graphics::Instance()->GetWindowResolution().x*0.5f, 400.0f));
	mNewFileActive->Pos(sf::Vector2f(Graphics::Instance()->GetWindowResolution().x*0.5f, 400.0f));
	mLoadFile->Pos(sf::Vector2f(Graphics::Instance()->GetWindowResolution().x *0.5f, 480.0f));
	mLoadFileActive->Pos(mLoadFile->Pos(world));
}

void StartScreen::Update()
{

	if (mCollisionMgr->checkMouseCollision(mNewFile))
	{
		if (mInputMgr->MouseButtonPressed(sf::Mouse::Left))
		{
			ChangeSelectedMode(1);
		}
	}

	if (mInputMgr->IsWindowResized() || mNewFile->Pos(world).x != Graphics::Instance()->GetWindowResolution().x *0.5f) //why not
	{
		AdaptToNewRes();
	}

	//std::cout << SelectedMode();

	mInputMgr->ResetMouseInput();

}

void StartScreen::Render()
{
	//do all renders here
	mLogo->Render();

	if (mCollisionMgr->checkMouseCollision(mNewFile))
		mNewFileActive->Render();
	else
		mNewFile->Render();

	if (mCollisionMgr->checkMouseCollision(mLoadFile))
		mLoadFileActive->Render();
	else
		mLoadFile->Render();
}

