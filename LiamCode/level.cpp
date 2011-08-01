#include "level.h"


//Constructor

Level::Level(void) {

  people = new Character *[10];
  people_point = 0;

}

int Level::getPeople_point() {
  return people_point;
}

Character * Level::getCharacter(int i) {
  return people[i];
}

void Level::addCharacter(Character* dude) {

  people[people_point] = dude;
  people_point++;

}
