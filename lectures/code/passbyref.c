#include "stdio.h"

void foo(int *x)
{
	printf("In foo(): %d\n", *x);
	*x = 10;
	printf("In foo(): %d\n",*x );
}

int main(int argc, char const *argv[])
{
	int i = 5;

	printf("In main(): %d\n", i);
	foo(&i);
	printf("In main(): %d\n", i);
	return 0;
}
