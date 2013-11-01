#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>       // Open Graphics Library (OpenGL) header
#include <GL/glut.h>     // The GL Utility Toolkit (GLUT) Header

#define KEY_ESCAPE 27
#define KEY_PLUS 43
#define KEY_MINUS 45

#define TRACES 13483     // Number of traces expected in the datafile
#define SAMPLES 1750     // Number of samples per trace expected in the datafile

char seismic[TRACES][SAMPLES];                    // Stores seismic data after reading
static GLubyte textureRGBArray[28][1024*1024*3];  // Stores RGB values for each pixel in each of the 28 textures
GLuint textures[28];                              // Stores identifiers for each of the 28 textures

GLfloat zoomFactor = 1.0;     // Multiplies the field_of_view to zoom in/out
GLfloat panX = 0.0;           // Added to X position of objects to pan along X-axis
GLfloat panY = 0.0;           // Added to Y position of objects to pan along Y-axis

typedef struct {  // Type used to store opengl window settings
  int width;
  int height;
  char* title;
  float field_of_view_angle;
  float z_near;
  float z_far;
} glutWindow;
glutWindow win;



void ReadSEGYTraceSamples (char *fileName)
{
  // Creating a file pointer. Read only, binary type.
  FILE* fileP = fopen(fileName, "rb");

  // Skipping 3600 byte header, from beginning of file
  fseek(fileP, 3600, SEEK_SET);

  for (int i = 0; i < TRACES; i++)
  {
    // Skipping 240 byte trace header, from current file pointer loc.
    fseek(fileP, 240, SEEK_CUR);
    for (int j = 0; j < SAMPLES; j++)
    {
      /*
      * fread(pointer, size, count, stream)
      *   pointer - Pointer to the block to write to
      *   size - Size in bytes of each elements
      *   count - Number of elements to read
      *   stream - Pointer to a file object to use as input stream
      */
      fread(&seismic[i][j], 1, 1, fileP);
    }
  }
  fclose(fileP);
}



void mapColors()
{
  char element;         // Temporarily holds 'active' element
  int textureNr = 0;    // Texture counter
  int pixelCounter;     // Pixel counter (0 to 1024*1024)
  float factor;         // Measure of how far from abs. max/min the element is

  for(int row=0; row<2; row++)
  {
    for(int col=0; col<14; col++)
    {
      pixelCounter = 0; // Set to zero at beginning of each new texture tile
      for(int i=col*1024; i<1024*(col+1); i++)    // Trace counter for the seismic
      {
        for(int j=row*1024; j<1024*(row+1); j++)  // Sample counter for the seismic
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
  glGenTextures(28, textures);
  for (int i = 0; i < 28; i++)
  {
    glBindTexture(GL_TEXTURE_2D, textures[i]);                          // Binding texture to target 2D texture object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // Setting magnification function to linear
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   // Setting minification function to linear. May also be GL_LINEAR_MIPMAP_NEAREST etc.
    /*glTexImage2D(
                  GL_TEXTURE_2D,      // target texture
                  0,                  // level of detail. 0 is base image level; level n is the n'th mipmap reduction
                  3,                  // internal format; i.e. number of color components in texture
                  1024, 1024,         // height, width of texture image
                  0,                  // border (MUST be 0)
                  GL_RGB,             // format of pixel data.
                  GL_UNSIGNED_BYTE,   // data type of the pixel data
                  &textureRGBArray[i] // data source
                );*/
    gluBuild2DMipmaps (
                        GL_TEXTURE_2D,      //GLenum    target,
                        3,                  //GLint   internalFormat,
                        1024, 1024,         //GLsizei   width, height,
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




void zoomIn()
{
  printf("Zooming in.\n");
  if (zoomFactor > 0.1) // Prevent flipping at negative view angle
  {
    zoomFactor -= 0.1;
  }
  glMatrixMode(GL_PROJECTION);                                                  // setting active matrix to projection
  glLoadIdentity();                                                             // reset projection matrix
  GLfloat aspect = (GLfloat) win.width / win.height;
  gluPerspective(win.field_of_view_angle*zoomFactor, aspect, win.z_near, win.z_far);   // set up a perspective projection matrix

  glMatrixMode(GL_MODELVIEW);                                                   // setting active matrix back to modelview
}




void zoomOut()
{
  printf("Zooming out.\n");
  if (zoomFactor < 1.9)
  {
    zoomFactor += 0.1;
  }
  glMatrixMode(GL_PROJECTION);                                                  // setting active matrix to projection
  glLoadIdentity();                                                             // reset projection matrix
  GLfloat aspect = (GLfloat) win.width / win.height;
  gluPerspective(win.field_of_view_angle*zoomFactor, aspect, win.z_near, win.z_far);   // set up a perspective projection matrix

  glMatrixMode(GL_MODELVIEW);                                                   // setting active matrix back to modelview
}



void panUp()
{
  printf("Pan up.\n");
  panY -= 0.1;
}



void panDown()
{
  printf("Pan down.\n");
  panY += 0.1;
}



void panLeft()
{
  printf("Pan left.\n");
  panX += 0.1;
}



void panRight()
{
  printf("Pan right.\n");
  panX -= 0.1;
}




void display()      // Display function regisetered to glut
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
  for (int row = 0; row < 2; row++)
  {
    for (int column = 0; column < 14; column++)
    {
      drawTile(-12.0f+2.0f*column+panX, -2.0f*row+panY, -12.0f, column + row*14);
    }
  }

  glutSwapBuffers();
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
  win.width = 1900;
  win.height = 700;
  win.title = "Project 1";
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
  ReadSEGYTraceSamples("../SEGY/NVGT-88-06.sgy");
  mapColors();

  setWindowValues();
  initializeGlut(argc, argv);
  initializeGl();
  glutMainLoop();   // run GLUT mainloop
  return 0;
}
