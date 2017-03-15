#include "classes.h"
#include "globals.h"
#include "functions.h"

Paddle::Paddle(int x, int y) {
	// Initialize the offsets
	mPosX = x;
	mPosY = y;
	
	mCollider.w = PADDLE_WIDTH;
	mCollider.h = PADDLE_HEIGHT;
	
	// Initialize the velocity
	mVelX = 0;
	mVelY = 0;
	
	shiftColliders();
}

void Paddle::handleEvent(SDL_Event& e) {
	// If a key was pressed
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		// Adjust the velocity
		switch(e.key.keysym.sym) {
			case SDLK_UP:
				mVelY -= PADDLE_VEL;
				break;
			case SDLK_DOWN:
				mVelY += PADDLE_VEL;
				break;
		}
	}
	// If a key was released
	else if(e.type == SDL_KEYUP && e.key.repeat == 0) {
		// Adjust the velocity
		switch(e.key.keysym.sym) {
			case SDLK_UP:
				mVelY += PADDLE_VEL;
				break;
			case SDLK_DOWN:
				mVelY -= PADDLE_VEL;
				break;
		}
	}
}

void Paddle::move(Circle& circle)
{
	// Move the paddle up or down
	mPosY += mVelY;
	shiftColliders();
	
	// If the paddle collided or went too far up or down
	if((mPosY < 0) || (mPosY + mCollider.h > SCREEN_HEIGHT) || checkCollision(circle, mCollider)) {
		// Move back
		mPosY -= mVelY;
		shiftColliders();
	}
}

void Paddle::render() {
	// Show the paddle
	gPaddleTexture.render(mPosX, mPosY);
}

SDL_Rect& Paddle::getCollider() {
	return mCollider;
}

void Paddle::shiftColliders() {
	mCollider.x = mPosX;
	mCollider.y = mPosY;
}
