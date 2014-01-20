#include <stdio.h>
#include <stdlib.h>

#ifndef SEGYREADER_H_
#define SEGYREADER_H_
void ReadSEGYTraceSamples(char *fileName, char *matrix, size_t traces, size_t samples);
#endif
