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

/*
 * Default constructer. Creates a non-moving object with a height and width of 
 * 20 pixals.
 */
Character::Character(void) {
  CPoint temp = {0,0};
  location = temp;
  x_v = 0;
  y_v = 0;
  SPEED = 1;
  height = 20;
  width = 20;
}

//
Character::Character (int x, int y) {
  CPoint temp = {x,y};
  location = temp;
  x_v = 0;
  y_v = 0;
  SPEED = 1;
  height = 20;
  width = 20;
}

Character::Character (int x, int y, int p_height, int p_width) {
  CPoint temp = {x,y};
  location = temp;
  x_v = 0;
  y_v = 0;
  SPEED = 1;
  height = p_height;
  width = p_width;
}

void Character::onGround(void) {
  grounded = 1;
}

void Character::offGround(void) {
  grounded = 0;
}

//Get functions.

int Character::getX_V(void) {
  return x_v;
}

int Character::getY_V(void) {
  return y_v;
}

int Character::isGoingRight(void) {
  return (getX_V() > 0);
}

int Character::isGoingLeft(void) {
  return (getX_V() < 0);
}

int Character::isGoingUp(void) {
  return (getY_V() > 0);
}

int Character::isGoingDown(void) {
  return (getY_V() < 0);
}

int Character::getHeight(void) {
  return height;
}

int Character::getWidth(void) {
  return width;
}

CPoint Character::getUR(void) {
  CPoint temp = {location.x + width, location.y + height};
  return temp;
}

CPoint Character::getLR(void) {
  CPoint temp = {location.x + width, location.y};
  return temp;
}

CPoint Character::getUL(void) {
  CPoint temp = {location.x, location.y + height};
  return temp;
}

CPoint Character::getLL(void) {
  CPoint temp = {location.x, location.y};
  return temp;
}

//Set new position.
void Character::setCharacter(int a, int b){
	location.x = a;
	location.y = b;
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

void Character::setV(CPoint p) {
  x_v = p.x;
  y_v = p.y;
}

//Updates location based on velocity
void Character::move(void) {
  location.x += x_v;
  if(location.y > 40 || y_v > 0) {
    location.y += y_v;
  } else {
    y_v = 0;
    onGround();
  }
}

void Character::ifUnchanged(CPoint *distance_away, CPoint *set_to) {
  if ((*distance_away).x == INT_MAX) {
    (*distance_away).x = 0;
    (*set_to).x = getX_V();
  }
  if ((*distance_away).y == INT_MAX) {
    (*distance_away).y = 0;
    (*set_to).y = getY_V();
  }
    

}

void Character::moveTo(CPoint distance_away, CPoint set_to) {
  ifUnchanged(&distance_away, &set_to);
  setV(distance_away);
  int temp_grounded = grounded;
  move();
  grounded = temp_grounded;
  setV(set_to);
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
  if (grounded) {
    y_v += 10;
  }
  offGround();
}

/*
 * Prints a point for debugging. The points are numbered
 *          3     4
 *           -----
 *           |   |
 *           -----
 *          1     2
 */

void Character::printPoint(int d) {
  CPoint point;
  if (d == 1) {
    point = getLL();
  } else if (d == 2) {
    point = getLR();
  } else if (d == 3) {
    point = getUL();
  } else if (d == 4) {
    point = getUR();
  } else {
    printf("From printPoint in Character.cpp: What was that input? %d? What?\n",
	   d);
    return;
  }
  printf("x = %d\n y = %d\n", point.x, point.y);
}



