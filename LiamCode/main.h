//C standard library
//#include <stdlib.h>

#ifndef __MAIN_H
#define __MAIN_H

//C++ standard library.
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "level.h"

//Imports fundamental constants and functions for GLUT and OpenGL
#include <GL/glut.h>
using namespace std;
int lastFrameTime = 0;

//Location of moving box
float boxX = 0.0f;

int width = 640;

int height = 480;

int frame = 0;

bool spawn = false;

bool keys [256];

Character* mia;

Level* level;

#endif
