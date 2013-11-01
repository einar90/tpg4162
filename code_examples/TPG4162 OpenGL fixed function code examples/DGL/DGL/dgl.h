#ifndef DGL_HEADER
#define DGL_HEADER

#ifdef WIN32
#include <windows.h>
#include <GL/glew.h>
#endif

#ifdef __APPLE__
#include <openGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "dgl_input.h"
#include "dgl_perspective.h"
#include "dgl_image.h"

// used for handling the window context. There can only be 
// one window operational at the time. This is an 
// implementation shortcut. 
void dglWindowOpen(char* title, int xsize, int ysize, bool fullscreen);
void dglWindowClose(void);

// call this one at the end of each frame. It swaps buffers, 
// handles all dgl messages and does a lot of background work. 
void dglSwapBuffers(void);

//returns true or false depending on whether key is pressed at the time of calling. 
//note that when framerates are getting slow, keypresses might be missed through this call. 
bool dglGetAsyncKeyState(unsigned int dglkey);


// returns the time since program start, in milliseconds.
unsigned long long dglGetCurrentTime(); 

#endif


