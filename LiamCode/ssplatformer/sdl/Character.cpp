/*
 * Code by Liam Wang.
 * <lzw@bu.edu>
 * Does all the calculation on the movement of the player character.
 *
 * WARNING: If you make the height or width smaller than the max speed,
 * TELL ME, so that I can fix collision detection to handle odd cases.
 * (max speed can be found in moveUp(), moveDown(), moveRight() moveLeft())
 * maxspeed currently = 10;
 */


#include "Character.h"

/*
 * Default constructer. Creates a non-moving square object with a height and 
 * width of 20 pixals. Takes in the coordinates where the lower left point of 
 * the object will be.
 */
Character::Character (int x, int y) {
  CPoint temp = {x,y};
  location = temp;
  x_v = 0;
  y_v = 0;
  acceleration = 1;
  height = 20;
  width = 20;
}

/*
 * Secondary constructor. Creates a non-moving square object with a specified
 * lower left coordinate, height and width. 
 */
Character::Character (int x, int y, int p_height, int p_width) {
  CPoint temp = {x,y};
  location = temp;
  x_v = 0;
  y_v = 0;
  acceleration = 1;
  height = p_height;
  width = p_width;
}

// Sets grounded to 1. Use when the character has landed.
void Character::onGround(void) {
  grounded = 1;
}

// Sets grounded to 0. Use when the character is in the air for whatever reason.
void Character::offGround(void) {
  grounded = 0;
}

// Returns the velocity in the x direction.
int Character::getX_V(void) {
  return x_v;
}

// Returns the velocity in the y direction.
int Character::getY_V(void) {
  return y_v;
}

// Returns 1 if going right. Returns 0 otherwise.
int Character::isGoingRight(void) {
  return (getX_V() > 0);
}

// As above, but tests if going left.
int Character::isGoingLeft(void) {
  return (getX_V() < 0);
}

// As above, but test if going up.
int Character::isGoingUp(void) {
  return (getY_V() > 0);
}

// As above, but test if going down.
int Character::isGoingDown(void) {
  return (getY_V() < 0);
}

// Returns the height of the Character.
int Character::getHeight(void) {
  return height;
}

// Returns the width of the Character.
int Character::getWidth(void) {
  return width;
}

// Returns the coordinates to the upper right point of the Character.
CPoint Character::getUR(void) {
  CPoint temp = {location.x + width, location.y + height};
  return temp;
}

// Returns the coordinates to the lower right point of the Character.
CPoint Character::getLR(void) {
  CPoint temp = {location.x + width, location.y};
  return temp;
}

// Returns the coordinates to the upper left point of the Character.
CPoint Character::getUL(void) {
  CPoint temp = {location.x, location.y + height};
  return temp;
}

// Returns the coordinates to the lower left point of the Character.
CPoint Character::getLL(void) {
  CPoint temp = {location.x, location.y};
  return temp;
}

// Given a coordinate, sets the location of the character.
void Character::setCharacter(CPoint new_point){
  location.x = new_point.x;
  location.y = new_point.y;
}

// Accelerates downwards.
void Character::moveDown(void) {
  if (y_v > -10) {
    y_v -= acceleration;
  }
}

// Accelerates leftwards.
void Character::moveLeft(void) {
  if (x_v > -10) {
    x_v -= acceleration;
  }
}

// Accelerates rightwards.
void Character::moveRight(void) {
  if (x_v < 10) {
    x_v += acceleration;
  }
}

// Given an int, sets the x component of the velocity.
void Character::setX_V(int neoX_V) {
  x_v = neoX_V;
}

// Given an int, sets the y component of the velocity.
void Character::setY_V(int neoY_V) {
  y_v = neoY_V;
}

// Given a coordinate, sets both components of the velocity.
void Character::setV(CPoint p) {
  x_v = p.x;
  y_v = p.y;
}

/*
 * Updates location based on the object's current velocity.
 * The current "default ground" is at y = 40. So if the object is below 40, it 
 * won't move the object further down and sets the y component of the velocity
 * to 0. (This is poorly implemented. Expect this to change soon).
 */
void Character::move(void) {
  location.x += x_v;
  if(location.y > 40 || y_v > 0) {
    location.y += y_v;
  } else {
    y_v = 0;
    onGround();
  }
}

// A helper function for the collision detection. 
/* 
 * The distance_away variable is set to INT_MAX by default. If it sees that part
 * of distance_away has not been changed, it changes it to 0 and set_to to the
 * previously stated velocity. This is so if there has been no collision in that
 * direction, the velocity remains unchanged.
 */
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
/*
 * Called when this character collides with this character collides with another
 * character. If the objects haven't collided in the x or y directions, it sets
 * the values accordingly. move() moves this character so it is touching the
 * character it is colliding with and setV() then sets x_v and y_v to 0 if it
 * collides and maintains its previous velocity if it doesn't.
 * This function also makes sure move does not change the "grounded" variable.
 */ 
void Character::moveTo(CPoint distance_away, CPoint set_to) {
  ifUnchanged(&distance_away, &set_to);
  setV(distance_away);
  int temp_grounded = grounded;
  move();
  grounded = temp_grounded;
  setV(set_to);
}

// Function to emulate friction. When called, it slows the object along the x
// axis by one. 
void Character::slowX(void) {
  if (isGoingLeft()) {
    x_v++;
  } else if (isGoingRight()) {
    x_v--;
  }
}

// If on ground, jump.
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
  if (d == LL_CORNER) {
    point = getLL();
  } else if (d == LR_CORNER) {
    point = getLR();
  } else if (d == UL_CORNER) {
    point = getUL();
  } else if (d == UR_CORNER) {
    point = getUR();
  } else {
    printf("From printPoint in Character.cpp: What was that input? %d? What?\n",
	   d);
    return;
  }
  printf("x = %d\n y = %d\n", point.x, point.y);
}



