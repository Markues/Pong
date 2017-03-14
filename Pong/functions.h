#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "circle.h"

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// Circle/Circle collision detector
bool checkCollision(Circle& a, Circle& b);

// Circle/Box collision detector
bool checkCollision(Circle& a, SDL_Rect& b);

// Calculates distance squared between two points
double distanceSquared(int x1, int y1, int x2, int y2);

#endif
