
#ifndef __CHARACTER_H
#define __CHARACTER_H

#include <iostream>
#include <stdio.h>
#include <limits.h>
#include "types.h"
#include "consts.h"

using namespace std;

class Character{
  
  // Velocity in x and y directions
  int x_v, y_v;

  // Height and width of object
  int height, width;
  
  // Boolean. 1 if on ground. 0 if in the air.
  int grounded;

  // Default acceleration (increments velocity by SPEED whenever moving)
  int acceleration;

  // x and y coordinate of location.
  CPoint location;
  
 public:
  // Default constructor.
  Character (int,int);
  
  // Secondary constructor.
  Character (int,int,int,int);

  // Sets grounded to 1.
  void onGround(void);

  // Sets grounded to 0.
  void offGround(void);

  // Returns the velocity in the x direction.
  int getX_V(void);

  // Returns the velocity in the y direction.
  int getY_V(void);

  // Returns 1 if going right. Returns 0 otherwise.
  int isGoingRight(void);

  // As above, but tests if going left.
  int isGoingLeft(void);
  
  // As above, but tests if going up.
  int isGoingUp(void);

  // As above, but tests if going down.
  int isGoingDown(void);

  // Returns the height of the Character.
  int getHeight(void);

  // Returns the width of the Character.
  int getWidth(void);
  
  // Returns the coordinates to the upper right point of the Character.
  CPoint getUR(void);
  
  // Returns the coordinates to the lower right point of the Character.
  CPoint getLR(void);

  // Returns the coordinates to the upper left point of the Character.
  CPoint getUL(void);

  // Returns the coordinates to the lower left point of the Character.
  CPoint getLL(void);
  
  // Given a coordinate, sets the location of the character.
  void setCharacter(CPoint);

  // Accelerates downwards.
  void moveDown(void);
  
  // Accelerates leftwards.
  void moveLeft(void);

  // Accelerates rightwards.
  void moveRight(void);

  // Given an int, sets the x component of the velocity.
  void setX_V(int);

  // Given an int, sets the y component of the velocity.
  void setY_V(int);

  // Given a coordinate, sets both components of the velocity.
  void setV(CPoint);
  
  /*
   * Updates location based on the object's current velocity.
   * The current "default ground" is at y = 40. So if the object is below 40, it 
   * won't move the object further down and sets the y component of the velocity
   * to 0. (This is poorly implemented. Expect this to change soon).
   */
  void move(void);
  
  // A helper function for moveTo. 
  void ifUnchanged(CPoint*,CPoint*);
  
  // A helper function for collision detection
  void moveTo(CPoint,CPoint);

  // A function that emulates function. When called, it slows the object along 
  // the x axis by one. 
  void slowX(void);

  // If on ground, jump.
  void jump(void);

  // Debugging program. Given a number
  void printPoint(int);
};

#endif
