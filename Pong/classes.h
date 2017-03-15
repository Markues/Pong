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

class Paddle {
public:
	static const int PADDLE_WIDTH = 6;
	static const int PADDLE_HEIGHT = 48;
	
	static const bool RIGHT_PADDLE = true;
	static const bool LEFT_PADDLE = false;
	
	static const int PADDLE_VEL = 3;
	
	Paddle(int x, int y, bool isRightPaddle);
	
	void handleEvent(SDL_Event& e);
	
	void move(Circle& circle);
	
	void render();
	
	SDL_Rect& getCollider();
	
private:
	int mPosX, mPosY;
	
	int mVelX, mVelY;
	
	bool isRight;
	
	SDL_Rect mCollider;
	
	void shiftColliders();
};

class Ball {
public:
	// The dimensions of the ball
	static const int BALL_WIDTH = 8;
	static const int BALL_HEIGHT = 8;
	
	// Maximum axis velocity of the ball
	static const int BALL_VEL = 2;
	
	// Initializes the variables
	Ball(int x, int y);
	
	// Takes key presses and adjusts the ball's velocity
	void handleEvent(SDL_Event& e);
	
	// Moves the ball and checks collision
	void move(SDL_Rect& leftPaddle, SDL_Rect& rightPaddle);
	
	// Shows the ball on the screen
	void render();
	
	// Gets collision circle
	Circle& getCollider();
	
private:
	// The X and Y offsets of the ball
	int mPosX, mPosY;
	
	// The velocity of the ball
	int mVelX, mVelY;
	
	// Ball's collision circle
	Circle mCollider;
	
	// Moves the collision circle relative to the ball's offset
	void shiftColliders();
};

#endif
