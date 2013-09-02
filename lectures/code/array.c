#include "stdio.h"
#include "stdlib.h"
#define WIDTH 5
#define HEIGHT 3

int jimmy [HEIGHT][WIDTH];
int n,m;

int main(int argc, char const *argv[])
{
	for (int n = 0; n < HEIGHT; n++)
	{
		for (int m = 0; m < WIDTH; m++)
		{
			jimmy[n][m] = (n+1)*(m+1);
		}
	}
	
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			printf("%i ", jimmy[i][j]);
		}
		printf("\n");
	}

	return 0;
}
