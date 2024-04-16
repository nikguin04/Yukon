#ifndef sdl_fps_counter_h
#define sdl_fps_counter_h

#include "sdlmanager.h"
#include <stdlib.h>

typedef struct FpsCounterManager_struct {
    char **str_ptr;
    
} FpsCounterManager;

FpsCounterManager* InitFpsCounter(SDLManager *manager);

#endif 