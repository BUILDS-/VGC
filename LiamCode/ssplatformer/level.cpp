#include "level.h"
#include "consts.h"

// Default constructor. Makes the default max number of characters 10 and the
// current number of people zero.
Level::Level(void) {
  max_size = DEFAULT_MAX_NUM_CHARACTERS;
  people = new Character *[max_size];
  num_people = 0;
}

// Returns the number of characters in the level.
int Level::getNumPeople() {
  return num_people;
}

// Given an integer, returns a pointer to the corresponding character in the 
// character array.
Character * Level::getCharacter(int i) {
  if (i < num_people) {
    return people[i];
  } else {
    printf("In Level.cpp: people[%d], doesn't exist.\n", i);
    return NULL;
  }
}

// Adds a character to the array and updates the number of people in the level.
// This function dynamically reallocates space for the array when the array is 
// full.
void Level::addCharacter(Character* dude) {
  if (num_people == max_size) {
    int i;
    Character** temp = new Character *[max_size * 2];
    for (i = 0; i < max_size; i++) {
      temp[i] = people[i];
    }
    max_size *= 2;
    delete people;
    people = temp;
  }
  
  people[num_people] = dude;
  num_people++;

}
