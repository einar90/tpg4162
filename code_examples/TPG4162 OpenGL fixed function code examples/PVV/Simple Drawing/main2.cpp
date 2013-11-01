#include "dgl.h"

void main()
{
	// create a GL-enabled window
	dglWindowOpen("Simple Drawing: glDrawArrays quad example", 800, 700, false);

	// set up some vertices
	const float vertexdata[] = 
	{
		-0.8f,	-0.8f,  0.5f,		// lower left corner
		 0.8f,  -0.8f,  0.5f,		// upper left corner
		 0.8f,   0.8f,  0.5f,		// upper right corner 
		-0.8f,   0.8f,  0.5f,		// lower right corner
	};

	// begin main loop and continue till user presses escape
	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )
	{
		// clear screen black before drawing
		glClear(GL_COLOR_BUFFER_BIT);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertexdata);	// 3 coords of type float, tightly packed
		glDrawArrays(GL_QUADS, 0, 4);					// draw a quad based on the array of vertices
		
		dglSwapBuffers();								// frame is done and can be shown on the screen
	}

	// close the opened window 
	dglWindowClose();
}