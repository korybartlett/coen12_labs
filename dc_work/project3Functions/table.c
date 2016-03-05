/*Kory Bartlett
 * Dr. Atkinson
 * COEN 12 10:30
 * Thursday 2:15
 * Project 3
 *
 * File: Table.c
 *
 *Description: This file containts the functions that create a set and identifiers, free the memory occupied by the set, output the number of elements in the set, determine if an element exsists in the set, add an element into the set if it does not previously exsist in the set, and remove the element if it is in the set.
 *
 * Note that this file has a hashtable so the elements were placed into the array in order they were hashed from the file and due to the collisions that may have occured during placement.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include "set.h"
#define empty 0
#define filled 1
#define deleted 2

int findElement(SET *sp, char *elt, bool *find);
unsigned hashString(char *s);

/*
 * Defines the elements insdie the structure
 *Best/Worst Case O(1)
 */
struct set
{
	int count;
	int length;
	char *flag;
	char**elts;
};

/*
 * Creates a set with maximum capacity of maxElts
 *Worst/Best Case O(n)
 */
SET *createSet(int maxElts)
{
	int i;

	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->elts = malloc(sizeof(char*)*maxElts);
	assert(sp->elts!=NULL);
	sp->flag = malloc(sizeof(char)*maxElts);
	assert(sp->flag != NULL);
	for(i=0; i < sp->length; i++)
	{
		sp->flag[i] = empty;
	}	
	return sp;
}

/* 
 *Returns the number of elements in the set pointed to by sp
 *Worst/Best Case O(1)
 */
int numElements(SET *sp)
{
	assert(sp!=NULL);
	return sp->count;
}

/*
 * Frees the memory allocated for the set by first clearing the array followed by the array itself then finally destroying the set at the end
 *Worst/Best Case O(n)
 */
void destroySet(SET *sp)
{
	assert (sp!=NULL);
	int i;
	for (i=0; i < sp->length; i++)
	{
		if(sp->flag[i] == filled)
		{	
			free(sp->elts[i]);
		}
	}
	free(sp->flag);
	free(sp->elts);
	free(sp);
}

/*
 * Calls findElement which will return the position of an element.
 * If the element is not in the array then hasElement will indicate that it is not in the array by returning false.
 *Worst Case O(n)
 *Best Case O(1)
 */
bool hasElement(SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);
	bool found;
	findElement(sp, elt, &found);
	return found;
}	

/*
 * Calls hashString to decide initial location of an element.
 * The initial location is used to linear probe through the for loop to decide where the final location of the element will be placed. 
 * Checks the flags to find a position for the element to be placed.
 * If the flag is empty then checks if a marker was found, if marker was not found the empty spot is returned. If marker is found then return the position of the marker.
 * If the flag is filled, the element is compared to what is already in the set. If they are the same then the position is returned of the element and found is true to mark there was a match.
 * If the flag is deleted, the first deleted spot is saved for later use and marker is made one.
 * Worst Case O(n)
 * Best Case O(1)
 */
int findElement(SET *sp, char *elt,bool  *found) 
{
	assert(sp!=NULL && elt!=NULL);
	int i, location, firstDeleted; 
	int marker = 0;
	unsigned hash;
	hash = hashString(elt) % sp->length;
	
	for(i= 0; i < sp->length; i++)
	{
		location = (hash + i) % sp->length;

		if(sp->flag[location] == empty)
		{
			*found = false;

			if(marker == 1)
			{
				return firstDeleted;
			}

			return location;
		}

		else if(sp->flag[location] == filled)
		{
			if(strcmp(elt,sp->elts[location]) == 0)
			{
				*found = true;

				return location;
			}
		}

		else if(sp->flag[location] == deleted)
		{
			if(marker == 0)
			{
				firstDeleted = location;
				
				marker = 1;
			}
		}
	}

	*found = false;
	return firstDeleted;
}

/*
 *Calls findElement to determine if an element exsists in the array.
 *If the element is not found in the array the position of where the element belongs is returned.
 *The flag at the position of where the element was added is changed to filled.
 *Worst Case O(n)
 *Best Case O(1)
 */
bool addElement (SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);
	bool found;
	int i;
	
	if (sp->count == sp->length)
	{
		found = false;
		return found;
	}

	i = (findElement(sp, elt, &found));
	
	if(found == false)
	{
		elt = strdup(elt);
		sp->elts[i] = elt;
		sp->count++;
		sp->flag[i] = filled;
		found = true;
	}
	
	return found;
}

/*
 *Calls findElement to check if element exsists in the array.
 *If the element exsists in the array its position in the array is returned along with true.
 *The element is deleted and flag at that positin is changed to deleted. 
 *Worst Case O(n)
 *Best Case O(1)
 */
bool removeElement(SET *sp, char *elt)
{
	assert(sp!=NULL && elt!=NULL);
	int i;
	bool found;
	
	if (sp->count == sp->length)
	{
		found = false;
		return found;
	}

	i = (findElement(sp, elt, &found));
	
	if (found == true)
	{
		free(sp->elts[i]);
		sp->flag[i] = deleted;
		sp->count--;
		found = true;
	}

	return found;
}

/*
 *Called by findElement to hash a location for the string that is passed as an arguement. 
 * Best Case: 0(n)
 * Worst Case: 0(n)
 * */
unsigned hashString(char *s)
{
	unsigned hash = 0;
	
	while(*s != '\0')
	{
		hash = 31 * hash + *s++;
	}
	
	return hash;
}
