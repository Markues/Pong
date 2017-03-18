#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <string>
#include "constants.h"
#include "classes.h"
#include "functions.h"
#include "globals.h"

using namespace std;

int main(int argc, char* args[]) {
	// Start up SDL and create window
	if(!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		// Load media
		if(!loadMedia()) {
			printf("Failed to load media!\n");
		}
		else {
			// Main loop flag
			bool quit = false;
			
			// Event handler
			SDL_Event e;
			
			// The ball that will be moving around on the screen
			Ball ball(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + (TOP_SCREEN_HEIGHT / 2));
			
			Paddle leftPaddle(0, (SCREEN_HEIGHT / 2) + (TOP_SCREEN_HEIGHT / 2) - (Paddle::PADDLE_HEIGHT / 2), Paddle::LEFT_PADDLE);
			Paddle rightPaddle(SCREEN_WIDTH - Paddle::PADDLE_WIDTH, (SCREEN_HEIGHT / 2) + (TOP_SCREEN_HEIGHT / 2) - (Paddle::PADDLE_HEIGHT / 2), Paddle::RIGHT_PADDLE);
			
			Score leftScore((SCREEN_WIDTH / 4) - (SCORE_WIDTH / 2), (TOP_SCREEN_HEIGHT / 2) - (SCORE_HEIGHT / 2), STARTING_SCORE);
			Score rightScore(((SCREEN_WIDTH / 4) * 3) - (SCORE_WIDTH / 2), (TOP_SCREEN_HEIGHT / 2) - (SCORE_HEIGHT / 2), STARTING_SCORE);
			
			bool leftWinner = false;
			bool rightWinner = false;
			
			// While application is running
			while(!quit) {
				if(leftScore.getVal() == WINNING_SCORE) {
					leftWinner = true;
				}
				else if(rightScore.getVal() == WINNING_SCORE) {
					rightWinner = true;
				}
				
				// Handle events on queue
				while(SDL_PollEvent(&e) != 0) {
					// User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					}
					
					if(!leftWinner && !rightWinner) {
						// Handle input for the ball
						leftPaddle.handleEvent(e);
						rightPaddle.handleEvent(e);
						ball.handleEvent(e);
					}
				}
				
				if(!leftWinner && !rightWinner) {
					leftPaddle.move();
					rightPaddle.move();
					
					// Move the ball and check collision
					int scoreCheck = ball.move(leftPaddle.getCollider(), rightPaddle.getCollider());
					if(scoreCheck != 0) {
						Mix_PlayChannel(-1, gScore, 0);
						switch (scoreCheck) {
							case -1:
								leftScore.setVal(leftScore.getVal() + 1);
								break;
							case 1:
								rightScore.setVal(rightScore.getVal() + 1);
								break;
						}
					}
				}
				
				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
			
				// Midcourt and score line
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH / 2, TOP_SCREEN_HEIGHT, SCREEN_WIDTH / 2, SCREEN_HEIGHT);
				SDL_RenderDrawLine(gRenderer, 0, TOP_SCREEN_HEIGHT, SCREEN_WIDTH, TOP_SCREEN_HEIGHT);
				
				leftScore.render();
				rightScore.render();
				ball.render();
				rightPaddle.render();
				leftPaddle.render();
				if(leftWinner) {
					gWinnerTexture.render((SCREEN_WIDTH / 2) - ((WINNER_WIDTH * 3) / 2), (TOP_SCREEN_HEIGHT / 2) - (WINNER_HEIGHT / 2));
				}
				else if(rightWinner) {
					gWinnerTexture.render((SCREEN_WIDTH / 2) + (WINNER_WIDTH / 2), (TOP_SCREEN_HEIGHT / 2) - (WINNER_HEIGHT / 2));
				}
				
				// Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	
	// Free resources and close SDL
	close();
	
	return 0;
}
