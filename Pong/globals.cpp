#include "classes.h"
#include "constants.h"

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The window renderer
SDL_Renderer* gRenderer = NULL;

// Scene textures
LTexture gBallTexture;
LTexture gPaddleTexture;
LTexture gScoreTexture;

SDL_Rect gScoreClips[TOTAL_SCORE_SPRITES];
