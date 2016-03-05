#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "deque.h"
/*
 * comments: asserts, O (1),  
 *
 * */
typedef struct node 
{
	int data;
	struct node *next;
	struct node *prev;
}NODE;

struct deque
{
	int count;
	struct node *head;
};

DEQUE *createDeque(void)
{
	DEQUE *dp;
	dp = malloc(sizeof(DEQUE));
	assert(dp!=NULL);
	dp->count = 0;
	dp->head = malloc(sizeof(NODE));
	dp->head->next = dp->head;
	dp->head->prev = dp->head;
	assert (dp->head!=NULL);
	return dp;
}

void destroyDeque(DEQUE *dp)
{
	assert(dp!=NULL);
	struct node *prev, *lead;
	prev = dp->head->next;
	while(prev != dp->head)
	{
		lead = prev->next;
		free(prev);
		prev = lead;
	}
	free(dp->head);
	free(dp);
}

int numItems(DEQUE *dp)
{
	assert(dp!=NULL);
	return dp->count;
}

void addFirst(DEQUE *dp, int x)
{
	assert(dp!=NULL);
	struct node  *pNew, *temp;
	pNew = malloc(sizeof(NODE));
	temp = dp->head;
	pNew->data = x;
	dp -> count++;
	pNew->next = temp->next;
	pNew->prev = temp;
	temp->next = pNew;
	temp->next->prev = pNew;
	return;
}

void addLast(DEQUE *dp, int x)
{
	assert(dp!= NULL);
	struct node *pNew, *temp;
	pNew = malloc(sizeof(NODE));
	temp = dp->head;
	pNew->data = x;
	dp->count++;
	pNew->next = temp;
	pNew->prev = temp->prev;
	temp->prev->next = pNew;
	temp->prev = pNew;	
	return;
}

int removeFirst(DEQUE *dp)
{
	assert(dp!=NULL);
	if(dp->count==0)
	{
		return -1;
	}
	int x;
	struct node *temp, *np;
	temp = dp->head;
	dp->count--;
	np = temp->next;
	temp->next = temp->next->next;
	np->next->prev = temp;
	x = np->data;
	free(np);
	return x;
}

int removeLast(DEQUE *dp)
{
	assert(dp!=NULL);
	if(dp->count == 0)
	{
		return -1;
	}

	int x;
	struct node *temp, *np;
	temp = dp->head;
	dp->count--;
	np = temp->prev;
	temp->prev = temp->prev->prev;
	temp->prev->next = temp;
	x = np->data;
	free(np);
	return x;
}

int getFirst(DEQUE *dp)
{
	assert(dp!=NULL);
	if(dp->count==0)
	{
		return -1;
	}
	struct node *temp;
	temp = dp->head->next;
	return temp->data;
}

int getLast (DEQUE *dp)
{
	assert(dp!=NULL);
	if(dp->count==0)
	{
		return -1;
	}
	struct node *temp;
	temp = dp->head->prev;
	return temp->data;
}
