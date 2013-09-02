#include "stdio.h"

int main(int argc, char const *argv[])
{
	int *a; // derfne a pointer to a mem loc interpreted as an int
	int b;	// Define a mem holding an int

	b = 21;	// b is set to 21
	a = &b;	// let a point to the address of b

	*a = 42; // mem loc pointed to by a set to int value 42

	printf("*a:%d, b:%d \n", *a, b);
	return 0;
}
