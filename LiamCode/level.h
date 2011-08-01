#include <iostream>
#include "Character.h"

#ifndef __LEVEL_H
#define __LEVEL_H

using namespace std;

class Level {
  Character** people;
  int people_point;

public:
  Level(void);  int getPeople_point();
  Character * getCharacter(int);
  void addCharacter(Character *);


};

#endif
