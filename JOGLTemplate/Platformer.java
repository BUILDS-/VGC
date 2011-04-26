//Packages: Netbeans, a couple IDEs use it. Edit it as necessary
//package org.platform;

//Yep, these are all necessary
import com.sun.opengl.util.Animator;
import com.sun.opengl.util.FPSAnimator;
import com.sun.opengl.util.GLUT;
import java.awt.Frame;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.media.opengl.GL;
import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLCanvas;
import javax.media.opengl.GLCapabilities;
import javax.media.opengl.GLEventListener;
import javax.media.opengl.glu.GLU;
import javax.swing.JFrame;
/*Hybridized code partially from Stan Sclaroff's CS480/680 class, Spring 2011*/

public class Platformer extends JFrame
  implements GLEventListener, KeyListener, MouseListener, MouseMotionListener {
	private final int DEFAULT_WINDOW_WIDTH =512;//Window size, change to your heart's desire
  	private final int DEFAULT_WINDOW_HEIGHT=512;

	//tools for setting up animation loop
  	private GLCapabilities capabilities;
 	private GLCanvas canvas;
  	private FPSAnimator animator;
  	private GLU glu;
  	private GLUT glut;
	//input tools
  	int last_x, last_y;
  	boolean rotate_world;
  	char[] pressedKeys;
	private Quaternion viewing_quaternion;
	//Variables for example animation.
	float increment;
	int angle;
	float scale;
  	public Platformer()
  	{
    	capabilities = new GLCapabilities();
    	capabilities.setDoubleBuffered(true);  // Enable Double buffering
		//various listeners, pretty straightforward
    	canvas  = new GLCanvas(capabilities);
    	canvas.addGLEventListener(this);
	    canvas.addMouseListener(this);
    	canvas.addMouseMotionListener(this);
    	canvas.addKeyListener(this);
    	canvas.setAutoSwapBufferMode(true); // true by default. Just to be explicit

    	getContentPane().add(canvas);


    	animator = new FPSAnimator(canvas, 60); // drive the display loop at 60 FPS
		//tools for modeling - typically actual modeling will happen in model classes
    	glu  = new GLU();
    	glut = new GLUT();

    	setTitle("Jellybeans");//Liam
    	setSize( DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);//inherited from JFrame
    	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//basic
    	setVisible(true);

    	viewing_quaternion = new Quaternion();
		pressedKeys = new char[128];//Big enough, and a pleasing number

		//these numbers will produce a nice smooth animation.
		increment = 0.005f;
		angle = 0;
		scale = 0.5f;
  	}
  	public void run()//will handle all the start up for us
  	{
  		animator.start();
  	}

  	public static void main( String[] args )
  	{
    	Platformer P = new Platformer();
    	P.run();
  	}
	//initialization, not my code
  	public void init( GLAutoDrawable drawable)
  	{
    	GL gl = drawable.getGL();
    	/* set up for shaded display of the world, non-vital*/
    	float light0_position[] = {1,1,1,0};
    	float light0_ambient_color[] = {0.25f,0.25f,0.25f,1};
    	float light0_diffuse_color[] = {1,1,1,1};

    	gl.glPolygonMode(GL.GL_FRONT,GL.GL_FILL);
    	gl.glEnable(GL.GL_COLOR_MATERIAL);
    	gl.glColorMaterial(GL.GL_FRONT,GL.GL_AMBIENT_AND_DIFFUSE);
	
    	gl.glClearColor(0.0f,0.0f,0.0f,0.0f);
    	gl.glShadeModel(GL.GL_SMOOTH);
    	gl.glClearAccum(0.0f,0.0f,0.0f,0.0f);
    	/* set up the light source */
    	gl.glLightfv(GL.GL_LIGHT0, GL.GL_POSITION, light0_position, 0);
    	gl.glLightfv(GL.GL_LIGHT0, GL.GL_AMBIENT, light0_ambient_color, 0);
    	gl.glLightfv(GL.GL_LIGHT0, GL.GL_DIFFUSE, light0_diffuse_color, 0);
	
    	/* turn lighting and depth buffering on */
    	gl.glEnable(GL.GL_LIGHTING);
    	gl.glEnable(GL.GL_LIGHT0);
    	gl.glEnable(GL.GL_DEPTH_TEST);
    	gl.glEnable(GL.GL_NORMALIZE);

  	}	

    public void display(GLAutoDrawable drawable) {
        GL gl = drawable.getGL();//the gl object provides basic drawing, lighting, texture, modeling, etc....
        gl.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT);//reseting
        gl.glColorMask(true,true,true,false);//determines which r,g,b,a  actually get updated

        gl.glMatrixMode(GL.GL_MODELVIEW);
        gl.glLoadIdentity();//gl has a master matrix for transformations, reset here
        // rotate the world and then do drawing
        glu.gluLookAt(0,0,6,0,0,0,0,1,0);
        gl.glMultMatrixf( viewing_quaternion.to_matrix(), 0 );
		
		//around here, place logic code based on which keys are pressed - found via the array pressedKeys

		if(scale < 0.1 || scale > 1.2)//object should bounce in size
			increment *= -1;
		scale += increment;
		angle++;
		angle %= 360;//technically unneccessary, just avoids overflow
		gl.glPushMatrix();//pushing means that these matrix transforms won't stick past pop
			gl.glColor3f(0.15f, 0.8f, 0.6f);//color set
			gl.glRotatef(90, 1, 0, 0);//The top-most transform happens first
			gl.glRotatef(angle, 0, 1, 0);
			gl.glTranslatef(0, -1*scale/2, 0);
			glut.glutSolidCylinder(scale, 2*scale, 36, 18);//r, h, these two values are detail of cylinder drawing (don't touch)
		gl.glPopMatrix();//GL will now forget those rotation calls
    }
	//not necessary to mess with for simple programs.
    public void displayChanged(GLAutoDrawable drawable, boolean modeChanged, boolean deviceChanged) {
    }
	//original code, not imne
    public void reshape(GLAutoDrawable drawable, int x, int y,
                            int width, int height)
  {

    // Change viewport dimensions
    GL gl = drawable.getGL();

    // Prevent a divide by zero, when window is too short (you cant make a
    // window of zero width).
    if(height == 0) height = 1;

    double ratio = 1.0f * width / height;

    // Reset the coordinate system before modifying
    gl.glMatrixMode(GL.GL_PROJECTION);
    gl.glLoadIdentity();

    // Set the viewport to be the entire window
    gl.glViewport(0, 0, width, height);

    // Set the clipping volume
    glu.gluPerspective(25,ratio,0.1,100);

    // Camera positioned at (0,0,6), look at point (0,0,0), Up Vector (0,1,0)
    glu.gluLookAt(0,0,6,0,0,0,0,1,0);

    gl.glMatrixMode(GL.GL_MODELVIEW);

  }
    public void keyTyped(KeyEvent key)
  {

 }
/*Try it - holding a key in java registers keypressed/keyreleased events in rapid alternating succession.
Another problem is that if a new key is hit when a second is still down, Java cannot handle that.*/
	//worst case O(n) insert of a key, but trivial on any decent machine.
  public void keyPressed(KeyEvent key)
  {
	//Don't ask how, but due to how java handles key, if a second key is hit, the first is still in the array.
	//unlike the basic implementation, which just forgets the first key is being hit.
	for(int i = 0; i < pressedKeys.length && pressedKeys[i] != key.getKeyChar(); i++)
	{
		if(pressedKeys[i] == 0)
			pressedKeys[i] = key.getKeyChar();
	}
  }
	//O(n) removal of a key
  public void keyReleased(KeyEvent key)
  {
	//any key actually being released fires this event, even if it was hit three keys ago.
	int i;
	for(i = 0; i < pressedKeys.length && pressedKeys[i] != key.getKeyChar(); i++);
	if(i < pressedKeys.length)
		pressedKeys[i] = 0;
  }

  //**************************************************
  // MouseListener and MouseMotionListener Interfaces (Original code)
  //**************************************************
  public void mouseClicked(MouseEvent mouse)
  {

  }
  //from here down is unmodified
  public void mousePressed(MouseEvent mouse)
  {
    int button = mouse.getButton();
    if ( button == MouseEvent.BUTTON1 )
    {
      last_x = mouse.getX();
      last_y = mouse.getY();
      rotate_world = true;
    }
  }

  public void mouseReleased(MouseEvent mouse)
  {
    int button = mouse.getButton();
    if ( button == MouseEvent.BUTTON1 )
    {
      rotate_world = false;
    }
  }

  public void mouseMoved( MouseEvent mouse)
  {
  }

  	public void mouseDragged( MouseEvent mouse )
  	{
    	if (rotate_world)
		{
      		// vector in the direction of mouse motion
      		int x = mouse.getX();
      		int y = mouse.getY();
      		float dx = x - last_x;
      		float dy = y - last_y;

      		// spin around axis by small delta
      		float mag = (float) Math.sqrt( dx*dx + dy*dy );
      		float[] axis = new float[3];
      		axis[0] = dy/ mag;
      		axis[1] = dx/ mag;
      		axis[2] = 0.0f;

      		// calculate appropriate quaternion
      		float viewing_delta = 3.1415927f / 180.0f; // 1 degree
      		float s = (float) Math.sin( 0.5f*viewing_delta );
      		float c = (float) Math.cos( 0.5f*viewing_delta );

      		Quaternion Q = new Quaternion( c, s*axis[0], s*axis[1], s*axis[2]);
      		viewing_quaternion = Q.multiply( viewing_quaternion );

      		// normalize to counteract acccumulating round-off error
      		viewing_quaternion.normalize();

      		// Save x, y as last x, y
      		last_x = x;
      		last_y = y;
    	}
  	}

  	public void mouseEntered( MouseEvent mouse)
  	{
  	}

  	public void mouseExited( MouseEvent mouse)
 	{
  	}
	//can be used to find keys in the array (O(n))
	public boolean activeKey(char c)
	{
		for(int i = 0; i < pressedKeys.length; i++)
		{
			if(c == pressedKeys[i])
				return true;
		}
		return false;
	}
}

