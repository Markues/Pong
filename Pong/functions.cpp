#include <SDL2_image/SDL_image.h>
#include "constants.h"
#include "globals.h"
#include "functions.h"

bool init() {
	// Initialization flag
	bool success = true;
	
	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		// Set texture filtering to linear
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}
		
		// Create window
		gWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			// Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				
				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				
				// Initialize SDL_mixer
				if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}
	
	return success;
}

bool loadMedia() {
	// Loading success flag
	bool success = true;
	
	if(!gBallTexture.loadFromFile("Ball.png")) {
		printf("Failed to load ball texture!\n");
		success = false;
	}
	if(!gPaddleTexture.loadFromFile("Paddle.png")) {
		printf("Failed to load paddle texture!\n");
		success = false;
	}
	if(!gScoreTexture.loadFromFile("NumberSheet.png")) {
		printf("Failed to load score texture!\n");
		success = false;
	}
	if(!gWinnerTexture.loadFromFile("WinnerText.png")) {
		printf("Failed to winner text texture!\n");
		success = false;
	}
	
	// Load sound effects
	gBoop = Mix_LoadWAV("Boop.wav");
	if(gBoop == NULL) {
		printf("Failed to load Boop sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	gScore = Mix_LoadWAV("Score.wav");
	if(gScore == NULL) {
		printf("Failed to load Score sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	
	for(int i = 0; i < TOTAL_SCORE_SPRITES; i++) {
		gScoreClips[i].x = i * SCORE_WIDTH;
		gScoreClips[i].y = 0;
		gScoreClips[i].w = SCORE_WIDTH;
		gScoreClips[i].h = SCORE_HEIGHT;
	}
	
	return success;
}

void close() {
	// Free loaded images
	gBallTexture.free();
	gPaddleTexture.free();
	gScoreTexture.free();
	gWinnerTexture.free();
	
	Mix_FreeChunk(gBoop);
	Mix_FreeChunk(gScore);
	gBoop = NULL;
	gScore = NULL;
	
	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	
	// Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool checkCollision(Circle& a, SDL_Rect& b) {
	// Closest point on collision box
	int cX, cY;
	
	// Find closest x offset
	if(a.x < b.x) {
		cX = b.x;
	}
	else if(a.x > b.x + b.w) {
		cX = b.x + b.w;
	}
	else {
		cX = a.x;
	}
	
	// Find closest y offset
	if(a.y < b.y) {
		cY = b.y;
	}
	else if(a.y > b.y + b.h) {
		cY = b.y + b.h;
	}
	else {
		cY = a.y;
	}
	
	// If the closest point is inside the circle
	if(distanceSquared(a.x, a.y, cX, cY) < a.r * a.r) {
		// This box and the circle have collided
		return true;
	}
	
	// If the shapes have not collided
	return false;
}

double distanceSquared(int x1, int y1, int x2, int y2) {
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}
