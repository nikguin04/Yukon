#include "sdl_image_loader.h"

SDL_Texture *LoadOptimizedImage(char *path, SDL_Surface *gScreenSurface, SDL_Renderer *rend) {
    

    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
        return 0;
    }

    SDL_Surface* optimizedSurface = NULL;
    optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
    if( optimizedSurface == NULL )
    {
        printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
        return 0;
    }
    SDL_FreeSurface( loadedSurface );
    SDL_Texture * texture = SDL_CreateTextureFromSurface(rend, optimizedSurface);
    SDL_FreeSurface( optimizedSurface );
    return texture;
}

SDL_Texture *LoadSDLImage(char *path, SDL_Renderer *rend) {
    

    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
        return 0;
    }

    
    SDL_Texture * texture = SDL_CreateTextureFromSurface(rend, loadedSurface);
    SDL_FreeSurface( loadedSurface );
    return texture;
}
