#include "dgl.h"

void main()
{
	// create a 640x480 GL-enabled window
	dglWindowOpen("Simple Drawing example", 640, 480, false);

	// begin the main loop. Keep it running until someone presses escape
	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )
	{
		// clear screen black. Should be done before we draw anything
		glClear(GL_COLOR_BUFFER_BIT);

		// set up some vertices
		const float vertexdata[] = 
		{
		-0.8f, -0.8f, 0.5f,	// lower left corner
		0.8f, -0.8f, 0.5f,  // upper left corner
		0.8f, 0.8f, 0.5f,   // upper right corner 
		-0.8f, 0.8f, 0.5f,  // lower right corner
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertexdata);
		glDrawArrays(GL_QUADS, 0, 4);
		
		// tells your OS that the frame is done and can be shown on the screen. 
		dglSwapBuffers();
	}

	// close the opened window. The OS will usually close it, but it's always nice to be tidy. 
	dglWindowClose();

}