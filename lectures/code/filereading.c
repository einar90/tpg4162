#include "stdio.h"

char matrix[13483][1750];

void ReadSEGYTrace1Samples (char* sFileName)
{
	FILE* pFile = fopen(sFileName, "rb"); // Read only binary
	fseek(pFile, 3600, SEEK_SET);	// Skip file header

	for (int i = 0; i < 13483; i++)		// Loop over num of traces
	{
		fseek(pFile, 240, SEEK_CUR);	// Skip trace header
		for (int j = 0; j < 1750; j++)	// Loop through 1750 samples
		{
			fread(&matrix[i][j], 1, 1, pFile); // Read each 1B sample
		}
	}

	fclose(pFile);
}
