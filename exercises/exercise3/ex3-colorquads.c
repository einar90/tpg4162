/*
* 3D Visualization of petroleum data
* 	Exercise 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/gl.h>		// Header file for OpenGL32 Library
#include <GL/glu.h>		// Header File For The GLu32 Library



float * getRgbColorArray(int temps[], int length) {
	/*
	* 1 	  0-25 	Blue 	rgb(0.0f, 0.0f, 1.0f)
	* 2	 	 26-50	Green 	rgb(0.0f, 1.0f, 0.0f)
	* 3	 	 51-75 	Yellow 	rgb(1.0f, 1.0f, 0.0f)
	* 4	 	76-100 	Red 	rgb(1.0f, 0.0f, 0.0f)
	*/
	float red[3] 	= {1.0f, 0.0f, 0.0f};
	float yellow[3]	= {1.0f, 1.0f, 0.0f};
	float green[3] 	= {0.0f, 1.0f, 0.0f};
	float blue[3] 	= {0.0f, 0.0f, 1.0f};

	// Setting values to be used for this case of the color mapping algorithm
	int min = 0;
	int max = 100;
	int n = 4;

	// Declaring and allocating the array to be returned
	float *rgbArray = malloc(3*length*sizeof(float));

	// Appending appropriate rgb values to the rgbArray using the color mapping algorithm
	for (int j = 0; j < length; j++)
	{
		int i = n * (temps[j]-min)/(max-min);
		if (i == 0)	{
			memcpy(rgbArray + j*3, blue, 3*sizeof(float));
		} 
		else if (i == 1){
			memcpy(rgbArray + j*3, green, 3*sizeof(float));
		} 
		else if (i == 2){
			memcpy(rgbArray + j*3, yellow, 3*sizeof(float));
		}
		else if (i >= 3){
			memcpy(rgbArray + j*3, red, 3*sizeof(float));
		}
	}

	return rgbArray;
}



void DrawTwoQuadsUsingVertexArrays() {
	// Defining coordinate data
	const float coords[] = {
		-0.8f, -0.8f, 0.0f, 	// Lower left 	[#1]
		 0.0f, -0.8f, 0.0f, 	// Lower middle [#2]	  
		 0.0f,  0.8f, 0.0f, 	// Upper middle [#3]	  
		-0.8f,  0.8f, 0.0f,  	// Upper left 	[#4]
		 0.8f, -0.8f, 0.0f,   	// Lower right 	[#5]
		 0.8f,  0.8f, 0.0f,    	// Upper right 	[#6]
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, coords);

	// Defining temperature data
	int temperatures[] = {10, 50, 100, 50, 10, 50}; 	
	float *rgbArray;
	rgbArray = getRgbColorArray(temperatures, 6);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, rgbArray);

	// Clearing color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Defining indeces
	// Note: Triangles are generated for each of the two quads, with 
	// 	the hypothenuse connecting the first and the third vertices
	const unsigned char indeces[] = { 0, 1, 2, 3, 4, 1, 2, 5 }; // Symmetry 1
	//const unsigned char indeces[] = { 1, 0, 3, 2, 1, 4, 5, 2 }; // Symmetry 2
	
	glColor3f(1.0f, 1.0f, 1.0f);	// set red, green, blue
	glDrawElements(GL_QUADS, 8, GL_UNSIGNED_BYTE, indeces);
}






void DrawGLfigs() {
	DrawTwoQuadsUsingVertexArrays();
}


// Including OpenGL methods
#include"ex3-glfuns.c"

int main(int argc, char *argv[]) {
	initializeWindow();
	displayWindow();
	createContext_enableDepthTest();
	startProgram();
} 