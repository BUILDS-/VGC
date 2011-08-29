#include <iostream>
#include "Character.h"

#ifndef __LEVEL_H
#define __LEVEL_H

using namespace std;

class Level {
  
  // Array of characters in level.
  Character** people;
  
  // Number of characters in level.
  int num_people;

  // Current length of array
  int max_size;

public:

  // Default constructor.
  Level(void);  

  // Returns the number of characters in the level.
  int getNumPeople();

  // Given an integer, returns a pointer to the corresponding character in the 
  // character array.
  Character * getCharacter(int);

  // Adds a character to the array and updates the number of people in the 
  // level.
  void addCharacter(Character *);


};

#endif
