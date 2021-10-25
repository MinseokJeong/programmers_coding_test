#include <iostream>
#include <chrono>

#include "mj_timer.h"

std::chrono::_V2::steady_clock::time_point startTime;
std::chrono::_V2::steady_clock::time_point endTime;

void startTimer()
{
    startTime = std::chrono::steady_clock::now();
}

void endTimer()
{
    endTime = std::chrono::steady_clock::now();
}

void printTimeDiff()
{
      std::cout<<"Delay : "
      <<std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()
      <<std::endl;
}
