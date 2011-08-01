
#ifndef __CHARACTER_H
#define __CHARACTER_H

#include <iostream>
#include <stdio.h>

using namespace std;

class Character{
  int x, y, x_v, y_v, height, width, grounded;
	int SPEED;
public:
	Character (void);
	Character (int,int);
	void onGround(void);
	void offGround(void);
	int getX(void);
	int getY(void);
	int getX_V(void);
	int getY_V(void);
	int getHeight(void);
	int getWidth(void);

	//redundant, but help my visual sensablities.
	//Gets the upper right corner's x.
	int getURX(void);
	//Gets the upper right corner's y.
	int getURY(void);
	//Gets the lower right corner's x. etc.
	int getLRX(void);
	int getLRY(void);
	int getULX(void);
	int getULY(void);
	void setCharacter(int,int);
	void setX_V(int);
	void setY_V(int);
	void moveDown(void);
	void moveLeft(void);
	void moveRight(void);
	void move(void);
	void slowX(void);
	void jump(void);
};

#endif
