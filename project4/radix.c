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
	DEQUE *bucket[r];//creates bucket that has ten categories
	dp = createDeque();//creates the deque and assigns it to dp

	for(i =0; i < r; i++)//loop to create the ten buckets needed
	{
		bucket[i] = createDeque();
    }

	while(scanf("%d", &input)==1)
	{
		if(input < 0)//checks to make sure no negative numbers are input
		{
			for(d=0;d<r;d++)//destroys the ten bucket deques and main deque
			{
				destroyDeque(bucket[d]);
			}

			destroyDeque(dp);
			return printf("Error: negative number input\n");
		}
		
		if(max < input)//saves the max number 
		{
			max = input;
		}
		

		addLast(dp, input);//adds the input to the end of the main deque
	} 

	digits = ceil(log(max + 1)/log(r));//saves the amount of significant figures in the biggest number
	numElem = numItems(dp);//saves the number of elements in the deque to numElem
	divisor = 1;

	for(j = 0; j < digits; j++)//loops to check each digit of the numbers input
	{
		for(i = 0; i < numElem; i++)//places the numbers in their corresponding bucket for thier digit being checked
		{
			value = removeFirst(dp);//saves the value of the removed node
			position = (value / divisor) % r ;//checks the siginificant digit
			addLast(bucket[position],value);//adds the number to the end of the significant digit bucket that it corresponds with
				
		}	
		divisor = divisor * 10;//increases divisor so that it can check the next significant digit
	
		for(i = 0; i < r; i++)//removes the numbers from the bucket and readds the numbers to the main deque
		{
			numElemB = numItems(bucket[i]);//obtains the number of elements from the bucket
			for(b=0;b<numElemB;b++)//removes the elements from the buckets and moves them into the main deque
			{
				element = removeFirst(bucket[i]);//removes the first element from the bucket 
				addLast(dp, element);
			}
		}

	}


	for (i = 0; i < numElem; i++)//loop to print out the elements from the deque
	{
		printf("%d\n", removeFirst(dp));
	}
	for(d=0;d<r;d++)//destroys the buckets and the deque
	{
		destroyDeque(bucket[d]);
	}
	destroyDeque(dp);
}
