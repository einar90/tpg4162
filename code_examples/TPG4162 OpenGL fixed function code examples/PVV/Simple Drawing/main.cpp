#include "dgl.h"

void main()
{
	dglWindowOpen("Simple Drawing example (2 tria)", 800, 700, false);	// create a GL-enabled window of given pixel size

	// begin main loop; continue till user presses escape
	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )
	{
		glClear(GL_COLOR_BUFFER_BIT);				// clear screen black before drawing anything

		// vertex coordinates [draw on board, c.f. indices for the 2 TRIA, clip coordinates]
		const float vertexdata[] = 
		{
			-0.8f, -0.8f, 0.5f,	  
			 0.8f, -0.8f, 0.5f,   
			 0.8f,  0.8f, 0.5f,    
			-0.8f,  0.8f, 0.5f,   
		};

		const unsigned char indices[] = { 0, 1, 2, 0, 2, 3 };		// index array for 2 triangles

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertexdata);				// each vertex specified by 3 coords of type float, tightly packed in an array
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices); // tria, 6 indices of type unsigned byte
		
		dglSwapBuffers();		// specifies that the frame is done and can be shown on the screen
	}
	dglWindowClose();			// close opened window
}