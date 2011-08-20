#include <iostream>
#include "Character.h"

#ifndef __LEVEL_H
#define __LEVEL_H

using namespace std;

class Level {
  //Array of Characters
  Character** people;
  //number of characters in level
  int num_people;

public:
  Level(void);  
  int getNumPeople();
  Character * getCharacter(int);
  void addCharacter(Character *);


};

#endif
