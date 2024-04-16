#include "sdl_fps_counter.h"




FpsCounterManager* InitFpsCounter(SDLManager *manager) {
    FpsCounterManager *fcm = (FpsCounterManager*) malloc(sizeof(FpsCounterManager));
    fcm->str_ptr = &manager->fpstext;
    *fcm->str_ptr = "FPS: 0";
}