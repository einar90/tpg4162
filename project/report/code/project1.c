// Standard libs
#include <stdio.h>
#include <stdlib.h>

// OpenGL libs
#include <GL/gl.h>       // Open Graphics Library (OpenGL) header
#include <GL/glut.h>     // The GL Utility Toolkit (GLUT) Header

// Home cooked libs
#include "SEGYReader.h"  // Header file containing the subprocedure used to read SEGY-files

// Key-code definitions
#define KEY_ESCAPE 27
#define KEY_PLUS 43
#define KEY_MINUS 45

// File related definitions
#define TRACES 13483    // Number of traces expected in the datafile
#define SAMPLES 1750    // Number of samples per trace expected in the datafile

// Texture related definitions
#define TEX_TOT 28      // Number of textures to generate in total
#define TEX_ROWS 2      // Number of rows the textures are placed in
#define TEX_COLS 14     // Number of columns the textures are placed in
#define TEX_WIDTH 1024  // Width of each generated texture
#define TEX_HEIGHT 1024 // Heigh of each generated texture

// Array declarations
char seismic[TRACES][SAMPLES];                                    // Stores seismic data after reading
static GLubyte textureRGBArray[TEX_TOT][TEX_WIDTH*TEX_HEIGHT*3];  // Stores RGB values for each pixel in each of the 28 textures
GLuint textures[TEX_TOT];                                         // Stores identifiers for each of the 28 textures

// Runtime variable declarations
GLfloat zoomFactor = 1.0;     // Multiplies the field_of_view to zoom in/out
GLfloat panX = 0.0;           // Added to X position of objects to pan along X-axis
GLfloat panY = 0.0;           // Added to Y position of objects to pan along Y-axis

// GLUT window data struct
typedef struct
{
  int width;
  int height;
  char* title;
  float field_of_view_angle;
  float z_near;
  float z_far;
} glutWindow; // Type used to store opengl window settings
glutWindow win;



void mapColors()
{
  char element;         // Temporarily holds 'active' element
  int textureNr = 0;    // Texture counter
  int pixelCounter;     // Pixel counter (0 to TEX_WIDTH*TEX_HEIGH)
  float factor;         // Measure of how far from abs. max/min the element is

  for(int row=0; row<TEX_ROWS; row++)
  {
    for(int col=0; col<TEX_COLS; col++)
    {
      pixelCounter = 0; // Set to zero at beginning of each new texture tile
      for(int i=col*TEX_WIDTH; i<TEX_WIDTH*(col+1); i++)    // Trace counter for the seismic
      {
        for(int j=row*TEX_HEIGHT; j<TEX_HEIGHT*(row+1); j++)  // Sample counter for the seismic
        {
          if( (i>(TRACES-1)) || (j>(SAMPLES-1)) )   // Setting to black if outside data range
          {
            textureRGBArray[textureNr][3*pixelCounter]   = 0;
            textureRGBArray[textureNr][3*pixelCounter+1] = 0;
            textureRGBArray[textureNr][3*pixelCounter+2] = 0;
          }
          else
          {
            element = seismic[i][j];
            factor = (float) abs(element)/128.0;
            if( element > 0)          // Setting positive elements to blue
            {
              textureRGBArray[textureNr][3*pixelCounter]   = 255 - 255*factor;
              textureRGBArray[textureNr][3*pixelCounter+1] = 255 - 255*factor;
              textureRGBArray[textureNr][3*pixelCounter+2] = 255;
            }

            else if( element < 0 )    // Setting negative elements to red
            {
              textureRGBArray[textureNr][3*pixelCounter]   = 255;
              textureRGBArray[textureNr][3*pixelCounter+1] = 255 - 255*factor;
              textureRGBArray[textureNr][3*pixelCounter+2] = 255 - 255*factor;
            }

            else if( element == 0 )   // Setting elements equal to zero to white
            {
              textureRGBArray[textureNr][3*pixelCounter] = 255;
              textureRGBArray[textureNr][3*pixelCounter+1] = 255;
              textureRGBArray[textureNr][3*pixelCounter+2] = 255;
            }
          }
          pixelCounter++; // Pixel color has been set; incrementing to next pixel
        }
      }
    textureNr +=1;  // All pixels have been set for texture; incrementing to next
    }
  }
}



void createTextures()
{
  glGenTextures(TEX_TOT, textures);
  for (int i = 0; i < TEX_TOT; i++)
  {
    glBindTexture(GL_TEXTURE_2D, textures[i]);                          // Binding texture to target 2D texture object

    // Linear filtering
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Nearest filtering
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Nearest filtering with mipmaps
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);


    // Linear filtering with mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

    // Trilinear filtering with mipmaps
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);


    // Without mipmaps
    /*glTexImage2D(
                  GL_TEXTURE_2D,      // target texture
                  0,                  // level of detail. 0 is base image level; level n is the n'th mipmap reduction
                  3,                  // internal format; i.e. number of color components in texture
                  TEX_WIDTH, TEX_HEIGHT,         // height, width of texture image
                  0,                  // border (MUST be 0)
                  GL_RGB,             // format of pixel data.
                  GL_UNSIGNED_BYTE,   // data type of the pixel data
                  &textureRGBArray[i] // data source
                );*/

    // With mipmaps
    gluBuild2DMipmaps (
                        GL_TEXTURE_2D,      //GLenum    target,
                        3,                  //GLint   internalFormat,
                        TEX_WIDTH, TEX_HEIGHT,         //GLsizei   width, height,
                        GL_RGB,             //GLenum    format,
                        GL_UNSIGNED_BYTE,   //GLenum    type,
                        &textureRGBArray[i] //const void *    data
                      );
  }
}



void drawTile(float transX, float transY, float transZ, int tile)
{
  // Defining coordinate data
  const float vertexCoords[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f
  };
  const float textureCoords[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f
  };

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertexCoords);
  glTexCoordPointer(2, GL_FLOAT, 0, textureCoords);

  glLoadIdentity();
  glTranslatef(transX,transY,transZ);
  glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);          // Rotating 90 degrees clockwise

  glBindTexture(GL_TEXTURE_2D, textures[tile]); // Binding texture to draw
  glDrawArrays(GL_QUADS, 0, 4);                 // Drawing quad with texture applied
}



void display()      // Display function regisetered to glut
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
  for (int row = 0; row < TEX_ROWS; row++)
  {
    for (int column = 0; column < TEX_COLS; column++)
    {
      drawTile(-12.0f+2.0f*column+panX, -2.0f*row+panY, -12.0f, column + row*TEX_COLS);
    }
  }

  glutSwapBuffers();
}




void zoomIn()
{
  if (zoomFactor > 0.1) // Prevent flipping at negative view angle
  {
    zoomFactor -= 0.1;
  }
  printf("Zoom: %f.\n", zoomFactor);
  glMatrixMode(GL_PROJECTION);                                                  // setting active matrix to projection
  glLoadIdentity();                                                             // reset projection matrix
  GLfloat aspect = (GLfloat) win.width / win.height;
  gluPerspective(win.field_of_view_angle*zoomFactor, aspect, win.z_near, win.z_far);   // set up a perspective projection matrix

  glMatrixMode(GL_MODELVIEW);                                                   // setting active matrix back to modelview
}




void zoomOut()
{
  if (zoomFactor < 1.9)
  {
    zoomFactor += 0.1;
  }
  printf("Zoom: %f.\n", zoomFactor);
  glMatrixMode(GL_PROJECTION);                                                  // setting active matrix to projection
  glLoadIdentity();                                                             // reset projection matrix
  GLfloat aspect = (GLfloat) win.width / win.height;
  gluPerspective(win.field_of_view_angle*zoomFactor, aspect, win.z_near, win.z_far);   // set up a perspective projection matrix

  glMatrixMode(GL_MODELVIEW);                                                   // setting active matrix back to modelview
}



void panUp()
{
  panY -= 0.1;
  printf("Pan Y: %f\n", panY);
}



void panDown()
{
  panY += 0.1;
  printf("Pan Y: %f\n", panY);
}



void panLeft()
{
  panX += 0.1;
  printf("Pan X: %f\n", panX);
}



void panRight()
{
  panX -= 0.1;
  printf("Pan X: %f\n", panX);
}




void keyboard ( unsigned char key, int mousePositionX, int mousePositionY )
{
  switch ( key )
  {
    case KEY_ESCAPE:
      exit ( 0 );
      break;

    case KEY_PLUS:
      zoomIn();
      break;

    case KEY_MINUS:
      zoomOut();
      break;

    default:
      break;
  }
}



void specialInput( int key, int x, int y)
{
  switch ( key )
  {
    case GLUT_KEY_UP:
      panUp();
      break;

    case GLUT_KEY_DOWN:
      panDown();
      break;

    case GLUT_KEY_LEFT:
      panLeft();
      break;

    case GLUT_KEY_RIGHT:
      panRight();
      break;

    default:
      break;

  }
}


void setWindowValues()
{
  win.width = 1600;
  win.height = 1000;
  win.title = "With mipmap. Trilinear filtering.";
  win.field_of_view_angle = 45;
  win.z_near = 1.0f;
  win.z_far = 500.0f;
}



void initializeGlut(int argc, char **argv)
{
  glutInit(&argc, argv);                                                        // GLUT initialization
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );                    // Display Mode
  glutInitWindowSize(win.width,win.height);                                     // set window size
  glutCreateWindow(win.title);                                                  // create Window
  glutDisplayFunc(display);                                                     // register Display Function
  glutIdleFunc( display );                                                      // register Idle Function
  glutKeyboardFunc( keyboard );                                                 // register Keyboard Handler
  glutSpecialFunc( specialInput );                                                  // In this program, this handles arrow keys
}



void initializeGl ()
{
    glMatrixMode(GL_PROJECTION);                                                // select projection matrix
    glViewport(0, 0, win.width, win.height);                                    // set the viewport

    glMatrixMode(GL_PROJECTION);                                                // set matrix mode
    glLoadIdentity();                                                           // reset projection matrix
    GLfloat aspect = (GLfloat) win.width / win.height;
    gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);     // set up a perspective projection matrix



    glMatrixMode(GL_MODELVIEW);                                                 // specify which matrix is the current matrix
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );                                                       // specify the clear value for the depth buffer
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );                        // specify implementation-specific hints

    glClearColor(0.0, 0.0, 0.0, 0.0);                                           // specify clear values for the color buffers
    glEnable(GL_TEXTURE_2D);                                                    // Enable Texture Mapping

    createTextures();
}



int main(int argc, char **argv)
{
  ReadSEGYTraceSamples("../SEGY/NVGT-88-06.sgy", &seismic[0][0], TRACES, SAMPLES);
  mapColors();

  setWindowValues();
  initializeGlut(argc, argv);
  initializeGl();
  glutMainLoop();   // run GLUT mainloop
  return 0;
}
