#include "dgl.h"
#include <stdlib.h>
#include <math.h>
#include <glut.h>



void main()		// Ambient light only. No shading, 
{
	dglWindowOpen("Light example", 800, 800, false);    // create a GL-enabled window of given pixel size

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	// homogenous coordinates for light position. Transformed by the current modelview matrix, just as for vertices.
	float position[] = { 0.0f, 0.0f, 10.0f, 0.0f };

	float ambient[] =  { 0.8f, 0.0f, 0.0f, 1.0f };	// not too bright
	float diffuse[] =  { 0.0f, 0.0f, 0.0f, 1.0f };	// no diffuse light
	float specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };	// no specular light

	// set up light 0. 
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// set up ambient part of material, rest is cancelled by black light anyway
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// begin the main loop. Keep on running until user presses escape
	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear before drawing
		
		glutSolidSphere(0.8f, 100, 100);
		
		dglSwapBuffers();										// frame is done and can be shown on the screen
	}
	dglWindowClose();											// close the opened window
}