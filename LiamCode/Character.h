
#ifndef __CHARACTER_H
#define __CHARACTER_H

#include <iostream>
#include <stdio.h>
#include "types.h"

using namespace std;

class Character{
  int x_v, y_v, height, width, grounded;
  int SPEED;
  CPoint location;

public:
	Character (void);
	Character (int,int);
	Character (int,int,int,int);
	void onGround(void);
	void offGround(void);
	int getX_V(void);
	int getY_V(void);
	int isGoingRight(void);
	int isGoingLeft(void);
	int getHeight(void);
	int getWidth(void);

	//redundant, but help my visual sensablities.
	//Gets the upper right corner's coordinates.
	CPoint getUR(void);

	//Gets the lower right corner's coordinates. etc.
	CPoint getLR(void);
	CPoint getUL(void);
	CPoint getLL(void);
	void setCharacter(int,int);
	void setX_V(int);
	void setY_V(int);
	void setV(CPoint);
	void moveDown(void);
	void moveLeft(void);
	void moveRight(void);
	void move(void);
	void moveTo(CPoint,CPoint);
	void slowX(void);
	void jump(void);
	
	void printPoint(int);
};

#endif
