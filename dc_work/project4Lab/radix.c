#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "deque.h"
#define r 10 

int main (void)
{ 
	int input, i, j, numElem, numElemB, digits, value, position, divisor, element, b, d;
	int max = 0;
	DEQUE *dp;
	DEQUE *bucket[r];
	dp = createDeque();

	for(i =0; i < r; i++)
	{
		bucket[i] = createDeque();
	}

	while(scanf("%d", &input)==1)
	{
		if(input < 0)
		{
			for(d=0;d<r;d++)
			{
				destroyDeque(bucket[d]);
			}

			destroyDeque(dp);
			return printf("Error: negative number input\n");
		}
		
		if(max < input)
		{
			max = input;
		}
		

		addLast(dp, input);
	} 

	digits = ceil(log(max + 1)/log(r));
	numElem = numItems(dp);
	divisor = 1;

	for(j = 0; j < digits; j++)
	{
		for(i = 0; i < numElem; i++)
		{
			value = removeFirst(dp);
			position = (value / divisor) % r ;
			addLast(bucket[position],value);
				
		}	
		divisor = divisor * 10;
	
		for(i = 0; i < r; i++)
		{
			numElemB = numItems(bucket[i]);
			for(b=0;b<numElemB;b++)
			{
				element = removeFirst(bucket[i]);
				addLast(dp, element);
			}
		}

	}


	for (i = 0; i < numElem; i++)
	{
		printf("%d\n", removeFirst(dp));
	}
	for(d=0;d<r;d++)
	{
		destroyDeque(bucket[d]);
	}
	destroyDeque(dp);
}
