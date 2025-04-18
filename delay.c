#include "delay.h"
int delay(int seconds)
{
    if (seconds < 0)
    {
        return -1; // Invalid input
    }
    usleep(seconds * 1000000); // Convert seconds to microseconds
    return 0;                  // Success
}

bool delayNonBlocking(int seconds)
{
    static bool isFirstCall = true;
    static time_t startTime;
    static time_t endTime;
    if (seconds < 0)
    {
        return false; // Invalid input
    }
    else
    {

        if (isFirstCall)
        {
            time(&startTime);              // Get the current time
            endTime = startTime + seconds; // Calculate the end time
            isFirstCall = false;           // Mark the first call
            return false;
        }
        else
        {
            time_t currentTime;
            time(&currentTime); // Get the current time again
            if (currentTime >= endTime)
            {
                isFirstCall = true; // Reset for the next call
                return true;        // Time is up
            }
            else{
                return false; // Time is not up yet
            }
        }
    }
}