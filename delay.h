#ifndef DELAY_H
#define DELAY_H

#include <unistd.h> // For usleep function
#include <time.h>    // For time function
#include <stdbool.h> // For bool type

int delay(int seconds);
bool delayNonBlocking(int seconds);

#endif // DELAY_H