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
	mVelX = BALL_VEL;
	mVelY = BALL_VEL;
	
	// Move collider relative to the circle
	shiftColliders();
}

void Ball::move(SDL_Rect& leftPaddle, SDL_Rect& rightPaddle)
{
	// Move the ball left or right
	mPosX += mVelX;
	shiftColliders();
	
	if(checkCollision(mCollider, leftPaddle) || checkCollision(mCollider, rightPaddle)) {
		mPosX -= mVelX;
		mVelX *= -1;
		shiftColliders();
	}
	
	// If the ball collided or went too far to the left or right
	if((mPosX - mCollider.r < 0) || (mPosX + mCollider.r > SCREEN_WIDTH)) {
		// Move back
		mPosX = SCREEN_WIDTH / 2;
		mPosY = (SCREEN_HEIGHT / 2) + (TOP_SCREEN_HEIGHT / 2);
		mVelX *= -1;
		mVelY *= -1;
		shiftColliders();
	}
	
	// Move the ball up or down
	mPosY += mVelY;
	shiftColliders();
	
	// If the ball collided or went too far up or down
	if((mPosY - mCollider.r < TOP_SCREEN_HEIGHT) || (mPosY + mCollider.r > SCREEN_HEIGHT)) {
		// Move back
		mPosY -= mVelY;
		mVelY *= -1;
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
