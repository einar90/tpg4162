#include "dgl.h"

void main()
{
	dglWindowOpen("Drawing using Vertex Buffer Objects (tightly packed coordinates and indices)", 800, 700, false);	// create a GL-enabled window of given pixel size

	GLuint vbo, indexbuffer;	// IDs for vertex and index buffer objects

	const float vertexdata[] =	// tightly packed array of coordinates for 4 vertices
	{
		-0.8f, -0.8f, 0.5f,		// lower left corner
		 0.8f, -0.8f, 0.5f,		// lower right corner
		 0.8f,  0.8f, 0.5f,		// upper right corner 
		-0.8f,  0.8f, 0.5f,		// upper left corner
	};

	const unsigned char indices[] = { 0, 1, 2, 0, 2, 3 };		// max 256 vertices, else use unsigned short or unsigned int

	glGenBuffers(1, &vbo);															// generate an ID for a new buffer object
	glBindBuffer(GL_ARRAY_BUFFER, vbo);												// specify that the buffer object will be used for vertex data
	glBufferData(GL_ARRAY_BUFFER, 4*3*sizeof(float), vertexdata, GL_STATIC_DRAW);	// reserve space for storing the vertex data and convey the vertex data

	glGenBuffers(1, &indexbuffer);																// generate an ID for a new buffer object to contain index array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);											// specify that the buffer object will be used for index data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned char), indices, GL_STATIC_DRAW);	// reserve space for storing index data and convey the data

	// begin main loop and keep on till user presses escape
	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )
	{
		glClear(GL_COLOR_BUFFER_BIT);							// clear screen black before drawing

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);						// specify that vertex coordinates are 3 coords of type float, tightly packed, offset nil according to buffer start
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);	// draw using indices for triangles which are 6 indices of type unsigned byte, offset nil according to buffer start
		 
		dglSwapBuffers();										// frame is ready to be shown on screen
	}
 
	dglWindowClose();											// close the opened window
}