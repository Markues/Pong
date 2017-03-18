#include <SDL2_mixer/SDL_mixer.h>
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
LTexture gWinnerTexture;

Mix_Chunk *gBoop = NULL;
Mix_Chunk *gScore = NULL;

SDL_Rect gScoreClips[TOTAL_SCORE_SPRITES];
