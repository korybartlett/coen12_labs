/*
 *File: set.h
 *
 *Description: This file contains the public function and type declarations for a set abstract type for strings. A set is an unordered collection of distinct elements. 
 */
#ifndef SET_H
#define SET_H

typedef struct set SET;
SET *createSet (int maxElts);
void destroySet(SET *sp);
int numElements(SET *sp);
bool hasElement(SET *sp, char *elt);
bool addElement(SET *sp, char *elts);
bool removeElement(SET *sp, char *elt);
#endif
