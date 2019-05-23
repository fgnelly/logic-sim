#include "Timer.h"

Timer* Timer::sInstance = NULL;

Timer* Timer::Instance() {
	if (sInstance == NULL)
		sInstance = new Timer();

	return sInstance;
}

void Timer::Release() {
	delete sInstance;
	sInstance = NULL;
}

Timer::Timer()
{
	Reset();
	mTimeScale = 1.0f;
}

Timer::~Timer()
{

}

void Timer::Reset()
{
	mStartTicks = mClock.getElapsedTime().asMilliseconds();
	mElapsedTicks = 0;
	mDeltaTime = 0.0f;
}

float Timer::DeltaTime()
{
	return mDeltaTime;
}

void Timer::TimeScale(float t)
{
	mTimeScale = t;
}

float Timer::TimeScale()
{
	return mTimeScale;
}

void Timer::Update()
{
	mElapsedTicks = mClock.getElapsedTime().asMilliseconds() - mStartTicks;
	mDeltaTime = mElapsedTicks * 0.001f;
}