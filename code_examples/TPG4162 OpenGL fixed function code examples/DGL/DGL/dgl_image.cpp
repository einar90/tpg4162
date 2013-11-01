#include "dgl.h"
#include <SDL_image.h>

// load an image from file into the img struct
DGLImage* dglCreateImage(char* filename)
{
	DGLImage* retval;

	retval = (struct DGLImage*) malloc(sizeof(DGLImage));
	if(!retval) return NULL;
	memset(retval, 0, sizeof(DGLImage));

	SDL_Surface* sdl_i = IMG_Load(filename);
	if(!sdl_i) { printf("%s\n", SDL_GetError()); exit(1); return NULL;}

	retval->width = sdl_i->w;
	retval->height = sdl_i->h;

	if(sdl_i->format->BitsPerPixel == 32) retval->format = GL_RGBA;
	else if(sdl_i->format->BitsPerPixel == 24) retval->format = GL_RGB;
	else 
	{
		SDL_FreeSurface(sdl_i);
		return NULL;
	}

	int size = sdl_i->w * sdl_i->h * sdl_i->format->BitsPerPixel/8;
	retval->pointer = malloc(size);
	if(!retval->pointer) 
	{
		SDL_FreeSurface(sdl_i);
		return NULL;
	}
	
	SDL_LockSurface( sdl_i );
	memcpy(retval->pointer, sdl_i->pixels, size);

	SDL_UnlockSurface( sdl_i );
	SDL_FreeSurface(sdl_i);

	return retval;
}

// Free an img struct
void dglFreeImage(struct DGLImage* img)
{
	free(img->pointer);
	free(img);
}


// load an image from file into the img struct
GLuint dglLoadTexture(char* filename, GLenum minfilter, GLenum magfilter)
{
	DGLImage* img;
	img = dglCreateImage(filename);
	if(img == NULL) return 0;
	
	glEnable(GL_TEXTURE_2D);

	GLuint TEXTURE_ID;
    glGenTextures(1, &TEXTURE_ID);
    glBindTexture(GL_TEXTURE_2D,TEXTURE_ID);

    if(magfilter != GL_NEAREST) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    }
    glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, magfilter);
    glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, minfilter);

    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA,
                   img->width,
                   img->height, 0,
                   img->format, GL_UNSIGNED_BYTE,
                   img->pointer);

	if(minfilter == GL_NEAREST_MIPMAP_NEAREST || 
	   minfilter == GL_NEAREST_MIPMAP_LINEAR || 
	   minfilter == GL_LINEAR_MIPMAP_NEAREST || 
	   minfilter == GL_LINEAR_MIPMAP_LINEAR )
	{
		glGenerateMipmapEXT(GL_TEXTURE_2D);
	}

    glDisable(GL_TEXTURE_2D);


	dglFreeImage(img);
	return TEXTURE_ID;
}