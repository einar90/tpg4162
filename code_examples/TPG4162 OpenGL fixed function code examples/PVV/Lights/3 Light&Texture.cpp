#include "dgl.h"
#include <stdlib.h>
#include <math.h>
#include <glut.h>

// TPG4162 SAMPLE CODE COMBINING TEXTURE MAPPING AND LIGHTING TO IMPROVE VISUAL EFFECT. 
// ILLUSTRATES THAT TEXTURE AND TEXTURE COORDINATES MUST MATCH TO GIVE CORRECT IMPRESSION FOR PATTERNED OBJECTS
// AND THE USE OF MIPMAPS TO AVOID SOME FLICKERING ARTIFACTS

void setupLighting();
void setupTexture();


void main()
{
	dglWindowOpen("Light example", 900, 750, false);    // create a GL-enabled window of given pixel size

	setupLighting();
	setupTexture();

	glEnable(GL_DEPTH_TEST);
 
	// variables to control object rotation
	float	rotAngle = 0.0f;
	unsigned long long int prevTime = dglGetCurrentTime();

	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )		// begin the main loop. Keep on running until user presses escape
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(30, 900.0/750.0, 1.0, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear screen black before drawing

		glRotatef(rotAngle, 0, 0.2, 0.2);
		glutSolidTeapot(1.5);
		
		dglSwapBuffers();	// frame is done and can be shown on the screen
		
		rotAngle += 0.02f * (dglGetCurrentTime() - prevTime);				// rotation speed 0.02 (degrees per millisecond)
		prevTime = dglGetCurrentTime();
	}

	dglWindowClose();
}





void setupLighting()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Homogenous coordinates for light position. Transformed by the current modelview matrix, just as for vertices.
	float position[] = { 0.0f, 10.0f, 10.0f, 0.0f };

	float ambient[] =  { 0.30f, 0.30f, 0.30f, 1.0f };	  // not too bright
	float diffuse[] =  { 0.95f, 0.95f, 0.85f, 1.0f };     // yellow-whiteish
	float specular[] = { 1.00f, 1.00f, 1.00f, 1.0f };	  // white and shiny

	// set up light zero 
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// set up material parameters for our teapot
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glMaterialfv(GL_FRONT, GL_AMBIENT,  ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,  diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
}




void setupTexture()
{
	// texture coordinates must be designed to  purpose, sample code uses a convenience function to load and setup texture
	struct DGLImage* img = dglCreateImage("brick.jpeg");        // looks good, seems to continue nicely across patch borders (where texture coordinates are discontinuous)
	//struct DGLImage* img = dglCreateImage("islamic.jpg");		// visual artifacts on the patch borders due to discontinuous texture coordinates
	//struct DGLImage* img = dglCreateImage("lenna.png");		// used to visualize the borders of patches and the discontinuity of texture coordinates
 
	GLuint texobj;
	glGenTextures(1, &texobj);
	glBindTexture(GL_TEXTURE_2D, texobj);
	glTexImage2D(GL_TEXTURE_2D, 0, img->format, img->width, img->height, 0, img->format, GL_UNSIGNED_BYTE, img->pointer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_CLAMP gives artifacts
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// creation of mipmaps improves visual fidelity, avoids white stippling effect on teapot patch borders
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img->width, img->height, GL_RGB, GL_UNSIGNED_BYTE, img->pointer);

	glEnable(GL_TEXTURE_2D);
}
















/* 
// Sample code to illustrate light components and their influence, c.f Red Book Example 5-1 pp 190 
// Code modified to dgl/SDL framework.

void main()
{
	dglWindowOpen("TPG4162 Gouraud and Phong Lighting Model Shader Example", 640, 640, false);
	
	glShadeModel(GL_SMOOTH);	// default

	// light position in homogeneous coordinates
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat mat_ambient[]	 = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat mat_diffuse[]	 = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_specular[]	 = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);   //25.0);

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// initiate rotation angle
	float rot_angle = 0.0f;

	// main loop
	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )
	{
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear screen and depth buffer before drawing

		glLoadIdentity();
		glRotatef(30, 1.0f, 0.0f, 0.0f);
		glRotatef(rot_angle, 0.0f, 0.0f, 1.0f);

		glColor3ub(255, 255, 0);
		glutSolidSphere(1.0, 20, 16);
		glFlush ();
		glColor3ub(0, 0, 0);
		glutWireSphere(0.9, 20, 20);

		dglSwapBuffers();
		rot_angle += 0.5;
	}
	dglWindowClose();
}
*/
