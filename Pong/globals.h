#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>
#include "classes.h"

// The window we'll be rendering to
extern SDL_Window* gWindow;

// The window renderer
extern SDL_Renderer* gRenderer;

// Scene textures
extern LTexture gBallTexture;
extern LTexture gPaddleTexture;
extern LTexture gScoreTexture;
extern LTexture gWinnerTexture;

extern SDL_Rect gScoreClips[TOTAL_SCORE_SPRITES];

#endif
