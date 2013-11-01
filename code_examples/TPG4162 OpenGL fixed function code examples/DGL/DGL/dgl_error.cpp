#include "dgl_private.h"

// function which handles all critical errors.  
void dglCriticalError(char* msg, ...) 
{

#ifdef WIN32
	// windows would probably want the error as a popupbox
#if 0
	char buffer[4096];
	va_list ap;
	va_start (ap, msg);
	vsnprintf(buffer, 4096, msg, ap);
	buffer[4095] = '\0';
	va_end (ap);
#endif
	MessageBox(NULL,L"test",L"DGL encountered a critical_error:",MB_OK | MB_ICONINFORMATION);
#else 
	// other OS'es, print the error messagt to stdout. 
	va_list ap;
	va_start (ap, msg);
	fprintf(stderr, "DGL encountered a critical error: ");
	vfprintf(stderr, msg, ap);
	va_end (ap);
	fprintf(stderr, "\n");
#endif

	exit(1);
}