int cDetectionDown(Character * mover) {
  int i;
  int end = level->getNumPeople();
  CPoint* distance_away = NULL;
  CPoint set_to = {mover->getX_V(), mover->getY_V()};
  //CHANGE THIS SO THAT IT JUST DOESN'T RUN FOR THE MOVER'S OWN CHARACTER
  for (i = 1; i < end; i++) {
    Character * target = level->getCharacter(i);
    int temp_y, temp_x = 0;
    //Remember to set set_to.[x,y] to zero when there is a collision there.
    if(collideUp(mover, target)) {
      temp_y = target->getLL().y - mover->getUL().y;
      if (distance_away == NULL) {
	CPoint distance_away_value = {0, temp_y};
	distance_away = &distance_away_value;
	set_to.y = 0;
      } else if (temp_y < (*distance_away).y) {
	(*distance_away).y = temp_y;
      }
    } else if (collideDown(mover,target)) {
      mia->onGround();
      temp_y = target->getUL().y - mover->getLL().y;
      if (distance_away == NULL) {
	CPoint distance_away_value = {0, temp_y};
	distance_away = &distance_away_value;
	set_to.y = 0;
      } else if (temp_y < (*distance_away).y) {
	(*distance_away).y = temp_y;
      }
    }  
    if(collideRight(mover, target)) {
      temp_x = target->getUL().x - mover->getUR().x;
      if (distance_away == NULL) {
	CPoint distance_away_value = {temp_x, 0};
	distance_away = &distance_away_value;
	set_to.x = 0;
      } else if (temp_x < (*distance_away).x){
	(*distance_away).x = temp_x;
      }
    } else if (collideLeft(mover, target)) {
      temp_x = target->getUR().x - mover->getUL().x;
      if (distance_away == NULL) {
	CPoint distance_away_value = {temp_x, 0};
	distance_away = &distance_away_value;
	set_to.x = 0;
      } else if (temp_x < (*distance_away).x) {
	(*distance_away).x = temp_x;
      }
    }
  }
  if (distance_away != NULL) {
    mover->moveTo(*distance_away,set_to);
    return 0;
  }
  return 1;
