#include "SEGYReader.h"

void ReadSEGYTraceSamples (char *fileName, char *matrix, size_t traces, size_t samples)
{
  // Creating a file pointer. Read only, binary type.
  FILE* fileP = fopen(fileName, "rb");
  // Skipping 3600 byte header, from beginning of file
  fseek(fileP, 3600, SEEK_SET);

  for (int i = 0; i < traces; i++)
  {
    // Skipping 240 byte trace header, from current file pointer loc.
    fseek(fileP, 240, SEEK_CUR);
    for (int j = 0; j < samples; j++)
    {
      /*
      * fread(pointer, size, count, stream)
      *   pointer - Pointer to the block to write to
      *   size - Size in bytes of each elements
      *   count - Number of elements to read
      *   stream - Pointer to a file object to use as input stream
      */
      fread(&matrix[i*samples+j], 1, 1, fileP);
    }
  }
  fclose(fileP);
}
