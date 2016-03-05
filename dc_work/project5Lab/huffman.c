/*
 Kory Bartlett
 Dr. Atkinson
 COEN 12 9:15
 Project 5
 
 File Descprition: Creates a primary queue through a binary heap incorporating huffman coding. This type of sorting allows for lossless data compression when compressing and uncompressing the files.
 */
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "tree.h"
#include "pack.h"

void insert(struct tree *);
struct tree *delete(void);
void encoding(struct tree *);

/*Global Variables and arrays used*/
int counter = 0;
int i;
struct tree *leaves[257];
struct tree *heap[257];

int main(int argc, char *argv[])
{
    if(argc!=3)//checks for correct numbe of files used
    {
        printf("Improper number of files used\n");
        return -1;
    }
	FILE *fp;
	int c, new;
	int count[257];
    struct tree *FirstMin, *SecondMin, *NewMin;
	
	fp = fopen(argv[1], "rb");//opens file argv[1] to be read
	
    if(fp == NULL)
	{
		printf("File could not be opened\n");
		return -1;
	}
	
    /*Initializes the count array to zero*/
    for(i=0;i<257;i++)
	{
		count[i] = 0;
	}
    
    /*Initializes the leaves array to NULL*/
	for(i=0; i<257; i++)
	{
		leaves[i] = NULL;
	}
    
    /*Reads each character from the file till the end of file.
     Saves the ASCII value of a character in c*/
	while((c=getc(fp))!=EOF)
	{
		count[c]++;//increases the count of an ASCII value in the corresponding slot in the array for each time the ASCII value occurs in the file
	}
    fclose(fp);
    
    /*Inserts values into the heap and leaves arrays that have a non-zero count in the count array*/
	for(i=0;i<257;i++)
	{
		if(count[i]>0)
		{
			leaves[i] = createTree(count[i], NULL, NULL);//creates a tree in the leaves array with its corresponding spot from the count array
			insert(leaves[i]);//inserts the created tree from leaves into the binary heap
		}
	}
	
	leaves[256] = createTree(0, NULL, NULL);//creates an end of file marker tree marked by zero into the final spot of the leaves array
	insert(leaves[256]);//puts the end of file marker in the binary heap as well

	while(counter!=1)//loops until counter for number of trees in the binary heap is 1
	{
		FirstMin = delete();//finds the smallest value in binary heap and removes it
		SecondMin = delete();//finds the second smallest value in the binary heap and removes it
		new = getData(FirstMin) + getData(SecondMin);//gets the data from the two smallest values and combines them into one
		NewMin = createTree(new, FirstMin, SecondMin);//creates a new tree using the combined data and sets the two removed nodes as its children
		insert(NewMin);//inserts the new tree into the binary heap
	}

	for(i=0;i<257;i++)
	{
		if(leaves[i]!= NULL)
		{
			if(isprint(i))//checks if value has a corresponding printable ASCII character
			{
				printf("'%c': %d ",i, getData(leaves[i]));//prints ASCII character
				encoding(leaves[i]);//gets bit encoding
				printf("\n");
			}

			else//if not
			{
				printf("%03o: %d ",i, getData(leaves[i]));//prints the three digit octal value
				encoding(leaves[i]);//gets bit encoding
				printf("\n");
			}
		}
	}

	pack(argv[1], argv[2], leaves);
    destroyTree(heap[0]);//frees the tree that contains all the data
    return 0;
}

/*Inserts tree into the binary heap*/
void insert(struct tree *leaf)
{
    int HeapDepth = counter;//holds the current value of where the tree is placed
    int ParentDepth = ((HeapDepth-1)/2);//holds the value of where the parent of the current tree would be
    while(HeapDepth!=0 && getData(heap[ParentDepth])>getData(leaf))//while the tree is not at the root or bigger than its parent
    {
		heap[HeapDepth] = heap[ParentDepth];//saves the parent of the current tree value to the current position of the tree which frees the current tree's parent spot
		HeapDepth = ParentDepth;//transverses up the tree
		ParentDepth = ((HeapDepth-1)/2);//resets the values for the tree's parent and current spot
	}
	heap[HeapDepth]=leaf;//once the position of the tree is found, it is inserted
	counter++;
}

/*Removes the smallest value of the binary heap and reorganizes the binary to so that it stays in heap order*/
struct tree *delete(void)
{
    int i, child;
    i = 0;
    struct tree *min = heap[0];//saves the smallest tree to be returned
    struct tree *UpStart = heap[counter -1];//tree from the bottom of the binary heap that replaces the smallest node at the top of the binary heap

    /*while the left child is less than counter*/
    while((2*i +1) < counter)
    {
		child = 2*i + 1;//assign child to left child
		
        /*checks if the right child is less than the counter. And, checks if the left child is bigger than the right child becuase the smaller of the two children becomes the new top of the binary heap from its current depth*/
		if(2*i+2 < counter && getData(heap[2*i+1]) > getData(heap[2*i+2]))
		{
			child = 2*i +2;//assign child to right child
		}
        /*If the tree is bigger than its child*/
		if(getData(UpStart) > getData(heap[child]))
		{
			heap[i] = heap[child];//moves the child to its parent in the binary heap order, freeing the child spot
			i = child;//transverses down the binary to the tree's child spot
		}
		else//the tree is smaller than its child, spot found to insert the tree
		{
			break;
		}
    }

	heap[i] = UpStart;//sets the tree in the open spot
	counter--;
	return min;

}

/*Outputs 0's and 1's for bit encoding of ASCII characters and values.
 Recursive function from the leaves to root*/
void encoding(struct tree *leaves)
{
	struct tree *parent;
	parent = getParent(leaves);
	if(parent != NULL)//if root's parent is accessible
	{	
		if(getLeft(parent) == leaves)//checks if leaves is left child of parent
		{
			encoding(parent);
			printf("0");
			return;
		}
		else//else leaves is right child of parent
		{
			encoding(parent);
			printf("1");
			return;
		}
	}
	else//breaks when at root because parent is NULL
	{
		return;
	}
}
