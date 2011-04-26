/*
 Code by Liam Wang.
 <lzw@bu.edu>
 Does all the calculation on the movement of the
 player character.
 */


#include "Character.h"

//My sad sad attempt at a global constant.
extern int SPEED;

//Constructor
Character::Character(void) {
	x = 0;
	y = 0;
	x_v = 0;
	y_v = 0;
	SPEED = 1;
}

//Redundant, yes. Will fix later.
Character::Character (int a, int b) {
	printf("Harp de darp\n");
	x = a;
	y = b;
	x_v = 0;
	y_v = 0;
	SPEED = 1;
}

//Get functions.
int Character::getX(void) {
	return x;
}

int Character::getY(void) {
	return y;
}

int Character::getX_V(void) {
	return x_v;
}

int Character::getY_V(void) {
	return y_v;
}

//Set new position.
void Character::setCharacter(int a, int b){
	x = a;
	y = b;
	printf("%d %d\n", a, b);
}

//Increases down, left, and right velocity by SPEED.
void Character::moveDown(void) {
	if (y_v > -10) {
		y_v -= SPEED;
	}
}
void Character::moveLeft(void) {
	if (x_v > -10) {
		x_v -= SPEED;
	}
}
void Character::moveRight(void) {
	if (x_v < 10) {
		x_v += SPEED;
	}
}

//Updates location based on velocity
void Character::move(void) {
	x += x_v;
	if(y > 40 || y_v > 0) {
		y += y_v;
	} else {
		y_v = 0;
	}
}

//Friction on x access.
void Character::slowX(void) {
	if (x_v < 0) {
		x_v++;
	} else if (x_v > 0) {
		x_v--;
	}
}

//If on ground, jump.
void Character::jump(void) {
	if (y <= 40) {
		y_v += 10;
	}
}





