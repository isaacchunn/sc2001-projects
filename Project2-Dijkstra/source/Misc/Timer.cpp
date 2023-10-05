#include "Timer.h"

//Initialize static variables
bool Timer::started = false;
std::chrono::steady_clock::time_point Timer::startTime = std::chrono::high_resolution_clock::now();
std::chrono::steady_clock::time_point Timer::endTime = std::chrono::high_resolution_clock::now();

/// <summary>
/// Starts the timer if applicable.
/// </summary>
void Timer::Start()
{
    if (started)
        return;

    startTime = std::chrono::high_resolution_clock::now();
    started = true;
}

/// <summary>
/// Checks if timer has started or not
/// </summary>
/// <returns>started</returns>
bool Timer::IsStarted()
{
    return started;
}

/// <summary>
/// Stops the timer if applicable
/// </summary>
void Timer::Stop()
{
    if (!started)
        return;

    endTime = std::chrono::high_resolution_clock::now();
    started = false;
}

/// <summary>
/// Gets the duration of the timer
/// </summary>
/// <returns>duration of the timer in microseconds</returns>
std::chrono::microseconds Timer::GetDuration()
{
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    return duration;
}

/// <summary>
/// Prints the duration of the timer
/// </summary>
void Timer::PrintDuration()
{
    std::cout << "Time taken: " << GetDuration().count() << " microseconds" << std::endl;
}