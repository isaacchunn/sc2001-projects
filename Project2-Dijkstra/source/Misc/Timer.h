#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>

class Timer
{
	private:
		static std::chrono::steady_clock::time_point startTime;
		static std::chrono::steady_clock::time_point endTime;
		static bool started;
	public:
		static void Start();
		static void Stop();
		static std::chrono::microseconds GetDuration();
		static void PrintDuration();
		static bool IsStarted();
};

#endif