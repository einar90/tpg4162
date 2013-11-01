#include "dgl.h"
#include <math.h>

void main()
{
	dglWindowOpen("Viewpoint animation", 640, 480, false);

	// set up vertices
	const float vertexdata[] = 
	{
		-8.0f, 0.0f, 10.0f, 
		 8.0f, 0.0f, 10.0f,  
		 8.0f, 0.0f,  0.0f,   
		-8.0f, 0.0f,  0.0f,  
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertexdata);

	// set up colors
	const float colordata[] = 
	{
		1.0f, 0.0f, 0.0f,	  // RGB color for vertex #1
		0.0f, 1.0f, 0.0f,     // RGB color for vertex #2
		1.0f, 0.0f, 0.0f,     // RGB color for vertex #3
		0.0f, 0.0f, 1.0f,     // RGB color for vertex #4
	};
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colordata);

	// some angle 
	float t = 0;

	// main loop
	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, 640.0f/480.0f, 1.0f, 500.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();          
		gluLookAt(-t,2,sin(t/3.0)/0.2,		// eye
//		gluLookAt( 0, 30*sin(t/3.0), 0,				
		           0, 0,  10,	//vrp		
				   0, 1,  0 );  //up

		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_QUADS, 0, 4);
		dglSwapBuffers();

		t += 0.03f;
	}
	dglWindowClose();
}