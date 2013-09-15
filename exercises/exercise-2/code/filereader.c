#include "stdio.h"
#include "stdlib.h"
#define HEIGHT 13483
#define WIDTH 1750

/* 
* 	Using char because each value in the data file is 
* 	one byte, and so is a char-element. int causes problems
* 	because it contains 4 bytes.
*/
char matrix[HEIGHT][WIDTH];


void ReadSEGYTraceSamples (char *fileName)
{
	// Creating a file pointer. Read only, binary type.
	FILE* fileP = fopen(fileName, "rb"); 

	// Skipping 3600 byte header, from beginning of file
	fseek(fileP, 3600, SEEK_SET); 

	for (int i = 0; i < HEIGHT; i++)
	{
		// Skipping 240 byte trace header, from current file pointer loc.
		fseek(fileP, 240, SEEK_CUR);
		for (int j = 0; j < WIDTH; j++)
		{
			/*
			* fread(pointer, size, count, stream)
			*	pointer - Pointer to the block to write to
			* 	size - Size in bytes of each elements
			* 	count - Number of elements to read
			* 	stream - Pointer to a file object to use as input stream
			*/
			fread(&matrix[i][j], 1, 1, fileP);
		}
	}
	fclose(fileP);
}

void printSampleValues() {
	for (int i = 40; i < 55; i++)
	{
		printf("%d ", matrix[50][i]); // Printing char as digit
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
	ReadSEGYTraceSamples("../../../SEGY/NVGT-88-06.sgy");
	printSampleValues();
	return 0;
}