/*
 Code By Liam Wang
 <lzw@bu.edu>
 This is the main method of the graphics test program.
 It's job is to interprete user input and display the
 characters and environments on screen.
 */

/*
 VOCAB
 mia = player character
 frame = Keeps track of how many times display() has been called
 keys[] = Array. When a key is pressed it switches the coorisponding
					0 to 1. When released, it goes back to 0.
 */

/*
 * Compile with:
 * g++ -Wall -I. -I/usr/X11R6/include -I/opt/local/include -L/opt/local/lib -L/usr/X11R6/lib -lglut -lglu -lgl -o main main.cpp
 * From site:
 * http://dirkraffel.com/2008/01/17/eclipse-cdt-on-mac-os-x/
 */

#include "main.h"

int isInBetween(int a, int b, int c) {
  if ((a <= b && b <= c) || (c <= b && b <= a)) {
    return 1;
  }
  return 0;
}

int collide(int a1, int a2, int b1, int b2) {
  if((b1 <= a1 && a2 <= b2) || 
     (a1 <= b1 && b1 <= a2) ||
     (a1 <= b2 && b2 <= a2)) {
    return 1;
  }
  return 0;
}


int cDetectionRight(Character * mover) {
  int end = level->getNumPeople();
  int i, a_x1, a_x2 = 0;
  CPoint* distance_away = NULL;
  CPoint set_to = {0,mover->getY_V()};
  a_x1 = mover->getUR().x + mover->getX_V();
  a_x2 = mover->getUL().x + mover->getX_V();
  //CHANGE THIS SO THAT IT JUST DOESN'T RUN FOR THE MOVER'S OWN CHARACTER
  for (i = 1; i < end; i++) {
    Character * target = level->getCharacter(i);
    if(((mover->isGoingRight() && 
	 isInBetween(mover->getUR().x, target->getUL().x, a_x1)) || 
	(mover->isGoingLeft() && 
	 isInBetween(mover->getUL().x, target->getUR().x, a_x2))) && 
       collide(mover->getLR().y,mover->getUR().y,target->getLL().y,target->getUL().y)) {
      int temp;
      if(mover->isGoingRight()) {
	temp = target->getUL().x - mover->getUR().x;
      } else {
	temp = target->getUR().x - mover->getUL().x;
      }
      if (distance_away == NULL || temp < (*distance_away).x) {
	CPoint distance_away_value = {temp, 0};
	distance_away = &distance_away_value;
      }
    }
  }
  if (distance_away != NULL) {
    mover->moveTo(*distance_away,set_to);
    return 0;
  }
  return 1;

}


//Problems REDUNDANT. MAKE MORE EFFICIENT. ALSO DISTANCE AWAY IS WEIRD.
//ALSO IF STATEMENT MAY BE OVERLY COMPLEX
int cDetectionDown(Character * mover) {
  int end = level->getNumPeople();
  int i, a_y1, a_y2 = 0;
  CPoint* distance_away = NULL;
  CPoint set_to = {mover->getX_V(),0};
  a_y1 = mover->getLL().y + mover->getY_V();
  a_y2 = mover->getUL().y + mover->getY_V();
  //CHANGE THIS SO THAT IT JUST DOESN'T RUN FOR THE MOVER'S OWN CHARACTER
  for (i = 1; i < end; i++) {
    Character * target = level->getCharacter(i);
    if(((mover->getY_V() < 0 && isInBetween(mover->getLL().y,target->getUL().y,a_y1)) || 
	(mover->getY_V() > 0 && isInBetween(mover->getUL().y,target->getLL().y,a_y2))) && 
       collide(mover->getLL().x,mover->getLR().x,target->getUL().x,target->getUR().x)) {
      int temp; 
      if(0 < mover->getY_V()) {
	temp = target->getLL().y - mover->getUL().y;
      } else {
	temp = target->getUL().y - mover->getLL().y;
      }
      if (distance_away == NULL || temp < (*distance_away).y) {
	CPoint  distance_away_value = {0, temp};
	distance_away = &distance_away_value;
      }
    }
  }
  if (distance_away != NULL) {
    mover->moveTo(*distance_away,set_to);
    mover->onGround();
    return 0;
  }
  return 1;
}


/*
 Gravity! Every some such frame (can't get global
 constants to work gravity increases mia's downward
 velocity by one.
 */
void gravity(void) {
  int end = level->getNumPeople();
  int i;
  for (i = 0; i < end; i++) {
    Character * target = level->getCharacter(i);
    int x = (target->getLL()).x;
	 //as long as not on the floor (the floor being
	 //at x = 40
	if (x > 40) {
	  target->moveDown();
	  cDetectionDown(mia);
		//printf("Now at %d\n", target->getY());
	}
  }
}

//Draws Mia
void drawMia(void) {

  int end = level->getNumPeople();
  int i;
  for (i = 0; i < end; i++) {
    int mia_x = (level->getCharacter(i)->getLL()).x;
    int mia_y = (level->getCharacter(i)->getLL()).y;

    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex2f(mia_x, mia_y);
    glVertex2f(mia_x + mia->getWidth(), mia_y);
    glVertex2f(mia_x + mia->getWidth(), mia_y + mia->getHeight());
    glVertex2f(mia_x, mia_y + mia->getHeight());
    glEnd();
  }	
}

//Draws the grid.
void drawGrid(void) {
	glPushMatrix();
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
}

//keys 100-103 are the arrow keys.
//SlowX() is called as friction on the x plane
void moveMia(void) {
  char direction = '\0';
  //Move up, right, left, down.
  if (keys[100]) {
    direction = 'l';
    mia->moveLeft();
  } else if (keys[101]) {
    //Nope
    //mia->moveUp();
    mia->slowX();
  } else if (keys[102]) {
    direction = 'r'; 
    mia->moveRight();
  } else if (keys[103]) {
    direction = 'd';
    mia->moveDown();
    mia->slowX();
  } else {
    mia->slowX();
  }
  
  if (keys[' ']) {
    direction = ' ';
    mia->jump();
  }
  
  if (0 < mia->getX_V()) {
    cDetectionRight(mia);
  } else if (0 > mia->getX_V()) {
    cDetectionRight(mia);
  } else if (0 < mia->getY_V()) {
    cDetectionDown(mia);
  } else if (0 > mia->getY_V()) {
    cDetectionDown(mia);
  }
  mia->move();
}
 
/*
 Where the main loop is. For (mostly) every frame
 this function is called.
 */
void display(void)
{
	//Keeps track of what frame we're on.
	frame++;
	//Clears the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	
	//Spawns Mia (if she hasn't been spawned)
	if (!spawn) {
		//Spawns at pixal x = 200 and y = 200
		mia = new Character(200, 200);
		spawn = true;
		level = new Level();
		level->addCharacter(mia);
		
		Character * block = new Character(100, 100);
		level->addCharacter(block);

	}

	//Draws grid.
	drawGrid();
	
	
	//Next paragraph in case we need to know the frame rate later.
	//If this is the first frame, set the global frametime variable
	if (lastFrameTime == 0)
    {
        lastFrameTime = glutGet(GLUT_ELAPSED_TIME);
    }
	int now = glutGet(GLUT_ELAPSED_TIME);
	lastFrameTime = now;

	//If player is pressing arrow key, move mia, then bring gravity
	//into effect. Only does it every 50th frame to keep from insanely
	//high acceleration and the ilk.
	//CAN'T MAKE GLOBAL CONSTANTS.
	if (frame % 15 == 0) {
		gravity();
		moveMia();
		int end = level->getNumPeople();
		int i;
		for(i = 1; i < end; i++) {
		  level->getCharacter(i)->move();
		}
	}
	
	//Draws Mia.
	drawMia();
	
	//then swaps the back buffer onto the screen
	glutSwapBuffers();
}

//Simply tells OpenGL the window size has changed.
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    
	//glMatrixMode tells OpenGL which of the matrices it 
	//uses for projecting OpenGL coordinates onto pixels we want to modify
    glMatrixMode(GL_PROJECTION);
	
	//Resets the whole matrix to the identity matrix
    glLoadIdentity();
	
	//Parameters in order: left, right, bottom and top.
	//Note that in opengl the 0,0 is in the bottom left
	//(like in most math) rather than top left (like in
	//most graphics)
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}


//All it says is to draw another frame.
//This in addition to the fact this is called
//whenever nothing else is going on ensures maximum
//frame rate
void idle(void)
{
    glutPostRedisplay();
}

//If a normal key is pressed, this is called.
void keyPressed (unsigned char key, int x, int y) {
	keys[key] = 1;
}

//If a key is released, this is called.
void keyReleased (unsigned char key, int x, int y) {
	keys[key] = 0;
}

//If a special key is pressed (arrow keys), this is called.
void keySpecial (int key, int x, int y) {
	if (key >= 0 && key < 256) {
		keys[key] = 1;
	}
}

//If a spacial key is released (arrow keys), this is called.
void keySReleased (int key, int x, int y) {
	if (key >= 0 && key < 256) {
		keys[key] = 0;
	}
	
}


//Main method. The openGL equivalent of a pilot checking 
//things off a list before taking off.
int main(int argc, char** argv)
{
	
	//Where the keys are stored.
	for (int i = 0; i < 256; i++) {
		keys[i] = 0;
	}
	
	//Passes command-line into GLUT (all you need to 
	//know is that the init function needs them) Always call this function first or 
	//bad stuff will happen.
	glutInit(&argc, argv);
    
	//Our window should be in red-green-blue-alpha, double buffered to avoid
	//flickering when drawing, and have a depth buffer to ensure 3D objects
	//overlap correctly regardless of the order they're drawn in. 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	
	//Size of our window (width = 640 pixels -- height = 480 pixels)
	glutInitWindowSize(width, height);
    
	//Makes the program and titles the window
	glutCreateWindow("Game");
    
	//Called whenever it's time to call a frame
	glutDisplayFunc(display);
	
	
	//Called whenever you want to resize the window
	glutReshapeFunc(reshape);
	
	//Holding down a key won't register another key pressed.
	glutIgnoreKeyRepeat(1);
	
	//Yes, we will press keys
	glutKeyboardFunc(keyPressed);
	
	//Yes, we will release keys
	glutKeyboardUpFunc(keyReleased);
	
	//Yes, we may even press special keys
	glutSpecialFunc(keySpecial);
	
	//And yes, we might even release those
	glutSpecialUpFunc(keySReleased);
	
	//Called whenever GLUT isn't doing anything else
	glutIdleFunc(idle);
	
	//Tells the GLUT to go do the important stuff. (display function)
	glutMainLoop();
	
	//glutMianLoop never ends so this is redundant, but this satisfies the compiler
    return EXIT_SUCCESS;
}
