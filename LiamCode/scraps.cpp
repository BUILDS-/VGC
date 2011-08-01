//Complicated.
//Projects where the object is about to move. If there is an object between
//it and where it's going to be, return 0. If not, return 1;
int checkLocation(Character * mover) {
  char going_right = 0;

  //if the object is moving to the right
  if(0 < getX_V()) {
    going_right = 1;

    //the left x coordinate is the right most side of the object.
    axl = mover->getXLR();
    //and the right x coordinate is the right most side of the projected
    //location of the object
    axr = axl + mover->getX_V();
  
  //If the object is moving to the left.
  } else {
    
    //The right x coordinate is the left most side of the object.
    axr = getX();

    //The left x coordinate is the left most side of the projected location
    //of the object.
    axl = axr + mover->getX_V();
  }

  //For all the characters on the map
  for(all of the Characters) {
    
    //sets the x coordinate of the potential obstacle.
    if (going_right)
      bx = getX();
    else
      bx = getXLR();

    if(axl < bx && bx < axr) {
      //DO STUFF TO MAKE SURE IT'S CLOSEST.
      return 0;
    }

  }

}
