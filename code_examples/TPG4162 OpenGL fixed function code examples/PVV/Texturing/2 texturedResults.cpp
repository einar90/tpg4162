#include "dgl.h"
#include <stdlib.h>
#include <math.h>
#include <glut.h>

// TPG4162 SAMPLE CODE INSPIRED BY EXERCISE 3 TO ILLUSTRATE THE USE OF TEXTURE FOR COLOR MAPPING OF A RESULT DISTRIBUTION

void setupColorMapTexture();

/***************************************************************************************************************
 * Macro for linear conversion from temperature t ∈ [0, 100] to texture coordinat s ∈ [0.0, 1.0].
 * According color map formula = n * (Si - min) / (max - min) = 1.0 (Si - 0) / (100 - 0) = Si / 100. 
 * Check the 4 legend levels which means t = {10, 50, 100} ⇔ s = {0.1, 0.5, 1.0}
 ***************************************************************************************************************/
#define TEMP_TO_TEXCOORD(Si) (Si/100.0)


void main()
{
	dglWindowOpen("Textured Color Mapping of Results", 900, 750, false);    // create a GL-enabled window of given pixel size

	setupColorMapTexture();		// set up the one-dimensional texture for the color legend of the result distribution

	glEnableClientState(GL_VERTEX_ARRAY);

	static float vertexData[] = 
	{ //  X      Y     Z     TEMP converted to texcoord
		-0.8f, -0.8f, 0.0f, TEMP_TO_TEXCOORD(10),
		 0.0f, -0.8f, 0.0f, TEMP_TO_TEXCOORD(50),
		 0.0f,  0.8f, 0.0f, TEMP_TO_TEXCOORD(100),
		-0.8f,  0.8f, 0.0f, TEMP_TO_TEXCOORD(50),
		 0.8f, -0.8f, 0.0f, TEMP_TO_TEXCOORD(10),
		 0.8f,  0.8f, 0.0f, TEMP_TO_TEXCOORD(50),
	};

	GLsizei stride = 4 * sizeof(float);
	glVertexPointer  (3, GL_FLOAT, stride, vertexData);
	glTexCoordPointer(1, GL_FLOAT, stride, &vertexData[3]);

	static unsigned int indices[] = 
	{
		0, 1, 2, 3,
		1, 4, 5, 2,
	};


	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )		// begin the main loop. Keep on running until user presses escape
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear screen black before drawing

		glDrawElements(GL_QUADS, 4 * 2, GL_UNSIGNED_INT, indices);

		dglSwapBuffers();	// frame is done and can be shown on the screen
		
	}

	dglWindowClose();
}





/***************************************************************************************************************
 * Set up the one-dimensional texture for the color legend of the result distribution spanning four levels by
 * the colors blue, green, yellow, and red. Red signals the highest temperatures, c.f. ranges denoted below.
 * The color legend ranges from low value to high value, i.e. texture coordinate 1.0 represents temperature 100
 ***************************************************************************************************************/
void setupColorMapTexture()
{
	static unsigned char colorMap[] = 
	{  
		  0,    0,   255,		// blue,   i.e. temp [ 0, 25>
		  0,  255,     0,		// green,  i.e. temp [25, 50>
		255,  255,     0,		// yellow, i.e. temp [50, 75>
		255,    0,     0		// red,    i.e. temp [75, 100]
	};
	
	GLuint colorMapTextureID;								
	glGenTextures(1, &colorMapTextureID);
	glBindTexture(GL_TEXTURE_1D, colorMapTextureID);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 4,  0, GL_RGB, GL_UNSIGNED_BYTE, colorMap);

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);

	glEnable(GL_TEXTURE_1D);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}
