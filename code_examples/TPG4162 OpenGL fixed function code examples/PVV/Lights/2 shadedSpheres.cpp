#include "dgl.h"
#include <stdlib.h>
#include <math.h>
#include <glut.h>
#include <stdio.h>


void main()
{
	dglWindowOpen("TPG4162: Sphere illumination example", 1000, 600, false);    // create 1000 x 600 pixels GL enabled window

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	// parameter setup for light 0
	float light0_position[] = { 10.0f, 10.0f, 3.0f, 0.0f  }; // last component zero => directional light
	float light0_ambient[]  = {  0.1f, 0.1f,  0.1f, 1.0f  }; // dull grey ambient
	float light0_diffuse[]  = {  0.9f, 0.9f, 0.9f,  1.0f  }; // bright diffuse light
	float light0_specular[] = {  1.0f, 1.0f, 1.0f,  1.0f  }; // white and shiny specular light

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	// material reflection parameters
	GLfloat mat_ambient[]	 = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat mat_diffuse[]	 = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_specular[]	 = { 1.0, 1.0, 1.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  
	// begin main loop and continue until user presses escape
	while( !dglGetAsyncKeyState(DGLK_ESCAPE) )
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-5.0, 5.0, -1.5, 4.5, 0, 20);			// orthographic view avoids perspective distortion (unequal spheres); aspect ratio 10 to 6 
//		glFrustum(-5.0, 5.0, -1.5, 4.5, 8, 20);			// perspective view specifying left/right/bot/top at front clip plane z=8 from eye point in view direction 
		glClearColor(1.0, 1.0, 1.0, 0.0);				// clear screen white
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(3, 1.5, 10, 3, 0, 0, 0, 1, 0);		// eye point, view ref point, up-vector

		for (int i = 0; i < 3; ++i)						// three rows of spheres
		{
			for (int j = 0; j < 5; ++j)					// five columns of spheres
			{
				GLfloat shininess = (j + 1) * 20.0f;	// shininess varies equally along each row

				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess);			// assign shininess for each sphere of current row
				glLightfv(GL_LIGHT0, GL_POSITION, light0_position);		// not necessary here but safe as light positions are transformed, too
				glutSolidSphere(0.7, 50, 50);
				glTranslatef(1.6f, 0.0f, 0.0f);							// translate horizontally allowing for some space between spheres
			}

			glTranslatef(-5 * 1.6f, 1.6f, 0.0f);		// return to position of first sphere horizontally and up a row 
		}

		dglSwapBuffers();								// show scene on screen 
	}

	dglWindowClose();
}








/*********************************************************************************************************************************
// VARIATION OF ks and alpha

		for (int i = 0; i < 3; ++i)						// three rows of spheres
		{
			for (int j = 0; j < 5; ++j)					// five columns of spheres
			{
				GLfloat shininess = (j + 1) * 20.0f;	// shininess varies equally along each row

				GLfloat hack_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
				if (j>0) for (int k=0; k<3; k++) hack_specular[k] = mat_specular[k]/((float)j); 
				hack_specular[3] = 1.0f;

				glMaterialfv(GL_FRONT, GL_SPECULAR, hack_specular);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess);			// assign shininess for each sphere of current row
				glLightfv(GL_LIGHT0, GL_POSITION, light0_position);		// not necessary here but safe as light positions are transformed, too
				glutSolidSphere(0.7, 50, 50);
				glTranslatef(1.6f, 0.0f, 0.0f);
			}

			glTranslatef(-5 * 1.6f, 1.6f, 0.0f);		// return to position of first sphere 
		}
*********************************************************************************************************************************/
