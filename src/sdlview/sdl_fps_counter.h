#ifndef sdl_fps_counter_h
#define sdl_fps_counter_h

#include "sdlmanager.h"
#include <stdlib.h>
#include <time.h>

typedef struct FpsCounterManager_struct {
    char str[16];
    int count;
    clock_t last_update;
    clock_t start;
    
} FpsCounterManager;

FpsCounterManager* InitFpsCounter(SDLManager *manager);
void UpdateFpsCounter(FpsCounterManager *fcm);

#endif 