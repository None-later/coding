#include <stdio.h>
#include <string.h>
#include <math.h>
#include<stdlib.h>
void print(char* C)
{
	while (*C != '\0')
	{
		printf("%c", *C);
		C++;
	}
	printf("\n");
}

int Add(int a, int b)
{
	return a + b ;
}

void A()
{
	printf("Hello");
}
void B(void (*ptr)())
{
	ptr();
}

int compare (const void* a, const void* b)
{
	return (abs(*((int*)a)) < abs(*((int*)b))) ? 1 : -1;
}

void sort(int* A, int n, int (*compare) (int, int))
{
	// bubble sort
	int i, j, temp;
	for (i = 0; i < n; i++)
	{
		for (j = i+1; j < n; ++j)
		{
			if (compare(A[i], A[j]) > 0)
			{
				temp = A[i];
				A[i] = A[j];
				A[j] = temp;
			}
		}
	}
}

int main()
{
	int i, A[] = {-31,22,-1,50,-6,4};

	qsort(A,6, sizeof(int), compare);
	for (i = 0; i < 6; ++i)
	{
		printf("%d ", A[i]);
	}
	getchar();
	return 0;
}