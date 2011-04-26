//C standard library
//#include <stdlib.h>

#include "Character.cpp"

//C++ standard library.
#include <iostream>

#include <math.h>
#include <stdlib.h>

//Imports fundamental constants and functions for GLUT and OpenGL
#include <GLUT/glut.h>
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