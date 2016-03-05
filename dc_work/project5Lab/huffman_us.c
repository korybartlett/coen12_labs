#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "tree.h"
#include "pack.h"

void insert(struct tree *);
struct tree *delete(void);
void encoding(struct tree *);

int counter = 0;
int i;
struct tree *leaves[257];
struct tree *heap[257];

int main(int argc, char *argv[])
{
	FILE *fp;
	int c, new;
	int count[257];
    struct tree *FirstMin, *SecondMin, *NewMin;
	
	fp = fopen(argv[1], "rb");
	if(fp == NULL)
	{
		printf("File could not be opened\n");
		return -1;
	}
	
	for(i=0; i<257; i++)
	{
		leaves[i] = NULL;
	}
	
	for(i=0;i<257;i++)
	{
		count[i] = 0;
	}

	while((c=getc(fp))!=EOF)
	{
		count[c]++;
	}
/*	
			int t = 0;
			for(i=0;i<257;i++)
			{
				t+=count[i];
			}
			printf("%d\n", t);
*/	
	for(i=0;i<257;i++)
	{
		if(count[i]>0)
		{
			leaves[i] = createTree(count[i], NULL, NULL);
			insert(leaves[i]);
		}
	}
	
	leaves[256] = createTree(0, NULL, NULL);
	insert(leaves[256]);
/*	
	int h = 0;
	for(i=0; i<counter; i++)
	{
		h += getData(heap[i]);
	}
		printf("%d\n", h);
*/
//	int f = counter;

	while(counter!=1)
	{
		FirstMin = delete();
		SecondMin = delete();
		new = getData(FirstMin) + getData(SecondMin);
		NewMin = createTree(new, FirstMin, SecondMin);
		insert(NewMin);
	}
/*	
	for(i=0; i<f; i++)
	{
		printf("%d: %d\n", i, getData(heap[i]));
	}
	
	printf("%d\n", getData(heap[0]));
*/
	for(i=0;i<257;i++)
	{
		if(leaves[i]!= NULL)
		{
			if(isprint(i))
			{
				printf("'%c': %d ",i, getData(leaves[i]));
				encoding(leaves[i]);
				printf("\n");
			}

			else
			{
				printf("%03o: %d ",i, getData(leaves[i]));
				encoding(leaves[i]);
				printf("\n");
			}
		}
	}
	pack(argv[1], argv[2], leaves);
}

void insert(struct tree *leaf)
{
	heap[counter] = leaf;
	counter++;
}

struct tree *delete(void)
{
	int lowest, x;
	struct tree *min;
	lowest = getData(heap[0]);
	x = 0; 
	min = heap[0];
	for(i=0;i<counter;i++)
	{
		if(lowest>getData(heap[i]))
		{
			lowest = getData(heap[i]);
			min = heap[i];
			x = i;
		}
	}

	heap[x] = heap[counter-1];
	counter--;
	return min;
}

void encoding(struct tree *leaves)
{
	struct tree *parent;
	parent = getParent(leaves);
	if(parent != NULL)
	{	
		if(getLeft(parent) == leaves)
		{
			encoding(parent);
			printf("0");
			return;
		}
		else
		{
			encoding(parent);
			printf("1");
			return;
		}
	}
	else
	{
		return;
	}
}
