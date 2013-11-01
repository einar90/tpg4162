
#include <iostream>
#include <math.h>
#include <stdio.h>     // Standard C/C++ IO  
#include "GLee.h"
#include <GL/glut.h>   // The GL Utility Toolkit (GLUT) Header

GLuint   program_object;  // a handler to the GLSL program used to update
GLuint   vertex_shader;   // a handler to vertex shader. This is used internally 
GLuint   fragment_shader; // a handler to fragment shader. This is used internally too

// a simple vertex shader source
// this just rotates a quad 45°
static const char *vertex_source = {
"void main(){"
"  float PI = 3.14159265358979323846264;"
"  float angle = 45.0;"
"  float rad_angle = angle*PI/180.0;"
""
"  vec4 a = gl_Vertex;"
"  vec4 b = a;"
""
"  b.x = a.x*cos(rad_angle) - a.y*sin(rad_angle);"
"  b.y = a.y*cos(rad_angle) + a.x*sin(rad_angle);"
"gl_Position = gl_ModelViewProjectionMatrix*b;"
"}"
};

// a simple fragment shader source
// this change the fragment's color by yellow color
static const char *fragment_source = {
"void main(void){"
"   gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);"
"}"
};

/// Print out the information log for a shader object 
/// @arg obj handle for a program object
static void printProgramInfoLog(GLuint obj)
{
	GLint infologLength = 0, charsWritten = 0;
	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
	if (infologLength > 2) {
		GLchar* infoLog = new GLchar [infologLength];
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		std::cerr << infoLog << std::endl;
		delete infoLog;
	}
}

// Our GL Specific Initializations
bool init(void){    
   glClearColor(0.7f, 0.7f, 0.7f, 0.5f);	// Black Background
   
   
   program_object  = glCreateProgram();    // creating a program object
   vertex_shader   = glCreateShader(GL_VERTEX_SHADER);   // creating a vertex shader object
   fragment_shader = glCreateShader(GL_FRAGMENT_SHADER); // creating a fragment shader object
   printProgramInfoLog(program_object);
   
   glShaderSource(vertex_shader, 1, &vertex_source, NULL); // assigning the vertex source
   glShaderSource(fragment_shader, 1, &fragment_source, NULL); // assigning the fragment source
   printProgramInfoLog(program_object);   // verifies if all this is ok so far
   
   // compiling and attaching the vertex shader onto program
   glCompileShader(vertex_shader);
   glAttachShader(program_object, vertex_shader); 
   printProgramInfoLog(program_object);   // verifies if all this is ok so far
   
   // compiling and attaching the fragment shader onto program
   glCompileShader(fragment_shader);
   glAttachShader(program_object, fragment_shader); 
   printProgramInfoLog(program_object);   // verifies if all this is ok so far
   
   // Link the shaders into a complete GLSL program.
   glLinkProgram(program_object);
   printProgramInfoLog(program_object);   // verifies if all this is ok so far
   
   // some extra code for checking if all this initialization is ok
   GLint prog_link_success;
   glGetObjectParameterivARB(program_object, GL_OBJECT_LINK_STATUS_ARB, &prog_link_success);
   if (!prog_link_success) {
      fprintf(stderr, "The shaders could not be linked\n");
      exit(1);
   }
   
	return true;
}

// Our rendering is done here
void render(void)  {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
		
	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	// bind the GLSL program	
	// this means that from here the GLSL program attends all OpenGL operations
	glUseProgram(program_object);
	// painting a quad
	glBegin(GL_QUADS);
	   glVertex3f(-0.5, -0.5, 0.0);
	   glVertex3f(0.5, -0.5, 0.0);
	   glVertex3f(0.5, 0.5, 0.0);
	   glVertex3f(-0.5, 0.5, 0.0);
	glEnd();
	
	// unbind the GLSL program
	// this means that from here the OpenGL fixed functionality is used
	glUseProgram(0);
	
   // Swap The Buffers To Become Our Rendering Visible
   glutSwapBuffers( );
}

// Our Reshaping Handler (Required Even In Fullscreen-Only Modes)
void reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);     // Select The Projection Matrix
	glLoadIdentity();                // Reset The Projection Matrix
	// Calculate The Aspect Ratio And Set The Clipping Volume
	if (h == 0) h = 1;
	gluPerspective(45, (float)w/(float)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);      // Select The Modelview Matrix
	glLoadIdentity();                // Reset The Modelview Matrix
}

// Our keyboard handler
void keyboard(unsigned char key, int x, int y){
	switch (key) {
		case 27:       // When escape is pressed...
			exit(0);    // Exit The Program
		   break;      
		default:       
		break;
	}
}



// Main Function For Bringing It All Together.
int main(int argc, char** argv){	
	glutInit(&argc, argv);                           // GLUT Initializtion
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);     // Display Mode (Rgb And Double Buffered)	
	glutCreateWindow("GLSL Hello World!");          // Window Title 
	
	init();                                          // Our Initialization
	glutDisplayFunc(render);                         // Register The Display Function
	glutReshapeFunc(reshape);                        // Register The Reshape Handler
	glutKeyboardFunc(keyboard);                      // Register The Keyboard Handler	
//	glutIdleFunc(render);                            // Do Rendering In Idle Time
	glutMainLoop();                                  // Go To GLUT Main Loop
	return 0;
}
