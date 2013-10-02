#include <X11/X.h>		// X window system
#include <X11/Xlib.h>	// Libraries for X window system
#include <GL/glx.h>		// OpenGL Extension for X window system

Display 				*dpy;
Window 					root;
GLint 					att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None }; // Defining the needed OpenGL capabilities for our program. More possible options can be found in GL/glx.h
XVisualInfo 			*vi;
Colormap 				cmap;
XSetWindowAttributes	swa;
Window 					win;
GLXContext 				glc;
XWindowAttributes 		gwa;
XEvent 					xev;




void initializeWindow() {
	dpy = XOpenDisplay(NULL); 			// Opening graphical output on local computer
	root = DefaultRootWindow(dpy);		// Creating handle to root window (the desktop background window)
	vi = glXChooseVisual(dpy, 0, att); 	// Assigning an available visual
	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone); 	// Creating colormap for the window

	/* Initializing XSetWindowAttributes structure
	* 	The The colormap we created is used
	* 	The window shall respond to Exposure and KeyPress events
	*/
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;
}




void displayWindow() {
	/* Creating window
	*  The arguments are:
	* 	Displaypointer, determining which display to create window on: dpy
	* 	The handle of the root window passed as the parent window: root
	* 	Initial x,y positions of the window; usually ignored: 0, 0	
	* 	Window width and height in pixels: 600, 600
	* 	Border width: 0
	* 	Depth, defined in XVisualInfo structure *vi: vi->depth
	* 	Window type: InputOutput
	* 	bitwise-OR of the values CWColormap and CWEventMask. This tells the X server which 
	*		fields of the XSetWindowAttributes structure swa were filled by the program and 
	* 		should be taken into account when creating the window: CWColormap | CWEventMask
	* 	Pointer to the structure itself: &swa
	*  Returns a window id (int)
	*/
	win = XCreateWindow(dpy, root, 0, 0, 1200, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);


	XMapWindow(dpy, win); 		//Makes the window appear
	XStoreName(dpy, win, "Exercise 3: Symmetry 2"); // Change the string in the title bar
}
 



void createContext_enableDepthTest() {
	// Create GL context to enable displaying 3D things and bind it to the window
	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);

	// Enable depth test bebause we want to use depth buffering (GLX_DEPTH_SIZE)
	glEnable(GL_DEPTH_TEST); 
}




void startProgram() {
	while(1) { // Start infinite loop
		XNextEvent(dpy, &xev); 		// Blocks program execution untill an ExposureMask or KeyPressMask event occurs
		
		/* If event is an Exposure Event (an event generated when the system thinks a window should be updated): 
		* 	Get information about current window size
		* 	Resize viewport 
		* 	Draw the thing
		* 	Swap the buffer (we're drawing a double buffered visual)
		*/
		if(xev.type == Expose) {
				XGetWindowAttributes(dpy, win, &gwa);
				glViewport(0, 0, gwa.width, gwa.height);
				DrawGLfigs(); 
				glXSwapBuffers(dpy, win);
		}
		
		/* If the event is a keypress, the program is terminated:
		* 	GL context binding to the window is released
		* 	GL context is destroyed
		* 	Kill the window
		* 	Close the display
		* 	Exit the program
		*/		
		else if(xev.type == KeyPress) {
				glXMakeCurrent(dpy, None, NULL);
				glXDestroyContext(dpy, glc);
				XDestroyWindow(dpy, win);
				XCloseDisplay(dpy);
				exit(0);
		}
	} 
}