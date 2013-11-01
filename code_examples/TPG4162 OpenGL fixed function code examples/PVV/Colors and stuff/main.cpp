#include "dgl.h"
#include <stdio.h>


void main()
{
	dglWindowOpen("Color Example: Color interpolation intuitive?", 640, 480, false);

	// vertice coordinates, quad vertices in counter-clockwise sequence
	const float vertexdata[] = 
	{
		 0.8f, -0.8f, 0.5f,   // vertex #2, lower right corner [#1]
		 0.8f,  0.8f, 0.5f,   // vertex #3, upper right corner [#2]
		-0.8f,  0.8f, 0.5f,   // vertex #4, upper left  corner [#3]
		-0.8f, -0.8f, 0.5f,   // vertex #1, lower left  corner [#4]
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertexdata);    // 3 coords of type float, tightly packed vertex array

	// Define colors for each quad vertex. Correct color interpolation case in brackets
	const float colordata[] = 
	{
		1.0f, 0.0f, 0.0f,		// RGB color for vertex #2 [#1]
		0.0f, 0.0f, 1.0f,		// RGB color for vertex #3 [#2]
		1.0f, 0.0f, 0.0f,		// RGB color for vertex #4 [#3]
		0.0f, 1.0f, 0.0f,	    // RGB color for vertex #1 [#4]
	};

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colordata);	// color given by 3 floats (rgb) by a tightly packed array

	// main loop
	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_QUADS, 0, 4);
		dglSwapBuffers();
	}
	dglWindowClose();
}