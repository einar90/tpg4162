#include "dgl.h"

// Example of building VBOs from one interleaved array of vertex data and one index array.
// Using interleaved array with VBO is not recommended as there are certain limitations, c.f.
// http://www.opengl.org/wiki/Vertex_Buffer_Object and http://www.opengl.org/wiki/Common_Mistakes

void main()	
{
	dglWindowOpen("Drawing using Vertex Buffer Objects (interleaved array of vertex data)", 800, 700, false);							// create a GL-enabled window of given pixel size

	GLuint vbo, indexbuffer;	// IDs for vertex and index buffer objects

	// vertex coordinates and color
	const float vertexdata[] = 
	{ //  X      Y     Z       R     G    B
		-0.8f, -0.8f, 0.5f,	  0.0f, 1.0f, 0.0f,				// vertex #1, lower left  corner [#4]
		 0.8f, -0.8f, 0.5f,	  1.0f, 0.0f, 0.0f,				// vertex #2, lower right corner [#1]
		 0.8f,  0.8f, 0.5f,	  0.0f, 0.0f, 1.0f,				// vertex #3, upper right corner [#2]
		-0.8f,  0.8f, 0.5f,	  1.0f, 0.0f, 0.0f,				// vertex #4, upper left  corner [#3]
	};

	// index array
	const unsigned char indices[] = { 0, 1, 2, 0, 2, 3 };	// when <= 256 vertices, else use unsigned short or unsigned int

	glGenBuffers(1, &vbo);															// generate an ID for a new buffer object
	glBindBuffer(GL_ARRAY_BUFFER, vbo);												// specify that the buffer object will be used for vertex data
	glBufferData(GL_ARRAY_BUFFER, 4*6*sizeof(float), vertexdata, GL_STATIC_DRAW);	// reserve space for storing the vertex data and convey the vertex data

	glGenBuffers(1, &indexbuffer);													// generate an ID for a new buffer object to contain index array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);								// specify that the buffer object will be used for index data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned char), indices, GL_STATIC_DRAW);	// reserve space for storing index data and convey the data

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// begin main loop and keep on till user presses escape
	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )
	{
		glClear(GL_COLOR_BUFFER_BIT);									// clear screen black before drawing

		glVertexPointer(3, GL_FLOAT, 6*sizeof(float), NULL);			// specify that vertex coordinates are 3 coords of type float, interleaved, offset nil from buffer start
		glColorPointer(3, GL_FLOAT, 6*sizeof(float), (float*)NULL + 3);	// RGB colors starts with a pointer offset of 3 floats from buffer start
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);			// draw using indices for triangles which are 6 indices of type unsigned byte, offset nil according to buffer start
		 
		dglSwapBuffers();												// frame is ready to be shown on screen
	}
 
	dglWindowClose();													// close the opened window
}