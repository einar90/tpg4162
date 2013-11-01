#include "dgl.h"
#include <stdio.h>

void main()										// *** VARIANTS: look below ***
{
	dglWindowOpen("TPG4162: Textured Example", 800, 700, false);

	// set up the vertices
	const float vertexdata[] = 
	{
		-0.8f, -0.8f, 0.5f,	 // vertex #1, lower left corner
		 0.8f, -0.8f, 0.5f,  // vertex #2, upper left corner
		 0.8f,  0.8f, 0.5f,  // vertex #3, upper right corner 
		-0.8f,  0.8f, 0.5f,  // vertex #4, lower right corner
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertexdata);

	// set up texture coordinates for each vertex 
	const float texcoorddata[] = 
	{
		0.0f, 1.0f,         // texture coordinates for vertex #2
		1.0f, 1.0f,         // texture coordinates for vertex #2
		1.0f, 0.0f,         // texture coordinates for vertex #3
		0.0f, 0.0f,         // texture coordinates for vertex #2
	};
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoorddata);

	// load texture object from file
	struct DGLImage* img = dglCreateImage("lenna.png");

	// initialize and bind the texture object
	GLuint texobj;
	glGenTextures(1, &texobj);
	glBindTexture(GL_TEXTURE_2D, texobj);
	glTexImage2D(GL_TEXTURE_2D, 0, img->format, img->width, img->height, 0, img->format, GL_UNSIGNED_BYTE, img->pointer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glEnable(GL_TEXTURE_2D); // enable texturing on all subsequent draws

	// main loop
	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_QUADS, 0, 4);  
		dglSwapBuffers();
	}
	dglWindowClose();
}

/*  VARIANTS:
	*** change to texcoord 2.0f instead of 1.0f
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//GL_CLAMP);

	*** rotate polygon to see better:
	    glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT);
		glTranslatef(-0.25, 0.2, 0);
		glRotatef(-25, 0, 0, 1);
		glRotatef(60, 0, 1, 0);

	*** may also try Code Sample 6 Lights: with dglLoadTexture("lenna.png"); 
	*** to see how texture is applied and that the brick texture imposes less visible effects.
*/