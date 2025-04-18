#ifndef DELAY_H
#define DELAY_H

#ifdef _WIN32
#include <windows.h> // For Sleep function
#else
#include <unistd.h>  // For usleep function
#endif
#include <time.h>    // For time function
#include <stdbool.h> // For bool type

int delay(int seconds);
bool delayNonBlocking(int seconds);

#endif // DELAY_H