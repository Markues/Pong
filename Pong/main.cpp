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
			Ball ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			
			Paddle rightPaddle(SCREEN_WIDTH - Paddle::PADDLE_WIDTH, (SCREEN_HEIGHT / 2) - (Paddle::PADDLE_HEIGHT / 2));
			Paddle leftPaddle(0, (SCREEN_HEIGHT / 2) - (Paddle::PADDLE_HEIGHT / 2));
			
			// While application is running
			while(!quit) {
				// Handle events on queue
				while(SDL_PollEvent(&e) != 0) {
					// User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					}
					
					// Handle input for the ball
					ball.handleEvent(e);
				}
				
				// Move the ball and check collision
				ball.move(rightPaddle.getCollider(), leftPaddle.getCollider());
				
				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
			
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
