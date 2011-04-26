#include <iostream>

using namespace std;

class Character{
	int x, y, x_v, y_v;
	int SPEED;
public:
	Character (void);
	Character (int,int);
	int getX(void);
	int getY(void);
	int getX_V(void);
	int getY_V(void);
	void setCharacter(int,int);
	void moveDown(void);
	void moveLeft(void);
	void moveRight(void);
	void move(void);
	void slowX(void);
	void jump(void);
};

