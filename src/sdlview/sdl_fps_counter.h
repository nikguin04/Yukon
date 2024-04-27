#ifndef SDL_FPS_COUNTER_H
#define SDL_FPS_COUNTER_H

#include "sdlmanager.h"
#include <stdlib.h>
#include <time.h>

typedef struct FpsCounterManager_struct {
	char str[16];
	int count;
	clock_t last_update;
	clock_t start;
} FpsCounterManager;

FpsCounterManager *InitFpsCounter(SDLManager *manager);
void UpdateFpsCounter(FpsCounterManager *fcm);

#endif
