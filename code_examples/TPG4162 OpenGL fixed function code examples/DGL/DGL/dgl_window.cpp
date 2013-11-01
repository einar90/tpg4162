#include <stdlib.h>
#include "dgl_private.h"


void dglWindowOpen(char* title, int width, int height, bool fullscreen) {
	
	// initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		dglCriticalError("Window creation failed: %s\n", SDL_GetError() );
	}

	// If fullscreen is set, request a fullscreen window
	GLuint flags = SDL_OPENGL;
	if(fullscreen) flags |= SDL_FULLSCREEN;

	// request a RGBA8888, 24bit depth, 8bit stencil, doublebuffered default framebuffer 
	SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
 
	// create window with requested features. 
	if( SDL_SetVideoMode(width, height, 0, flags) == NULL)
	{
		dglCriticalError("Window creation failed: %s\n", SDL_GetError() );
	}

	// set window title. 
	SDL_WM_SetCaption(title, NULL);
	
	// key input settings. 
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	SDL_EnableUNICODE(1);
   
#ifdef WIN32
	// windows programs need glew for any entrypoints made after 1998 
	GLenum glewerr = glewInit();
	if(glewerr != GLEW_OK) 
	{
		dglCriticalError("%s\n", glewGetErrorString(glewerr));
	}
#endif

}


void dglWindowClose() {
 
	SDL_Quit();
}


void dglSwapBuffers() {
	SDL_Event event;
	while( SDL_PollEvent(&event) ) 
	{
		switch(event.type) 
		{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEMOTION:
				dglHandleInputEvents(&event);
		}
	}
	SDL_GL_SwapBuffers();

	
#ifndef NDEBUG
	// this snippet here is useful to catch GL errors in development
	int i;
	if((i = glGetError())) 
	{
		printf("dglSwapBuffer reported an OpenGL Error: %i\n", i);
    }
#endif


}


