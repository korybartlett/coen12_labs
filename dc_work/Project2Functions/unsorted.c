/*Kory Bartlett
 * Dr. Atkinson
 * 10:30
 * Thursday 2:15
 * Project 2
 *
 * File: Unsorted.c
 *
 *Description: This file containts the functions that create the set, free the memory occupied by the set, output the number of elements in the set, determine if an element exsists in the set, add an element into the set if it does not previously exsist in the set, and remove the element if it is in the set.
 *
 * Note that this file is unsorted so the elements were placed into the array in order they were read from the file.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include "set.h"

int findElement(SET *sp, char *elt);

/*
 * Defines the elements insdie the structure
 *O(1)
 */
struct set
{
	int count;
	int length;
	char**elts;
};

/*
 * Creates a set with maximum capacity of maxElts
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
 *Returns the number of elements in the set pointed to by sp
 *O(1)
 */
int numElements(SET *sp)
{
	assert(sp!=NULL);
	return sp->count;
}

/*
 * Frees the memory allocated for the set by first clearing the array followed by the array itself then finally destroying the set at the end
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
 * Calls findElement which will return either the position of an element or -1 if it is not in the array.
 * If the element is not in the array then hasElement will indicate that it is not in the array
 *O(n)
 */
bool hasElement(SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);
	int i;
	bool found = false;
	i = findElement(sp, elt);
	if(i!=-1)
	{
		found = true;
	}
	return found;
}	

/*
 *Checks if there are initially any elements in the arry.
 *Then transverses the array to check the elements of the array to see if it already exsists in the array.
 *Outputs either the position of element if found or -1 if not in the array.
 *O(n)
 */
int findElement(SET *sp, char *elt) 
{
	assert(sp!=NULL && elt!=NULL);
	int i;

	if(sp->count == 0)
	{
		return -1;
	}

	for(i = 0; i < sp->count; i++)
	{
		if (strcmp(elt, sp->elts[i])==0)
			{
				return i;
			}
	}

	return -1;
}

/*
 *Calls findElement to determine if an element exsists in the array.
 *If the element is not found in the array it is added to the end of the arrary.
 *O(n)
 */
bool addElement (SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);
	bool found = false;
	int i;
	
	if (sp->count == sp->length)
	{
		return found;
	}

	i = (findElement(sp, elt));
	elt = strdup(elt);
	if(i == -1)
	{
		sp->elts[sp->count]= elt;
		sp->count++;
		found = true;
	}
	
	return found;
}

/*
 *Calls findElement to check if element exsists in the array.
 *If the element exsists in the array its position in the array is returned.
 *The element is deleted then replaced by the element that was initialy in the final spot of the array.
 *O(n)
 */
bool removeElement(SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);
	bool found = false;
	
	if (sp->count == sp->length)
	{
		return found;
	}

	int i  = (findElement(sp, elt));
	
	if (i != -1)
	{
		free(sp->elts[i]);
		sp->elts[i] = sp->elts[sp->count-1];
		sp->count--;
		found = true;
	}

	return found;
}
