#include "sdl_fps_counter.h"





FpsCounterManager* InitFpsCounter(SDLManager *manager) {
    FpsCounterManager *fcm = (FpsCounterManager*) malloc(sizeof(FpsCounterManager));
    fcm->str_ptr = &manager->fpstext;
    *fcm->str_ptr = "FPS: 0";
    fcm->start = clock();
    return fcm;
}

void UpdateFpsCounter(FpsCounterManager *fcm) {
    clock_t now = clock();
    int elapsed = ((double) (now - fcm->start)) / CLOCKS_PER_SEC;
    *fcm->str_ptr = "asd1234";
}