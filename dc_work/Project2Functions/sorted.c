/*Kory Bartlett
 * Dr. Atkinson
 * 10:30
 * Thursday 2:15
 * Project 2
 *
 * File: Sorted.c
 *
 *Description: This file containts the functions that create the set, free the memory occupied by the set, output the number of elements in the set, determine if an element exsists in the set, add an element into the set if it does not previously exsist in the set, and remove the element if it is in the set.
 * Note that this file is sorted so it organized the elements during addElement to ensure a faster run time.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include "set.h"
int findElement(SET *sp, char *elt, bool *find);

/*
 *Defines the elements insdie the structure
 *O(1)
 */
struct set
{
	int count;
	int length;
	char**elts;
};

/*
 *Creates a set with maximum capacity of maxElts which is defined in the main
 *O(1)
 */
SET *createSet(int maxElts)
{
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->elts = malloc(sizeof(char*)*maxElts);
	assert(sp->elts!=NULL);
	return sp;
}

/*
 * Firstly Transverses the array of elements to delete each element then deletes the array followed by the structure itself
 *O(n)
 */
void destroySet(SET *sp)
{
	assert (sp!=NULL);
	int i;
	for (i=0; i < sp->count; i++)
	{
		free(sp->elts[i]);
	}
	free(sp->elts);
	free(sp);
}

/*
 *Returns the number of elements in the set pointed to by sp
 *0(1)
 */
int numElements(SET *sp)
{
	assert(sp!=NULL);
	return sp->count;
}

/*
 * sends a blank bool to findElement and is returned with bool as true, if element found, and false, if elmenet not found
 *0(logn)
 */
bool hasElement(SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);
	bool found;
	findElement(sp, elt, &found);
	return found;
}	

/*Searches array by checking average of lo and hi elements, which is assigned to mid, to the recieved element.
 * if the element is smaller than the element in the array then the hi is reduced to truncate the amount of searched elements.
 * if the element is bigger than the element in the array then the lo is raised to compress the possible range of the element being added.
 * If the element matches with an element in the array it is found and true is returned as well as its posisiton.
 * If the element is never found then found is assigned false and the location where the element should go is returned.
 * 0(logn)
 * */
int findElement(SET *sp, char *elt,bool *found) 
{
	assert(sp!= NULL && elt != NULL);
	int lo, mid, hi, diff;
	lo = 0;
	hi =sp->count - 1;
	
	while (lo <= hi)
	{
	
		mid = (lo + hi)/2;
		diff = strcmp(elt, sp->elts[mid]);
		
		if(diff < 0)
		{
			hi = mid - 1;
		}

		else if(diff > 0)
		{
			lo = mid + 1;
		}

		else
		{
			*found = true;
			return mid;
		}
		
	}

	*found = false;
	return lo;
}

/*Calls findElement to check if the element exsists in the array and also finds the location of where the element should go.
 * If the element is not found in the array, the array is transversed from end to the beginning. 
 * The elements are shifted from the left to right until the location needed for the element is made available.
 * O(n)
 * */
bool addElement (SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);
	elt = strdup(elt);
	assert(elt!=NULL);
	bool found;
	
	if(sp->count == 0)
	{
			sp->elts[sp->count] = elt;
			sp->count++;
			return found;
	}
	
	if (sp->count == sp->length)
	{
		found = false;
		return found;
	}


	int i, location;
	location = (findElement(sp, elt, &found));
	
	if( found == false)
	{
		
		for(i = sp->count; i > location; i--) 
		{	
			sp->elts[i] = sp->elts[i-1];
		}
		sp->elts[i] = elt;
		sp->count++;
	}
	
	return found;
}

/*Calls findElement to check if the element previously exsisted in the array.
 * If true is returned then the location of the element is freed to delete the element.
 * The array is then trasnverse from beginning to end.
 * The elements are shifted from right to left to fill the void left by the element.
 * O(n)
 * */
bool removeElement(SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);
	bool found;
	
	if (sp->count == sp->length)
	{
		found = false;
		return found;
	}

	if (sp->count == 0)
	{
		found = false;
		return found;
	}
	
	int i, location;  
	location = (findElement(sp, elt, &found));
		
	if (found == true)
	{
		free(sp->elts[location]);
		for(i = location; i < sp->count; i++)
		{
			sp->elts[i] = sp->elts[i+1];
		}
		
		sp->count--;
	}

	return found;
}
