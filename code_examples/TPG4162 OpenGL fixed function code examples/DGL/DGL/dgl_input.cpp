#include "dgl.h"
#include <SDL.h>


void dglHandleInputEvents(SDL_Event *event)
{
	// NYI
  
}

bool dglGetAsyncKeyState(unsigned int dglkey){
	unsigned char * keys = SDL_GetKeyState(NULL);
	return keys[dglkey] != 0;
}

