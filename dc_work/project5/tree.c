/*
 Kory Bartlett
 Dr. Atkinson
 COEN 12 9:15
 Project 5
 
 File Descprition: Creates functions that are to be used by various main files involving tree sort. This file deals with the creation, destruction, and the setting of parent, right child, and left child pointers. As well as functions that can access the data and pointers of a created tree.
 */
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "tree.h"

void detach(struct tree *branch);

/*The structure for type tree to be used in the project*/
struct tree
{
	int data;
	struct tree *left, *right, *parent;
};

/*Function called to create a root for the start of a tree or to build up a tree when passed in children
 *Big O(1)*/
struct tree *createTree(int data, struct tree *left, struct tree *right)
{
	struct tree *root;
	root = malloc(sizeof(struct tree));
	assert(root!=NULL);
    /*reassigns the root's pointers*/
	root->data = data;
	root->right = right;
	root->left = left;
	root->parent = NULL;
	
    /*checks if root points to a child*/
	if(root->left != NULL)
	{
		detach(root->left);//severs connection to parent
		left->parent = root;//reassigns the newly freed child to the parent
	}
    
    /*same as left but for the right child*/
	if(root->right != NULL)
	{
		detach(root->right);
		right->parent = root;
	}

	return root;
}

/*Frees the root and its children created via post-order traversal
 *Big  O(n)*/
void destroyTree(struct tree *root)
{
	if (root != NULL)
	{
		destroyTree(root->left);
		destroyTree(root->right);
		free(root);
	}
	return;
}

/*outputs the data that is inside the current root
 *Big O(1)*/
int getData(struct tree *root)
{
	assert(root!=NULL);
	return root->data;
}

/*Returns the left child of a node
 *Big O(1)*/
struct tree *getLeft(struct tree *root)
{
	assert(root!=NULL);
	return root->left;
}

/*Returns the right child of a node
 *Big O(1)*/
struct tree *getRight(struct tree *root)
{
	assert(root!=NULL);
	return root->right;
}

/*Returns the parent of a node
 *Big O(1)*/
struct tree *getParent(struct tree *root)
{
	assert(root!=NULL);
	return root->parent; 
}

/*Sets the left child of the root
 *Big O(1)*/
void setLeft(struct tree *root, struct tree *left)
{
	assert(root != NULL && left != NULL);
	if(root->left!=NULL)//checks if root's left pointer needs to be changed
	{
		root->left->parent = NULL;//Sets the original root's left child's parent pointer to NULL
	}
    
    root->left = left;//sets the passed in arguement "left" as the left child of the root
    
    if(left!=NULL)
	{
        detach(left);//severs the pointer to the parent
        left->parent = root;//reassigns the left's parent to the root
	}
}

/*Sets the right child of the root
 *Big O(1)*/
void setRight(struct tree *root, struct tree *right)
{
	assert(root != NULL && right != NULL);
	if(root->right!=NULL)//checks if root's rights pointer needs to be changed
	{	
		root->right->parent = NULL;//sets the original root's right child's parent pointer to NULL
	}
    
	root->right = right;//sets the passed in arguement "right" as the right child of the root
	
    if(right!=NULL)
	{
		detach(right);//severs the pointer to the parent
		right->parent=root;//reassigns the right's parent to the root
	}
}

/*The function used to sever connections amongst children and parents
 *Big O(1)*/
void detach(struct tree *root)
{
	assert(root!=NULL);
	if(root->parent == NULL)//base case if the node does not have a parent
	{
		return;
	}
	
	if(root->parent->left!=NULL)//checks that the parent pointer exists
	{
		root->parent->left = NULL;//sets the node's parent pointer that was to the left child to NULL
	}

	if(root->parent->right!= NULL)//checks that the parent pointer exists
	{
		root->parent->right = NULL;//sets the node's parent pointer that was to the right child to NULL
	}
}
