#include "ProgramManager.h"
#include "time.h"

ProgramManager* ProgramManager::sInstance = NULL;

ProgramManager* ProgramManager::Instance() {
	if (sInstance == NULL)
		sInstance = new ProgramManager();

	return sInstance;
}

void ProgramManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

ProgramManager::ProgramManager()
{
	srand(time(0));

	mQuit = false;

	mGraphics = Graphics::Instance();

	if (!Graphics::Initalized())
		mQuit = true;

	mScreenMgr = ScreenManager::Instance();
	mTimer = Timer::Instance();
	mInputMgr = InputManager::Instance();

}

ProgramManager::~ProgramManager()
{
	Graphics::Release();
	mGraphics = NULL;

	InputManager::Release();
	mInputMgr = NULL;

	ScreenManager::Release();
	mScreenMgr = NULL;
}

void ProgramManager::EarlyUpdate()
{
	//mInputMgr->UpdatePrevInput();
	mInputMgr->Update();

	if (mInputMgr->IsWindowClosed())
		mQuit = true;

	if (mInputMgr->IsWindowResized())
	{
		mGraphics->AdaptToNewResolution();
	}
}

void ProgramManager::Update()
{
	mScreenMgr->Update();
}

void ProgramManager::LateUpdate()
{
	//mInputMgr->UpdatePrevInput();
	mTimer->Reset();
}

void ProgramManager::Render()
{
	mGraphics->ClearBackBuffer();
	//here all our draw calls

	mScreenMgr->Render();

	mGraphics->Render();
}

void ProgramManager::Run()
{
	while (!mQuit)
	{
		mTimer->Update();

		if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE))
		{
			EarlyUpdate();
			Update(); //objects update
			LateUpdate(); //collison delection and stuff
			mInputMgr->UpdatePrevInput();
			Render();
		}
	}
}