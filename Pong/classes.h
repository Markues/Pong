#ifndef CLASSES_H
#define CLASSES_H

#include <string>
#include <SDL2/SDL.h>
#include "constants.h"
#include "circle.h"

using namespace std;

class LTexture {
public:
	// Initializes variables
	LTexture();
	
	// Deallocates memory
	~LTexture();
	
	// Loads image at specified path
	bool loadFromFile(string path);
	
#ifdef _SDL_TTF_H
	// Creates image from font string
	bool loadFromRenderedText(string textureText, SDL_Color textColor);
#endif
	
	// Deallocates texture
	void free();
	
	// Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	
	// Set blending
	void setBlendMode(SDL_BlendMode blending);
	
	// Set alpha modulation
	void setAlpha(Uint8 alpha);
	
	// Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	// Gets image dimensions
	int getWidth();
	int getHeight();
	
private:
	// The actual hardware texture
	SDL_Texture* mTexture;
	
	// Image dimensions
	int mWidth;
	int mHeight;
};

class Dot {
public:
	// The dimensions of the dot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;
	
	// Maximum axis velocity of the dot
	static const int DOT_VEL = 2;
	
	// Initializes the variables
	Dot(int x, int y);
	
	// Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);
	
	// Moves the dot and checks collision
	void move(SDL_Rect& square, Circle& circle);
	
	// Shows the dot on the screen
	void render();
	
	// Gets collision circle
	Circle& getCollider();
	
private:
	// The X and Y offsets of the dot
	int mPosX, mPosY;
	
	// The velocity of the dot
	int mVelX, mVelY;
	
	// Dot's collision circle
	Circle mCollider;
	
	// Moves the collision circle relative to the dot's offset
	void shiftColliders();
};

#endif
