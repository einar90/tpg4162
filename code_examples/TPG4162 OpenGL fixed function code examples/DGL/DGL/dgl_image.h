#include "dgl.h"

struct DGLImage
{
	unsigned int width, height;
	GLenum format;
	void* pointer;
};

// load an image from file into the img struct
struct DGLImage* dglCreateImage(char* filename);

// Free an img struct
void dglFreeImage(struct DGLImage* img);

// load an complete GL texture
GLuint dglLoadTexture(char* filename, GLenum minfilter = GL_LINEAR_MIPMAP_LINEAR, GLenum magfilter = GL_LINEAR);