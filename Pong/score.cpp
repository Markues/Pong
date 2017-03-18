#include "classes.h"
#include "globals.h"
#include "functions.h"

Score::Score(int x, int y, int scoreVal) {
	// Get the offsets
	mBox.x = x;
	mBox.y = y;
	
	// Set the collision box
	mBox.w = SCORE_WIDTH;
	mBox.h = SCORE_HEIGHT;
	
	// Get the score type
	mVal = scoreVal;
}

void Score::render() {
	gScoreTexture.render(mBox.x, mBox.y, &gScoreClips[mVal]);
}

int Score::getVal() {
	return mVal;
}

void Score::setVal(int val) {
	mVal = val;
}

SDL_Rect Score::getBox() {
	return mBox;
}


