#include "dgl.h"
#include <stdio.h>


void main()			// vertex array method by tightly packed arrays
{
	dglWindowOpen("Color Example [quad in tight array]: Color interpolation intuitive?", 800, 700, false);

	// vertex coordinates, quad vertices in counter-clockwise sequence
	const float vertexdata[] = 
	{
		 0.8f,  0.8f, 0.5f,   // vertex #2, upper right corner [#1]
		-0.8f,  0.8f, 0.5f,   // vertex #3, upper left  corner [#2]
		-0.8f, -0.8f, 0.5f,   // vertex #4, lower left  corner [#3]
		 0.8f, -0.8f, 0.5f,   // vertex #1, lower right corner [#4]
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertexdata);    // 3 coords of type float, tightly packed vertex array

	// Define colors for each vertex of the quad. A more probable color interpolation case in brackets [AMD]. AMD and NVIDEA may differ wrt tria tesselation of a quad.
	const float colordata[] = 
	{
		0.0f, 0.0f, 1.0f,		// RGB color for vertex #3 [#1]
		1.0f, 0.0f, 0.0f,		// RGB color for vertex #4 [#2]
		0.0f, 1.0f, 0.0f,	    // RGB color for vertex #1 [#3]
		1.0f, 0.0f, 0.0f,		// RGB color for vertex #2 [#4]
	};

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colordata);	// color given by 3 floats (RGB), tightly packed array

	// main loop
	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_QUADS, 0, 4);
		dglSwapBuffers();
	}
	dglWindowClose();
}