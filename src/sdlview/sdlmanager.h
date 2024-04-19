#ifndef SDLMANAGER_H
#define SDLMANAGER_H

#include <SDL_events.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_pixels.h>
#include <SDL_render.h>

typedef struct GUI_Struct_struct {
	SDL_Window *wind;
	TTF_Font *font;
	char *statusmsg;
	char *fpstext;
	SDL_Texture *temptexture;
} SDLManager;

typedef const void (*EventTriggerFunction)(SDLManager *, SDL_Event *);
typedef struct Event_obs_struct {
	const EventTriggerFunction func;
} EventObserver;
#define EventObserverCount 1

#endif
