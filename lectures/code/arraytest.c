#include "stdio.h"
int matrix[4][4];

int setMatrixValues() {
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			matrix[i][j] = i+j;
		}
	}
}

void printMatrix() {
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char const *argv[])
{
	setMatrixValues();
	printMatrix();
	return 0;
}