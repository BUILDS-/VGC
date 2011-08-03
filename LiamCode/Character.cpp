/*
 Code by Liam Wang.
 <lzw@bu.edu>
 Does all the calculation on the movement of the
 player character.

 WARNING: If you make the height or width smaller than the max speed,
 TELL ME, so that I can fix collision detection to handle odd cases.
 (max speed can be found in moveUp(), moveDown(), moveRight() moveLeft())
 maxspeed currently = 10;
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
	height = 20;
	width = 20;
}

//Redundant, yes. Will fix later.
Character::Character (int a, int b) {
	printf("Harp de darp\n");
	x = a;
	y = b;
	x_v = 0;
	y_v = 0;
	SPEED = 1;
	height = 20;
	width = 20;
}

void Character::onGround(void) {
  grounded = 1;
}

void Character::offGround(void) {
  grounded = 0;
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

int Character::getHeight(void) {
  return height;
}

int Character::getWidth(void) {
  return width;
}

int Character::getURX(void) {
  return x + width;
}

int Character::getURY(void) {
  return y + height;
}

int Character::getLRX(void) {
  return x + width;
}

int Character::getLRY(void) {
  return y;
}

int Character::getULX(void) {
  return x;
}

int Character::getULY(void) {
  return y + height;
}

int Character::getLLX(void) {
  return x;
}

int Character::getLLY(void) {
  return y;
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

void Character::setX_V(int neoX_V) {
  x_v = neoX_V;
}

void Character::setY_V(int neoY_V) {
  y_v = neoY_V;
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
	if (y <= 40 || grounded) {
		y_v += 10;
	}
	offGround();
}





