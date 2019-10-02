#include "util/timer.hpp"

Timer::Timer()
{
}

void Timer::Start()
{
    m_Start = std::chrono::high_resolution_clock::now();
}

float Timer::GetTime()
{
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(end - m_Start).count();
}