#include "dgl.h"

void main()
{
	// create a 640x480 GL-enabled window
	dglWindowOpen("Simple Drawing example", 640, 480, false);

	GLuint vbo, indexbuffer;	// IDs for vertex and index buffer objects

	// set up some vertices
	const float vertexdata[] = 
	{
		-0.8f, -0.8f, 0.5f,		// lower left corner
		 0.8f, -0.8f, 0.5f,		// lower right corner
		 0.8f,  0.8f, 0.5f,		// upper right corner 
		-0.8f,  0.8f, 0.5f,		// upper left corner
	};

	// index array
	const unsigned char indices[] = { 0, 1, 2, 0, 2, 3 };

	glGenBuffers(1, &vbo);															// generate an ID for a new buffer object
	glBindBuffer(GL_ARRAY_BUFFER, vbo);												// specify that the buffer object will be used for storing array data for rendering
	glBufferData(GL_ARRAY_BUFFER, 4*3*sizeof(float), vertexdata, GL_STATIC_DRAW);	// reserve space for storing the vertex data

	glGenBuffers(1, &indexbuffer);																// generate an ID for a new buffer object to contain index array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);											// specify that the buffer object will be used for storing array data for rendering
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned char), indices, GL_STATIC_DRAW);	// reserve space for storing index data

	// begin main loop and keep on till user presses escape
	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )
	{
		glClear(GL_COLOR_BUFFER_BIT);							// before drawing anything, clear screen black. 

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);						// CONVEY VERTICES: 3 coords of type float, tightly packed, offset nil according to buffer start
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);	// CONVEY INDICES: tria, 6 indices of type unsigned byte, offset nil according to buffer start
		
		// tells your OS that the frame is done and can be shown on the screen. 
		dglSwapBuffers();
	}

	// close the opened window. The OS will usually close it, but it's always nice to be tidy. 
	dglWindowClose();
}