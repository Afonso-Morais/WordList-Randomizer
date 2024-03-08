/*
* SPDX-License-Identifier: ISC
*
* Copyright (c) 2024 Afonso L. Morais <moraisafonso@protonmail.com>
*
* Permission to use, copy, modify, and distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*==== WL-Random.c ======================================	

	This lets you read a file (txt recomended) and get
	each line into a array that will randomly select a
	line and display it for the user. Commenting in the
	files is possible with the '//' expression.
	
	Date: 28-02-2024
	Author: Afonso Morais
=========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include "WL-Random.h"

// Variables
DIR *currentDir;				// Current working directory
const char *dir_path = ".";			// Path of the directory

char currentFile[100] = "";			// Current wordlist file
FILE *file;					// Actual file

char line[100];					// Line of the wordlist
char words[5000][100];				// Max word count(5000) and max length(100)
int wordCount = 0; 				// Amount of words


int main(int argc, char *argv[]) {

	srand(time(NULL));				// Seed the random number with the current time				
    
	system(CLEAR);					// Clear screen
	
    if(argc != 1){
        printf("Usage: %s\n", argv[0]);
        return 1;
    }
    
    currentDir = opendir(dir_path);             	// Open current directory
    
    // Check if directory opened successfully
    if (currentDir == NULL) {
        perror("Unable to open directory");
        return 1;
    }
   
    char *programName = strrchr(argv[0], '/');		// Extract the program name from the path
    if (programName != NULL) { programName++; } 	// Move past the '/'
    else { programName = argv[0]; }			// If no '/', use the whole string

    
    drawFiles(programName);				// Start listing files from the current directory

	openFile();	
	getRandomWord();				// Print random word from word list for user
	
    closedir(currentDir); 				// Close the directory

    return 0;
}

void drawFiles(const char *programName) {
    struct dirent *entry;

	printf("*-- CURRENT WORKING DIRECTORY\n|\n");
	
    // Iterate through each entry in the directory
    while ((entry = readdir(currentDir)) != NULL) {
        // Ignore "." and ".." directories and the program's own file
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, programName) == 0) {
            continue;
        }
		
        printf("|- %s\n", entry->d_name);		// Print the name of the file or directory
    }

    printf("|\n*-- END OF CURRENT DIRECTORY\n");
}

void openFile(){
	

	// Read file and loop case it doesn't exist in the directory
	do{
		printf("\n\nWhat file do you want as your wordlist?\n> ");
		scanf("%s", currentFile);

		//Open file
		file = fopen(currentFile, "r");
		if(file == NULL){								// If is NULL (doesn't exist) give error message
			perror("Error Opening Wordlist");
			printf("Make sure the file '%s' exists!\n", currentFile);
		}
	
	}while(file == NULL);									// If is NULL (doesn't exist) loop until user types existing file

	// Break lines and ignore comments
	while (fgets(line, sizeof(line), file) != NULL) {
		

		if (strncmp(line, "//", 2) == 0) {						// CHECK IF THE LINE IS COMMENTED WITH '//'
            continue; 										// IGNORE/CONTINUE
        }	

        char *commentPtr = strstr(line, "//");		
        if (commentPtr != NULL) {
            *commentPtr = '\0'; 								// Null-terminate the line before the comment
		}
		
		size_t length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {						// Remove the \n (breaks) in each line
            line[length - 1] = '\0';
        }

		strcpy(words[wordCount], line);							// Copy the line to the words array
		wordCount ++; 									// Increment the word counter by 1
	}

	fclose(file);										// Close file not needed anymore
}

void getRandomWord(){
	
	waitForInput();

	while(0 < 1){		
		int randomIndex = rand() % wordCount;						// Get random Number
		printf("\nRANDOM WORD/LINE IS:\n%s", words[randomIndex]);			// Output random number line
		waitForInput();									// Wait for user to press ENTER
	}
}

void waitForInput(){
	int c;
	printf("\n");										// Break line
	while ((c = getchar()) != '\n' && c != EOF);						// Wait for user input
	
	clearInputBuffer();
}
