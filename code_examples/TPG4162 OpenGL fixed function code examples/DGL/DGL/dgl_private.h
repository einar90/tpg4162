#include "dgl.h"
#include <SDL.h>

// this is a Private header. Here, all internal-library calls that users never have to call are defined. 


// function which handles all critical errors.  
void dglCriticalError(char* msg, ...);

// prototypes for keyboard handling. 
void dglHandleInputEvents(SDL_Event *e);
