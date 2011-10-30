/*
 * Code By Liam Wang
 * <lzw@bu.edu>
 * This is the main method of the graphics test program.
 * It's job is to interprete user input and display the
 * characters and environments on screen.
 */

/*
 * VOCAB
 * mia = player character
 * frame = Keeps track of how many times display() has been called
 * keys[] = Array. When a key is pressed it switches the coorisponding
 *					0 to 1. When released, it goes back to 0.
 */

/*
 * Compile with:
 * g++ -Wall -I. -I/usr/X11R6/include -I/opt/local/include 
 * -L/opt/local/lib -L/usr/X11R6/lib -lglut -lglu -lgl -o main main.cpp
 * From site:
 * http://dirkraffel.com/2008/01/17/eclipse-cdt-on-mac-os-x/
 */



//The attributes of the screen                                                                                                                     

#include "main.h"

// If b is in between a and c, return 1. Otherwise return 0.
int isInBetween(int a, int b, int c) {
  if (((a-1) <= b && b <= (c+1)) || ((c-1) <= b && b <= (a+1))) {
    return 1;
  }
  return 0;
}


// Given the two defining points on two line segments labled a and b, this
// function figures out whether the line segments intersect.
int collide(int a1, int a2, int b1, int b2) {
  if ((b1 <= a1 && a2 <= b2) || 
     (a1 <= b1 && b1 <= a2) ||
     (a1 <= b2 && b2 <= a2)) {
    return 1;
  }
  return 0;
}


// If the mover will collide with the target while going down, return 1.
// Otherwise return 0. 
int collideDown(Character *mover, Character *target) {
  int a_y = mover->getLL().y + mover->getY_V();
  if (mover->isGoingDown() &&
     isInBetween(mover->getLL().y, target->getUL().y, a_y) &&
     collide(mover->getLL().x, mover->getLR().x, target->getUL().x,
	     target->getUR().x)) {
    mover->onGround();
    return 1;
  }
  return 0;
}

// If the mover will collide with the target while going up, return 1.
// Otherwise return 0. 
int collideUp(Character *mover, Character *target) {
  int a_y = mover->getUL().y + mover->getY_V();
  if (mover->isGoingUp() &&
     isInBetween(mover->getUL().y,target->getLL().y,a_y) && 
     collide(mover->getLL().x, mover->getLR().x, target->getUL().x, 
	     target->getUR().x)) {
    return 1;
  }
  return 0;
}

// If the mover will collide with the target while going right, return 1.
// Otherwise return 0. 
int collideRight(Character *mover, Character *target) {
  int a_x = mover->getUR().x + mover->getX_V();
  if(mover->isGoingRight() &&
     isInBetween(mover->getUR().x, target->getUL().x, a_x) &&
     collide(mover->getLR().y, mover->getUR().y, target->getLL().y, 
	     target->getUL().y)) {
    return 1;
  }
  return 0;
}

// If the mover will collide with the target while going left, return 1.
// Otherwise return 0. 
int collideLeft(Character *mover, Character *target) {
  int a_x = mover->getUL().x + mover->getX_V();
  if(mover->isGoingLeft() &&
     isInBetween(mover->getUL().x, target->getUR().x, a_x) &&
     collide(mover->getLR().y, mover->getUR().y, target->getLL().y, 
	     target->getUL().y)) {
    return 1;
  }
  return 0;
}

// Collision detection. 
void cDetection(Character * mover) {
  
  // For loop incrementer.
  int i;
  
  // Number of people in level (for the for loop)
  int end = level->getNumPeople();

  /*
   * If this character collides with another character, distance_away keeps
   * track of how far away the closest character is (the one this character
   * will collide with).
   *
   * If it does not collide, the default value will be changed to 0.
   */
  CPoint distance_away = {INT_MAX, INT_MAX};

  /*
   * If this character collides with another character, set_to will set
   * the appropriate component (x and y) of the velocity to zero. (you hit
   * something, you will come to a stop). Otherwise it will maintain velocity.
   */
  CPoint set_to = {0, 0};

  // CHANGE THIS SO THAT IT JUST DOESN'T RUN FOR THE MOVER'S OWN CHARACTER
  // For each character in the level.
  for (i = 0; i < end; i++) {
    Character * target = level->getCharacter(i);
    if (mover != target) {
      // If this character will collide with the target, temp keeps track of where
      // that character is.
      CPoint temp = {-1, -1};
      
      //Checks if collision occured
      int collide_vert = 0;
      int collide_hori = 0;
      
      // If they will collide above the mover, set the temp.y to the distance
      // between the two colliding characters.
      if (collideUp(mover, target)) {
	temp.y =target->getLL().y - mover->getUL().y - 1;
	collide_vert = 1;
	
	// If they will collide below this character, set the temp.y to the distance
	// between the two colliding characters.
      } else if (collideDown(mover,target)) {
	temp.y = 1 + target->getUL().y - mover->getLL().y;
	collide_vert = 1;
      }  
      
      // If they will collide to the right of this character, set the temp.x to
      // the distance between the two colliding characters.
      if(collideRight(mover, target)) {
	temp.x = target->getUL().x - mover->getUR().x - 1;
	collide_hori = 1;
	
	// If they will collide to the left of this character, set the temp.x to
	// the distance between the two colliding characters. 
      } else if (collideLeft(mover, target)) {
	temp.x = 1 + target->getUR().x - mover->getUL().x;
	collide_hori = 1;
      }
      
      // As long as the value temp has been set and the colliding character is
      // is closer than other characters this character may collide with, set it
      // as the distance to the closest character this character will collide with.
      if (collide_hori && temp.x < distance_away.x) {
	distance_away.x = temp.x;
      }
      
      if (collide_vert && temp.y < distance_away.y) {
	distance_away.y = temp.y;
      }
    }
  }
  // Moves the character to the cloestest colliding character, then stops it.
  // If no collision has occured, do not change velocity.
  mover->moveTo(distance_away, set_to);
}


/*
 * Gravity! Every frame a can character moves, gravity increases mia's downward
 * velocity by one (as long as the character is not grounded).
 */
void gravity(void) {
  int end = level->getNumPeople();
  int i;
  for (i = 0; i < end; i++) {
    Character * target = level->getCharacter(i);
    int y = (target->getLL()).y;
	 // As long as not on the floor (the floor being at y = 40)
	if (y > 40) {
	  target->moveDown();
	}
  }
}

// Figures out what all the object coordinates are and draws them to the
// screen.
void drawObjects(void) {
  int end = level->getNumPeople();
  int i;
  for (i = 0; i < end; i++) {
    Character* obj = level->getCharacter(i);
    int obj_x = (level->getCharacter(i)->getLL()).x;
    int obj_y = (level->getCharacter(i)->getLL()).y;

    boxRGBA(screen, ((Sint16) obj_x) - 1, 
			SCREEN_HEIGHT - (((Sint16) obj_y) + obj->getHeight() + 1),
			((Sint16) obj_x) + obj->getWidth() + 1, SCREEN_HEIGHT - (((Sint16) obj_y) - 1),
		  255, 255, 255, 255);		  
  }	
}

// Draws the grid on the screen.
void drawGrid(void) {
  /*  glPushMatrix();
  glBegin(GL_LINES);
  float i;
  for (i = 1.0f; i < 11.0f; i++) { 
    glVertex2f((width/10.0f)*i, 0.0f);
    glVertex2f((width/10.0f)*i, height + 0.0f);
    glVertex2f(0.0f, (height/10.0f)*i);
    glVertex2f(width, (height/10.0f)*i);
    
  }

  glEnd( );

  glPopMatrix();
  */
}


/*
 * Interpretes key presses and assosiates them with the appropriate actions.
 * (ie, press left and the player character will move left).
 * keys 100-103 are the arrow keys.
 * SlowX() is called as friction on the x plane
 */
 void moveMia(void) {
   char direction = '\0';
   // Move up, right, left, down.
   if (keys[SDLK_LEFT]) {
     direction = 'l';
     mia->moveLeft();
   } else if (keys[SDLK_UP]) {
     //Nope
     //mia->moveUp();
     mia->slowX();
  } else if (keys[SDLK_RIGHT]) {
     direction = 'r'; 
     mia->moveRight();
     
    // If you press the down key, the player will go down faster (if uncommented)
     /*  
   } else if (keys[103]) {
     direction = 'd';
     mia->moveDown();
     mia->slowX();
     */

   } else {
     mia->slowX();
   }
   
   if (keys[' ']) {
     direction = ' ';
    mia->jump();
   }
   int i;
   for (i = 0; i < level->getNumPeople(); i++) { 
     cDetection(level->getCharacter(i));
   }
  mia->move();
}


// Spawns levels and characters.
void spawn_level(void) {
  mia = new Character(100, 100);
  spawn = true;
  level = new Level();
  level->addCharacter(mia);
    
  Character * block = new Character(50, 200, 30, 500);
  level->addCharacter(block);
}

/*
 * Where the main loop is. For (mostly) every frame this function is called.
 * Spawns the character and level if either hasn't been made yet. Reads input
 * from the player and moves the player accordingly. Draws what the screen sees,
 * etc. This function is what organizes the control flow of the game. 
 */
void display(void) {
  // Keeps track of what frame we're on.
  frame++;
  
  // Spawns objects (if they haven't been spawned)
  if (!spawn) {
    spawn_level();
  }
  
  // Draws grid.
  drawGrid();
	
	
  // If player is pressing arrow key, move mia, then bring gravity
  // into effect. Only does it every 15th frame to keep from insanely
  // high acceleration.
  if (frame % 15 == 0) {
    gravity();
    moveMia();
    int end = level->getNumPeople();
    int i;
    for(i = 1; i < end; i++) {
      level->getCharacter(i)->move();
    }
  }
  
  // Draws Mia.
  drawObjects();
  
  //Update the screen
  

  if(SDL_Flip(screen) == -1) {
    return;
  }
  boxRGBA(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 255);
}

/*// Given a height and a width, this function changes the OpenGL window size.
void reshape(int width, int height)
{
  glViewport(0, 0, width, height);
  
  // glMatrixMode tells OpenGL which of the matrices it 
  // uses for projecting OpenGL coordinates onto pixels we want to modify
  glMatrixMode(GL_PROJECTION);
  
  // Resets the whole matrix to the identity matrix
  glLoadIdentity();
  
  // Parameters in order: left, right, bottom and top.
  // Note that in opengl the 0,0 is in the bottom left
  // (like in most math) rather than top left (like in
  // most graphics)
  gluOrtho2D(0, width, 0, height);
  glMatrixMode(GL_MODELVIEW);
}


// All it says is to draw another frame.
// This in addition to the fact this is called
// whenever nothing else is going on ensures maximum
// frame rate
void idle(void)
{
    glutPostRedisplay();
}
*/
// If a normal key is pressed, this is called.
void keyPressed (int key, int x, int y) {
	keys[key] = 1;
}

// If a key is released, this is called.
void keyReleased (int key, int x, int y) {
	keys[key] = 0;
}

// If a special key is pressed (arrow keys), this is called.
void keySpecial (int key, int x, int y) {
	if (key >= 0 && key < SDLK_LAST) {
		keys[key] = 1;
	}
}

// If a spacial key is released (arrow keys), this is called.
void keySReleased (int key, int x, int y) {
	if (key >= 0 && key < SDLK_LAST) {
		keys[key] = 0;
	}
	
}


// Main method. The openGL equivalent of a pilot checking 
// things off a list before taking off.
int main(int argc, char** argv)
{
  SDL_Event event;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
	  return 1;
	}

	//Creates screen                                                                                                                                                                          
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen == NULL) {
	  return 1;
	}



	//Sets the widnow caption                                                                                                                                                                 
	SDL_WM_SetCaption("VGC", NULL);
	
	//Unicode translation for Keyboard events. Overhead, and may not be useful
	//int SDL_EnableUNICODE(1);
	
	// Where the keys are stored.
	for (int i = 0; i < SDLK_LAST; i++) {
		keys[i] = 0;
	}
	

	int running = 1;
	while (running) {

	  while(SDL_PollEvent(&event)) {
		int code = event.key.keysym.sym;
		if (event.type == SDL_KEYUP) {

		  keyReleased(code,0,0);
		} else if (event.type == SDL_KEYDOWN) {
		  keyPressed(code,0,0);
		  if (code == SDLK_q) {
			running = 0;
		  }
		}	    
	  }
	  display();
	}
	
	
	
    return EXIT_SUCCESS;
}

