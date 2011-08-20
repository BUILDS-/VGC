#include "level.h"


//Constructor

Level::Level(void) {

  people = new Character *[10];
  num_people = 0;

}

int Level::getNumPeople() {
  return num_people;
}

Character * Level::getCharacter(int i) {
  return people[i];
}

void Level::addCharacter(Character* dude) {

  people[num_people] = dude;
  num_people++;

}
