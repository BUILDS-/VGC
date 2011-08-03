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

int cDetectionUp(Character * mover) {
  int i, ax1, ay1, ax2, bx1, by1, bx2, a_y1, distance_away, end;
  end = level->getPeople_point();
  ax1 = mover->getULX();
  ay1 = mover->getULY();
  ax2 = mover->getURX();
  a_y1 = ay1 + mover->getY_V();

  for(i = 1; i < end; i++) {
    Character * target = level->getCharacter(i);
    bx1 = target->getLLX();
    by1 = target->getLLY();
    bx2 = target->getLRX();
    if(ay1 <= by1 && by1 <= a_y1 && ((bx1 <= ax1 && ax2 <= bx2) ||
				     (ax1 <= bx1 && bx1 <= ax2) ||
				     (ax1 <= bx2 && bx2 <= ax2))) {
      int temp = ay1 - by1;
      if (distance_away == -1 || temp < distance_away)
	distance_away = temp;
    }
  }
  if (distance_away != -1) {
    mover->setY_V(distance_away);
    mover->move();
    mover->setY_V(0);
    return 0;
  }
  return 1;

}


int cDetectionRight(Character * mover) {
  //printf("Debug: cDetectionRight\n");
  int end = level->getPeople_point();
  int i, ax1, ay1, ay2, a_x1, bx1, by1, by2;
  ax1 = mover->getURX();
  ay1 = mover->getURY();
  ay2 = mover->getLRY();
  a_x1 = ax1 + mover->getX_V();
  //printf("ax1 = %d, ay1 = %d, ax2 = %d, ay2 = %d\n", ax1, ay1, ax2, ay2);
  //printf("a_x1 = %d, a_y1 = %d, a_x2 = %d, a_y2 = %d\n", a_x1, a_y1, a_x2, a_y2);
  int distance_away = -1;
  //CHANGE THIS SO THAT IT JUST DOESN'T RUN FOR THE MOVER'S OWN CHARACTER
  for (i = 1; i < end; i++) {
    Character * target = level->getCharacter(i);
    bx1 = target->getULX();
    by1 = target->getULY();
    by2 = target->getLLY();
    //printf("bx1 = %d, by1 = %d, bx2 = %d, by2 = %d\n", bx1, by1, bx2, by2);
    
    
    if(ax1 <= bx1 && bx1 <= a_x1 && ((by2 <= ay2 && ay1 <= by1) || 
				     (ay2 <= by2 && by2 <= ay1) || 
				     (ay2 <= by1 && by1 <= ay1))) {
      int temp = bx1 - ax1;
      if (distance_away == -1 || temp < distance_away)
	distance_away = temp;
    }
  }
  if (distance_away != -1) {
    mover->setX_V(distance_away);
    mover->move();
    mover->setX_V(0);
    return 0;
  }
  return 1;

}

//Problems REDUNDANT. MAKE MORE EFFICIENT. ALSO DISTANCE AWAY IS WEIRD.
//ALSO IF STATEMENT MAY BE OVERLY COMPLEX
int cDetectionLeft(Character * mover) {
  int end = level->getPeople_point();
  int i, ax1, ay1, ay2, a_x1, bx1, by1, by2;
  ax1 = mover->getULX();
  ay1 = mover->getULY();
  ay2 = mover->getLLY();
  a_x1 = ax1 + mover->getX_V();
  //printf("ax1 = %d, ay1 = %d, ax2 = %d, ay2 = %d\n", ax1, ay1, ax2, ay2);
  //printf("a_x1 = %d, a_y1 = %d, a_x2 = %d, a_y2 = %d\n", a_x1, a_y1, a_x2, a_y2);
  int distance_away = 1;
  //CHANGE THIS SO THAT IT JUST DOESN'T RUN FOR THE MOVER'S OWN CHARACTER
  for (i = 1; i < end; i++) {
    Character * target = level->getCharacter(i);
    bx1 = target->getURX();
    by1 = target->getURY();
    by2 = target->getLRY();
    //printf("bx1 = %d, by1 = %d, bx2 = %d, by2 = %d\n", bx1, by1, bx2, by2);
    
    
    if(ax1 >= bx1 && a_x1 <= bx1 && ((by2 <= ay2 && ay1 <= by1) || 
				     (ay2 <= by1 && by1 <= ay1) || 
				     (ay2 <= by2 && by2 <= ay1))) {
      int temp = bx1 - ax1;

      //Distance away maintains the number of pixals between it and nearest 
      //object. FIX SO THAT THE DEFAULT DOESN'T FLUCTUATE
      if (distance_away == 1 || temp > distance_away)
	distance_away = temp;
    }

  }
  if (distance_away != 1) {
    mover->setX_V(distance_away);
    mover->move();
    mover->setX_V(0);
    return 0;
  }
  return 1;
}


//Problems REDUNDANT. MAKE MORE EFFICIENT. ALSO DISTANCE AWAY IS WEIRD.
//ALSO IF STATEMENT MAY BE OVERLY COMPLEX
int cDetectionDown(Character * mover) {
  //printf("Debug: cDetectionDown\n");
  int end = level->getPeople_point();
  int i, ax1, ay1, ax2, a_y1, bx1, by1, bx2;
  ax1 = mover->getLLX();
  ay1 = mover->getLLY();
  ax2 = mover->getLRX();
  //printf("mover->getY_V() = %d\n", mover->getY_V());
  a_y1 = ay1 + mover->getY_V();
  //printf("ax1 = %d, ay1 = %d, ax2 = %d, ay2 = %d\n", ax1, ay1, ax2, ay2);
  //printf("a_x1 = %d, a_y1 = %d, a_x2 = %d, a_y2 = %d\n", a_x1, a_y1, a_x2, a_y2);
  int distance_away = 1;
  //CHANGE THIS SO THAT IT JUST DOESN'T RUN FOR THE MOVER'S OWN CHARACTER
  for (i = 1; i < end; i++) {
    Character * target = level->getCharacter(i);
    bx1 = target->getULX();
    by1 = target->getULY();
    bx2 = target->getURX();
    //printf("bx1 = %d, by1 = %d, bx2 = %d, by2 = %d\n", bx1, by1, bx2, by2);
    
    if(a_y1 <= by1 && by1 <= ay1 && ((bx1 <= ax1 && ax2 <= bx2) || 
				     (ax1 <= bx1 && bx1 <= ax2) || 
				     (ax1 <= bx2 && bx2 <= ax2))) {
      int temp = by1 - ay1;
      if (distance_away == 1 || temp < distance_away)
	distance_away = temp;
    }

  }
  if (distance_away != 1) {
    mover->setY_V(distance_away);
    mover->move();
    mover->setY_V(0);
    mover->onGround();
    return 0;
  }
  return 1;
}


/*
 Gravity! Every some such frame (can't get global
 constants to work) gravity increases mia's downward
 velocity by one.
 */
void gravity(void) {
  int end = level->getPeople_point();
  int i;
  for (i = 0; i < end; i++) {
    Character * target = level->getCharacter(i);
    int x = target->getY();
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

  int end = level->getPeople_point();
  int i;
  for (i = 0; i < end; i++) {
    float mia_x = level->getCharacter(i)->getX();
    float mia_y = level->getCharacter(i)->getY();
	
    //float mia_size = 20
    
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
  
  //jump.
  if (keys[' ']) {
    direction = ' ';
    printf("jump\n");
    mia->jump();
    printf("Y_V = %d\n", mia->getY_V());
  }
  
  //Test to prove opengl can read two keys at once.
  if (keys[100]&&keys[101]) { printf("WINNER!!\n");}
  
  if(direction == 'r') 
    cDetectionRight(mia);
  else if (direction == 'l')
    cDetectionLeft(mia);
  else if (direction == 'd')
    cDetectionDown(mia);
  
  if(direction == ' ')
    printf("Y_V = %d\n", mia->getY_V());
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
		int end = level->getPeople_point();
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
