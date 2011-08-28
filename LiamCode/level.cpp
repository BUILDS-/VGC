#include "level.h"
#include "consts.h"

// Default constructor. Makes the default max number of characters 10 and the
// current number of people zero.
Level::Level(void) {
  people = new Character *[DEFAULT_MAX_NUM_CHARACTERS];
  num_people = 0;
}

// Returns the number of characters in the level.
int Level::getNumPeople() {
  return num_people;
}

// Given an integer, returns a pointer to the corresponding character in the 
// character array.
Character * Level::getCharacter(int i) {
  return people[i];
}

// Adds a character to the array and updates the number of people in the level.
void Level::addCharacter(Character* dude) {
  people[num_people] = dude;
  num_people++;
}
