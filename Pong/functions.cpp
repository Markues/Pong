#include <SDL2/SDL.h>
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
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
			}
		}
	}
	
	return success;
}

bool loadMedia() {
	// Loading success flag
	bool success = true;
	
	// Load dot texture
	if(!gDotTexture.loadFromFile("dot.bmp")) {
		printf("Failed to load dot texture!\n");
		success = false;
	}
	
	return success;
}

void close() {
	// Free loaded images
	gDotTexture.free();
	
	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	
	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool checkCollision(Circle& a, Circle& b) {
	// Calculate total radius squared
	int totalRadiusSquared = a.r + b.r;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;
	
	// If the distance between the centers of the circles is less than the sum of their radii
	if(distanceSquared(a.x, a.y, b.x, b.y) < (totalRadiusSquared)) {
		// The circles have collided
		return true;
	}
	
	// If not
	return false;
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
