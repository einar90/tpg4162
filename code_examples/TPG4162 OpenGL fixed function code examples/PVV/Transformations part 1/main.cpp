#include "dgl.h"

void main()
{
	dglWindowOpen("Transform Example", 800, 700, false);

	// vertices coordinates
	const float vertexdata[] =		
	{
		-0.8f, -0.8f, 0.5f,	 // vertex #1, lower left corner
		 0.8f, -0.8f, 0.5f,  // vertex #2, upper left corner
		 0.8f,  0.8f, 0.5f,  // vertex #3, upper right corner 
		-0.8f,  0.8f, 0.5f,  // vertex #4, lower right corner
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertexdata);

	// set up colors
	const float colordata[] = 
	{
		1.0f, 0.0f, 0.0f,	 // RGB color for vertex #1
		0.0f, 1.0f, 0.0f,    // RGB color for vertex #2
		1.0f, 0.0f, 0.0f,    // RGB color for vertex #3
		0.0f, 0.0f, 1.0f,    // RGB color for vertex #4
	};

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colordata);

	// variables to control object rotation speed regardless of process wait time
	float rotAngle	  = 0.0f;
	unsigned long long prevTime = dglGetCurrentTime();

	// main loop, increment in object rotation is adjusted based on actual time to achieve constant rotation speed
	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )
	{
		glLoadIdentity();              // very important!
		glClear(GL_COLOR_BUFFER_BIT);

		glRotatef(rotAngle, 0, 0, 1);
		glDrawArrays(GL_QUADS, 0, 4);
		dglSwapBuffers();

		rotAngle += 0.03f * (dglGetCurrentTime() - prevTime);				// rotation speed 0.03 degrees per millisecond wall clock time
		prevTime = dglGetCurrentTime();
	}
	dglWindowClose();
}