#include "sdl_fps_counter.h"
#include <stdio.h>

FpsCounterManager *InitFpsCounter(SDLManager *manager) {
	FpsCounterManager *fcm = (FpsCounterManager *) malloc(sizeof(FpsCounterManager));
	manager->fpstext = fcm->str;
	sprintf(fcm->str, "FPS: ?");
	fcm->start = clock();
	fcm->count = 0;
	fcm->last_update = 0;
	return fcm;
}

void UpdateFpsCounter(FpsCounterManager *fcm) {
	clock_t now = clock();
//	int elapsed = ((double) (now - fcm->start)) / CLOCKS_PER_SEC;
	clock_t elapsedms = (now - fcm->start);
	fcm->count++;
	if (elapsedms - fcm->last_update >= 1000) { // 1 second has gone by since last update
		sprintf(fcm->str, "FPS: %d", fcm->count);
		fcm->count = 0;
		fcm->last_update = now;
	}
}
