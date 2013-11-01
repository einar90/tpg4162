#include "dgl.h"
#include <stdio.h>

void main()    // interleaved array of vertex data consisting of coordinates and RGB color, separate arrays below
{
	dglWindowOpen("Color Example [quad in interleaved array]: Color interpolation intuitive?", 800, 700, false);

	// vertex coordinates and color, quad vertices in counter-clockwise sequence
	const float vertexdata[] = 
	{ //  X      Y     Z       R     G    B
		 0.8f, -0.8f, 0.5f,	  1.0f, 0.0f, 0.0f,				// vertex #1, lower right corner [#2]
		 0.8f,  0.8f, 0.5f,	  0.0f, 0.0f, 1.0f,				// vertex #2, upper right corner [#3]
		-0.8f,  0.8f, 0.5f,	  1.0f, 0.0f, 0.0f,				// vertex #3, upper left  corner [#4]
		-0.8f, -0.8f, 0.5f,	  0.0f, 1.0f, 0.0f,				// vertex #4, lower left  corner [#1]
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 6*sizeof(float), vertexdata);		// 3 coords of type float, interleaved array

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 6*sizeof(float), vertexdata+3);		// RGB color given by 3 floats, interleaved array

	// main loop
	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_QUADS, 0, 4);
		dglSwapBuffers();
	}
	dglWindowClose();
}