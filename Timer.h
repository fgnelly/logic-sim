#ifndef _TIMER_H
#define _TIMER_H
#include <SFML/Graphics.hpp>

class Timer {
private:

	static Timer* sInstance;

	unsigned int mStartTicks;
	unsigned int mElapsedTicks;
	float mDeltaTime;
	float mTimeScale;

	sf::Clock mClock;

public:

	static Timer* Instance();
	static void Release();

	void Reset();
	float DeltaTime();

	void TimeScale(float t);
	float TimeScale();

	void Update();

private:

	Timer();
	~Timer();
};

#endif