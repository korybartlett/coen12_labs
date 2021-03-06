#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "deque.h"
/*
 * comments: asserts, O (1),  
 *O(1)
 *Creates the nodes structure used by deque for the linked lists.
 *O(1)
 * */
typedef struct node 
{
	int data;
	struct node *next;
	struct node *prev;
}NODE;

/*
 * Creates the deque which stores the number of nodes in the deque and creates the dummy head node.
 * O(1)
 */
struct deque
{
	int count;
	struct node *head;
};

/*
 * Creates the deque and intializes the values in the deque.
 * O(1)
 */
DEQUE *createDeque(void)
{
	DEQUE *dp;
	dp = malloc(sizeof(DEQUE));//creates deque pointer that points to deque
	assert(dp!=NULL);
	dp->count = 0;
	dp->head = malloc(sizeof(NODE));//creates dummy node 
	//creates circular list 
	dp->head->next = dp->head;
	dp->head->prev = dp->head;
	assert (dp->head!=NULL);
	return dp;
}

/*
 *Deletes every node in the the deque.
 *O(1)
 */
void destroyDeque(DEQUE *dp)
{
	assert(dp!=NULL);
	struct node *prev, *lead;
	prev = dp->head->next;//sets prev to the first node after the head
	while(prev != dp->head)
	{
		lead = prev->next;//assigns lead to the node after prev
		free(prev);
		prev = lead;//moves prev to lead
	}
	free(dp->head);
	free(dp);
}

/*
 *Returns the count in the deque.
 *O(1)
 */
int numItems(DEQUE *dp)
{
	assert(dp!=NULL);
	return dp->count;
}

/*
 * Adds a node in the first spot after the dummy node. Switches the pointers so that the list is kept as a circular doubly linked list.
 *O(1)
 */
void addFirst(DEQUE *dp, int x)
{
	assert(dp!=NULL);
	struct node  *pNew, *temp;
	pNew = malloc(sizeof(NODE));
    assert(pNew != NULL);
	temp = dp->head;//sets temp to the dummy node
	pNew->data = x;//saves the data recieved to the node created
	dp -> count++;
	//creats space for pNew to be inserted into list after the head and adjusts pointers accordingly
	pNew->next = temp->next;
	pNew->prev = temp;
	temp->next = pNew;
	temp->next->prev = pNew;
	return;
}

/*
 * Adds a ndoe in the last spot before the dummy node. Switches the pointers so that the nodes are kept in circular doubly linked list.
 *O(1)
 */
void addLast(DEQUE *dp, int x)
{
	assert(dp!= NULL);
	struct node *pNew, *temp;
	pNew = malloc(sizeof(NODE));
    assert(pNew != NULL);
	temp = dp->head;//sets temp to the dummy node
	pNew->data = x;//puts the number recieved into the new node
	dp->count++;
	//creats space for pNew to be inserted into list before the head and adjusts pointers accordingly 
	pNew->next = temp;
	pNew->prev = temp->prev;
	temp->prev->next = pNew;
	temp->prev = pNew;	
	return;
}

/*
 * removes the first node after the dummy node.
 *O(1)
 */
int removeFirst(DEQUE *dp)
{
	assert(dp!=NULL);
	if(dp->count==0)
	{
		return -1;
	}
	int x;
	struct node *temp, *np;
	temp = dp->head;//sets temp to the dummy node
	dp->count--;
	np = temp->next;//sets np to the first node
	//delets the space held by pNew by adjusting pointers accordingly
	temp->next = temp->next->next;
	np->next->prev = temp;
	x = np->data;//saves the data from the node being deleted
	free(np);
	return x;
}

/*
 * Removes the last node which is the node before the dummy node.
 *O(1)
 */
int removeLast(DEQUE *dp)
{
	assert(dp!=NULL);
	if(dp->count == 0)
	{
		return -1;
	}

	int x;
	struct node *temp, *np;
	temp = dp->head;//assigns the dummy node to temp
	dp->count--;
	np = temp->prev;//sets np to the last node
	//delets the space held by pNew by adjusting pointers accordingly
	temp->prev = temp->prev->prev;
	temp->prev->next = temp;
	x = np->data;//saves the data in the node being deleted so it can be returned
	free(np);
	return x;
}

/*
 *Gets the first node that is after the dummy node.
 *O(1)
 */
int getFirst(DEQUE *dp)
{
	assert(dp!=NULL);
	if(dp->count==0)//checkts that the list has elements
	{
		return -1;
	}
	struct node *temp;
	temp = dp->head->next;//sets the first node to temp
	return temp->data;
}

/*
 *Gets the last node in the list which is the node before the dummy node.
 *O(1)
 */
int getLast (DEQUE *dp)
{
	assert(dp!=NULL);
	if(dp->count==0)//checks that list has elements
	{
		return -1;
	}
	struct node *temp;
	temp = dp->head->prev;//sets the last node to temp
	return temp->data;
}
