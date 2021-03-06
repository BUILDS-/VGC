#ifndef __MAIN_H
#define __MAIN_H


#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include "level.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_gfxPrimitives.h"


using namespace std;

                                         
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

const int LEVEL_WIDTH = 1280; 
const int LEVEL_HEIGHT = 960;




//The surfaces that will be used
SDL_Surface *hello = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *reload = NULL;


// Keeps track of what frame number we are on.
int frame = 0;

// Location of moving box.
float boxX = 0.0f;

// Has the main character spawned?
bool spawn = false;

// If a key is pressed, the corresponding boolean in the array is set to true.
// If a key is released, the corresponding boolean in the array is set to false.
bool keys [SDLK_LAST];

// Pointer to the player character.
Character* mia;

// Pointer to the level the player character is currently in.
Level* level;

// If b is in between a and c, return 1. Otherwise return 0.
int isInBetween(int, int, int);

// Given the two defining points on two line segments labled a and b, this
// function figures out whether the line segments intersect.
int collide(int, int, int, int);

// If the mover will collide with the target while going down, return 1.
// Otherwise return 0.
int collideDown(Character *, Character *);

// If the mover will collide with the target while going up, return 1.
// Otherwise return 0.
int collideUp(Character *, Character *);

// If the mover will collide with the target while going right, return 1.
// Otherwise return 0.
int collideRight(Character *, Character *);

// If the mover will collide with the target while going left, return 1.
// Otherwise return 0.
int collideLeft(Character *, Character *);

// Collision detection
void cDetection(Character *);

/*
 * Gravity! Every frame a can character moves, gravity increases mia's downward
 * velocity by one (as long as the character is not grounded).
 */
void gravity(void);

// Figures out what the all the object coordinates are and draws them to the
// screen.
void drawObjects(void);

// Draws the grid on the screen.
void drawGrid(void);

// Interpretes key presses and assosiates them with the appropriate actions.
// (ie, press left and the player character will move left).
void moveMia(void);

// Spawns level and characters.
void spawn_level(void);

// Function is called once per frame. MAIN LOOP.
void display(void);

// Given a height and a width, this function changes the OpenGL window size.
void reshape(int,int);

// All it says is to draw another frame.
void idle(void);

// If a normal key is pressed, this is called.
void keyPressed (unsigned char,int,int);

// If a key is released, this is called.
void keyReleased (unsigned char,int,int);

// If a special key is pressed (arrow keys), this is called.
void keySpecial (int,int,int);

// If a spacial key is released (arrow keys), this is called.
void keySReleased(int,int,int);


#endif

