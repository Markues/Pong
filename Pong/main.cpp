#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
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
			
			// While application is running
			while(!quit) {
				// Handle events on queue
				while(SDL_PollEvent(&e) != 0) {
					// User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					}
					
					// Handle input for the ball
					leftPaddle.handleEvent(e);
					rightPaddle.handleEvent(e);
				}
				
				leftPaddle.move();
				rightPaddle.move();
				
				// Move the ball and check collision
				//ball.move(leftPaddle.getCollider(), rightPaddle.getCollider());
				
				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
			
				// Midcourt and score line
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH / 2, TOP_SCREEN_HEIGHT, SCREEN_WIDTH / 2, SCREEN_HEIGHT);
				SDL_RenderDrawLine(gRenderer, 0, TOP_SCREEN_HEIGHT, SCREEN_WIDTH, TOP_SCREEN_HEIGHT);
				
				ball.render();
				rightPaddle.render();
				leftPaddle.render();
				
				// Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	
	// Free resources and close SDL
	close();
	
	return 0;
}
