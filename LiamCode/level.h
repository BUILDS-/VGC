#include <iostream>
#include "Character.h"

#ifndef __LEVEL_H
#define __LEVEL_H

using namespace std;

class Level {
  //Array of Characters
  Character** people;
  //number of characters in level
  int people_point;

public:
  Level(void);  int getPeople_point();
  Character * getCharacter(int);
  void addCharacter(Character *);


};

#endif
