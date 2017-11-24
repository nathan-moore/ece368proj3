#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CASES 800000

int intcmp(const void* n1,const void* n2);

int main(void)
{
	srand(time(NULL));
	int testCase[CASES];
	for(int i = 0; i < CASES;i++)
	{
		testCase[i] = rand();
	}

	Heap* h = pQueueInit(CASES);

	for(int i = 0; i < CASES;i++)
	{
		addQueue(h,i,testCase[i]);
	}

	qsort(testCase,CASES,sizeof(*testCase),intcmp);

	for(int i = 0;i < CASES;i++)
	{
		data d;
		pop(h,&d);
		if(d.distance != testCase[i])
		{
			printf("Error with sorting");
			printf("%d, expected %d got %d",i,testCase[i],d.distance);

		}
	}

	int bug[] = {1,2,3};
	for(int i = 0;i < 3;i++)
	{
		addQueue(h,i,bug[i]);
	}

	for(int i = 0;i < 3;i++)
	{
		data d;
		pop(h,&d);
		printf("%i\n",d.distance);
	}
}

int intcmp(const void* n1,const void* n2)
{
	int* i1 = (int *)n1;
	int* i2 = (int *)n2;

	return *i1 - *i2;
}
