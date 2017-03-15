#include "classes.h"
#include "globals.h"
#include "functions.h"
#include "circle.h"

Ball::Ball(int x, int y) {
	// Initialize the offsets
	mPosX = x;
	mPosY = y;
	
	// Set collision circle size
	mCollider.r = BALL_WIDTH / 2;
	
	// Initialize the velocity
	mVelX = 0;
	mVelY = 0;
	
	// Move collider relative to the circle
	shiftColliders();
}

void Ball::handleEvent(SDL_Event& e) {
	// If a key was pressed
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		// Adjust the velocity
		switch(e.key.keysym.sym) {
			case SDLK_UP:
				mVelY -= BALL_VEL;
				break;
			case SDLK_DOWN:
				mVelY += BALL_VEL;
				break;
			case SDLK_LEFT:
				mVelX -= BALL_VEL;
				break;
			case SDLK_RIGHT:
				mVelX += BALL_VEL;
				break;
		}
	}
	// If a key was released
	else if(e.type == SDL_KEYUP && e.key.repeat == 0) {
		// Adjust the velocity
		switch(e.key.keysym.sym) {
			case SDLK_UP:
				mVelY += BALL_VEL;
				break;
			case SDLK_DOWN:
				mVelY -= BALL_VEL;
				break;
			case SDLK_LEFT:
				mVelX += BALL_VEL;
				break;
			case SDLK_RIGHT:
				mVelX -= BALL_VEL;
				break;
		}
	}
}

void Ball::move(SDL_Rect& square)
{
	// Move the ball left or right
	mPosX += mVelX;
	shiftColliders();
	
	// If the ball collided or went too far to the left or right
	if((mPosX - mCollider.r < 0) || (mPosX + mCollider.r > SCREEN_WIDTH) || checkCollision(mCollider, square)) {
		// Move back
		mPosX -= mVelX;
		shiftColliders();
	}
	
	// Move the ball up or down
	mPosY += mVelY;
	shiftColliders();
	
	// If the ball collided or went too far up or down
	if((mPosY - mCollider.r < 0) || (mPosY + mCollider.r > SCREEN_HEIGHT) || checkCollision(mCollider, square)) {
		// Move back
		mPosY -= mVelY;
		shiftColliders();
	}
}

void Ball::render() {
	// Show the ball
	gBallTexture.render(mPosX - mCollider.r, mPosY - mCollider.r);
}

Circle& Ball::getCollider() {
	return mCollider;
}

void Ball::shiftColliders() {
	// Align collider to center of ball
	mCollider.x = mPosX;
	mCollider.y = mPosY;
}
