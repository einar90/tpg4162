/*
* This code is compiled with 
* 	gcc -o tut1 tut1.c -lX11 -lGL -lGLU
*
* and in fedora linux requires the following packages to be installed:
* 	mesa-libGL-devel 
* 	mesa-libGLU-devel 
* 	mesa-libGLw-devel 
* 	mesa-libOSMesa-devel
*
* The tutorial is found at the following address:
* 	http://www.opengl.org/wiki/Programming_OpenGL_in_Linux:_GLX_and_Xlib
*/


#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>		// Header file for OpenGL32 Library
#include<GL/glu.h>		// Header File For The GLu32 Library

void DrawAQuadTheOldWay() {
	glBegin(GL_QUADS);	
		glColor3f(1.0f, 1.0f, 1.0f);	// set red, green, blue
		glVertex3f(-0.8f, -0.8f, 0.0f);
		glVertex3f(0.8f, -0.8f, 0.0f);
		glVertex3f(0.8f, 0.8f, 0.0f);
		glVertex3f(-0.8f, 0.8f, 0.0f);
	glEnd();
} 




void DrawAQuadUsingVertexArrays() {
	// Defining coordinate data
	const float coords[] = {
		-0.8f, -0.8f, 0.5f, 	// Lower left 	[#1]	  
		 0.8f, -0.8f, 0.5f,   	// Lower right 	[#2]
		 0.8f,  0.8f, 0.5f,    	// Upper right 	[#3]
		-0.8f,  0.8f, 0.5f,  	// Lower left 	[#4]
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, coords);
	
	// Defining color data
	const float colordata[] =  {
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colordata);

	// Clearing color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Defining indeces
	const unsigned char indeces[] = { 0, 1, 2, 0, 2, 3 };
	glColor3f(1.0f, 1.0f, 1.0f);	// set red, green, blue
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indeces);
}





// Including OpenGL methods
#include"glMethods.c"

int main(int argc, char *argv[]) {
	initializeWindow();
	displayWindow();
	createContext_enableDepthTest();
	startProgram();
} 