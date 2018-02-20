/*
 ============================================================================
 Name        : loremIpsum.c
 Author      : Chad Mello
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_WORD_LEN 100
#define MAX_LINE_LEN 1000

#define ipsumFile "Lorem ipsum.txt"
#define ipsumCopy "Lorem ipsum_COPY.txt"

void pause(void);
int wordCount(FILE *fp);
int charCount(FILE *fp);
int sendContentTo(FILE *fp, FILE *out);
int getWordAt(FILE *fp, int pos, char *word);
int appendToFile (char *fileName, char*newText);

int main(void)
{
	FILE *fp;
	FILE *fpCopy;

	// open Lorem ipsum.txt for read.
	if ((fp = fopen(ipsumFile, "r")) == NULL)
	{
		fprintf(stdout,"Can't open %s file.\n",ipsumFile);
		exit(EXIT_FAILURE);
	}

	if ((fpCopy = fopen(ipsumCopy, "w+")) == NULL)
	{
		fprintf(stdout, "Can't open %s file.\n", ipsumCopy);
		exit(EXIT_FAILURE);
	}

	//PROBLEM 1: SIMPLE DATA TRANSFER

	sendContentTo(fp, fpCopy);
	
	if (fclose(fpCopy) != 0)
		fprintf(stderr, "Error closing file\n");

	//END PROBLEM 1


	//PROBLEM 4: FILE APPEND

	appendToFile(ipsumCopy, "\nUt enim ad minima veniam, quis nostrum exercitationem ullam corporis\nsuscipit laboriosam, nisi ut aliquid ex ea commodi consequatur?\n");

	//END PROBLEM 4


	if ((fpCopy = fopen(ipsumCopy, "r")) == NULL)
	{
		fprintf(stdout, "Can't open %s file.\n", ipsumCopy);
		exit(EXIT_FAILURE);
	}


	// print out and count all words in Lorem ipsum.txt

	//5.1
	int numOfWords = wordCount(fp); // note that I'm not using the value in numOfWords here

	//5.2
	int copyNumOfWords = wordCount(fpCopy);
	pause();

	//5.3
	char wordLookup[MAX_WORD_LEN];
	int lookupPosition = 233;
	// get the n th word from file
	int wordPosition = getWordAt(fp, lookupPosition, wordLookup);
	if (wordPosition != 0) {
		// indicate we found the word, and then print the word to console
		printf("Word at position %d: %s\n", wordPosition, wordLookup);
	
	}
	else {
		// indicate that we could not get any word at that location
		+printf("Unable to find word at position %d\n", lookupPosition);
		
	}

	// print out and count all lines in Lorem ipsum.txt
	//5.4
	int numOfLines = sendContentTo(fp, stdout); // note that I'm not using the value in numOfLines here
	pause();

	//#5.5
	int numOfChars = charCount(fp);
	pause();

	//#5.6
	char copyWordLookup[MAX_WORD_LEN];
	lookupPosition = 500;
	//find the word in file at the given position
	wordPosition = getWordAt(fpCopy, lookupPosition, copyWordLookup);
	if (wordPosition != 0) {
		// display word and position
		printf("Word at position %d: %s\n", wordPosition, copyWordLookup);
	
	}
	else {
		//Error, no word found
		printf("Unable to find word at position %d\n", lookupPosition);
		
	}

	//#5.7
	int copyNumOfLines = sendContentTo(fp, stdout);
	pause();
	
	




	//PROBLEM 5 QUESTIONS
	printf("1) How many words are reported to be in lorem ipsum.txt?    %d words.\n\n", numOfWords);
	printf("2) How many words are reported to be in lorem ipsum.txt_COPY?   %d words\n\n", copyNumOfWords);
	printf("3) What is the 233rd word in lorem ipsum.txt?   \"%s\"\n\n", wordLookup);
	printf("4) How many lines are reported to be in lorem ipsum.txt?   %d lines.\n\n", numOfLines);
	printf("5) How many characters are reported to be in lorem ipsum.txt?   %d characters.\n\n", numOfChars);
	printf("6) What is the 500th word in lorem ipsum_COPY.txt?   \"%s\"\n\n", copyWordLookup);
	printf("7) How many lines are reported to be in lorem ipsum_COPY.txt?   %d lines.\n\n", copyNumOfLines);
	pause();














	// ** Starting here **
	// Use the sendContentTo function to copy the
	// contents of Lorem ipsum.txt into a new file (ipsumCopy),
	// instead of the console/screen.

	//NOTE:  DO NOT MODIFY the sendContentTo function in any way; it's perfect the way it is..
	//       use it AS-IS.

	//So, how would you do that?



	// Now that we are finished with the file,
	// close Lorem ipsum.txt
	//(close any other files you might have open at this point as well)
	if (fclose(fp) != 0)
		fprintf(stderr,"Error closing file\n");
	return 0;
}

void pause() {
	printf("\nPress any key to continue... \n\n");
	getch();
}

// Read content from file one line (crlf) at a time.
// Send content to output one line at a time.
// Returns number of lines processed.
int sendContentTo(FILE *in, FILE *out)
{
	fprintf(stdout, "Performing file copy...\n\n");

	//start at the beginning of the file
	rewind(in);

	// array to hold one line of text up to 1000 characters
	char line[MAX_LINE_LEN];

	// Start out assuming input
	// file contains ZERO lines.
	int lineCount=0;

	// read one line at a time from our input file
	while (fgets(line, MAX_LINE_LEN, in) !=NULL)
	{
		//send line we just read to output.
		fprintf(out, "%s", line);

		//count the lines
		lineCount++;
	}

	fprintf(stdout, "\nFinished line count.\n");
	fprintf(stdout, "Count is: %d.\n\n",lineCount);

	// Return how many text lines
	// we've processed from input file.
	return lineCount;
}

// Read content from file one character at a time.
// Returns number of total characters read from the file.
int charCount(FILE *fp)
{
	fprintf(stdout, "Performing char count...\n\n");
	
	int charCount = 0;

	//PROBLEM 2: charCount()

	char character;
	rewind(fp);

	while (fscanf(fp, "%c", &character) == 1) {
		printf("%c\n", character);
		charCount++;
	}
	
	//END PROBLEM 2

	fprintf(stdout, "\nCharacter count Completed. \nTotal Characters: %d", charCount);
	return charCount;
}


// Read content from file one word at a time.
// Returns number of total words read from the file.
int wordCount(FILE *fpcopy)
{
	fprintf(stdout, "Performing word count...\n\n");

	rewind(fpcopy);

	char word[MAX_WORD_LEN];
	int wordCount=0;

	while (fscanf(fpcopy,"%s",word) == 1)
	{
		// Send entire word string
		// we just read to console
		puts(word);

		//count the word
		wordCount++;
	}

	fprintf(stdout, "\nFinished word count.\n");
	fprintf(stdout, "Count is: %d.\n\n",wordCount);
	return wordCount;
}


int appendToFile (char *fileName, char *newText)
{
	fprintf(stdout, "Performing file append...\n\n");
	fprintf(stdout, "Appending: %s\n", newText);
	
	//PROBPLEM 4: FILE APPEND
	FILE * fp;
	
		// open file in append mode
	if ((fp = fopen(fileName, "a")) == NULL)
	{
		fprintf(stdout, "Can't open %s file.\n", fileName);
		exit(EXIT_FAILURE);
	}
	
		// Append newText
	fprintf(fp, "%s", newText);
	
	return 0;

}

int getWordAt(FILE *fp, int pos, char *word)
{

	fprintf(stdout, "Getting word at position %d...\n\n", pos);
	char resultWord[MAX_WORD_LEN];
	
	
	//PROBLEM 3: FIND THE NTH WORD:
	rewind(fp);
	for (int k = 0; k < pos; k++) {
			// if not found, return -1
		if (!(fscanf(fp, "%s", word) == 1 && word[0] != EOF)) {
			fprintf(stdout, "\nFinished finding word - NOT FOUND.\n");
			return -1;
			
		}
		
	}
	
	strcpy(resultWord, word);
	//END PROBLEM 3

	fprintf(stdout, "\nFinished finding word - NOT FOUND.\n");
	return pos;
}