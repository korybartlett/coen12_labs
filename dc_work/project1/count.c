/*
 *Kory Bartlett
 *Atkinson 10:30
 *Project 1: Counting the Number of Words
 *Thursday 2:15
 *3 April 2014
 *
 *
 *Program to read words from a text file and count the number of words in the text file
 */
#include<stdio.h>
#include<stdlib.h>
#define MAX_WORD_LENGTH 30
int
main( int argc, char*argv[])//recieves arguements from comand line
{
	FILE *fp;
	int word_counter = 0;
	char buffer [MAX_WORD_LENGTH];

	if( argc != 2)//checks to make sure that comand line passes two arguements
	{
		printf("Insuffiecient number of arguments used\n");
		return 0;
	}

	fp = fopen(argv[1],"r");//opens the text file in the argv[1] slot and sets it to be read

	if(fp == NULL)//checks text file to make sure it has content
	{
		printf("File could not be opened\n");
		return 0;
	}

	while(fscanf(fp,"%s", buffer)!=EOF)//reads a string from text file into buffer. the function runs until it reaches the end of the file	
	{
		word_counter++;

	}
	
	printf("%d total words\n", word_counter);
	fclose(fp);
	return 1;
}
