/* Author: Collin Smith
 * Date: 5/26/2021
 *
 * Description: This program reads input from either keyboard, file, or redirected file. 
 * Takes each line and stores it as a string in 2d array. Then calculates value of each string
 * by adding ascii value of first two characters together.  Builds binary tree based on this value.
 * First string is root, if next node is less in value it is inserted left, if node is
 * greater in value it goes right.
 *
 * Duplicates are allowed only once, they are stored within a node with the same value.
 * After that, duplicates are not recorded.
 *
 * Tree level is represented by spaces, furthest to the left is root.  Nodes which have 
 * duplicates are represented with a dash.  Prints preorder, postorder, and inorder 
 * traversals.  Also saves these outputs to a log file.
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include "node.h"
#include "tree.h"


void print_usage();
static char *read_stdin();
static char *load_file(char const * path);


int main (int argc, char* argv[]) {

	

	// Check number of arguments
	if (argc > 2) {
		printf("Too many arguments\n");
		print_usage();
		exit(0);
	}	
	else if (argc == 2) {
		// File was passed, check if it exists
		if (access(argv[1], F_OK) == 0) {
			printf("File exists, continuing...\n");
		}
		else {
			printf("File doesn't exist, exiting...\n");
			exit(0);
		}
		

		char *input = load_file(argv[1]);
		char *delim = " \n ";			// Used for splitting string
		char *input_copy = strdup(input); 
		char *input_copy2 = strdup(input);


		printf("Getting input from file...\n");


		// Use strtok to count how many strings there are
		// Multiple copies needed due to strtok altering original string
		char *split_string = strtok(input, delim);
		int rows = 0;


		while (split_string != NULL) {

			printf("%s\n", split_string);
			split_string = strtok(NULL, delim);
			rows++;
		}

		
		// Use strtok to get length of strings.
		// Store string length in string_length[]
		int string_length[rows];		
		int j = 0;
		char *split_string2 = strtok(input_copy, delim);


		while (split_string2 != NULL) {
			if (j == (rows - 1)){
				break;
			}	
			
			string_length[j] = strlen(split_string2);
			split_string2 = strtok(NULL, delim);
			j++;	
		}	

		
		// One string leftover from previous loop
		string_length[j] = strlen(split_string2);


		// Create 2d  array to store strings.
		int columns = 32;
		char string_storage[rows][columns - 1];
		int length_index = 0;
		char *split_string3 = strtok(input_copy2, delim);
		
		j = 0;	
		while (split_string3 != NULL) {
			if (j == (rows - 1)) {
				break;
			}

			int i = 0;
			for (i = 0; i < string_length[length_index]; i++) {
				string_storage[j][i] = split_string3[i];	
			}

			length_index++;
			split_string3 = strtok(NULL, delim);
			j++;			
		}
		
		
		// One string leftover from previous loop
		int i = 0;
		for (i = 0; i < string_length[length_index]; i++) {
			string_storage[j][i] = split_string3[i];
		} 


		//Build tree and print traversals
		buildTree(string_storage, string_length, rows);

		
		free(input);
		exit(0);
	}
	else if (argc == 1) {

		printf("Getting input from stdin...\n");
		printf("Simulate EOF by entering 0 \n");


		char *input = read_stdin(); 	 // Read from STDIN
		char *delim = " \n ";		// For splitting string
		char *input_copy = strdup(input); 
		char *input_copy2 = strdup(input);


		// Use strtok just to count how many strings there are
		// Multiple copies due to strtok altering original string
		char *split_string = strtok(input, delim);
		int rows = 0;


		while (split_string != NULL) {

			printf("%s\n", split_string);
			split_string = strtok(NULL, delim);
			rows++;
		}

		
		// Use strtok to get length of strings.
		int string_length[rows];		
		int j = 0;
		char *split_string2 = strtok(input_copy, delim);


		while (split_string2 != NULL) {
			if (j == (rows - 1)){
				break;
			}	
			
			string_length[j] = strlen(split_string2);
			split_string2 = strtok(NULL, delim);
			j++;	
		}	

		
		// One string leftover from previous loop
		string_length[j] = strlen(split_string2);


		// Create 2d  array and store strings.
		int columns = 31;
		char string_storage[rows][columns];
		int length_index = 0;
		char *split_string3 = strtok(input_copy2, delim);

		
		j = 0;	
		while (split_string3 != NULL) {
			if (j == (rows - 1)) {
				break;
			}

			int i = 0;
			for (i = 0; i < string_length[length_index]; i++) {
				string_storage[j][i] = split_string3[i];	
			}

			length_index++;
			split_string3 = strtok(NULL, delim);
			j++;			
		}
		
		
		// One string leftover from previous loop
		int i = 0;
		for (i = 0; i < string_length[length_index]; i++) {
			string_storage[j][i] = split_string3[i];
		} 


		//Build tree and print traversals
		buildTree(string_storage, string_length, rows);

		
		free(input);
		exit(0);
	}
	else {
		// Shouldn't happen,  0 args
		printf("Error: 0 args passed\n");
		print_usage();
		exit(0);
	}


	return 0;
}


void print_usage(){

	printf("---Usage---\n");
	printf("Enter './main' to test keyboard\n");
	printf("Enter './main < FILENAME' to test keyboard input from some file\n");
	printf("Enter './main FILENAME' to read from a file\n");

}


// Read from stdin and store in buffer
static char *read_stdin(){


	size_t capacity = 4096, offset = 0;  // Set size of buffer and offset.
	char *buffer = malloc(capacity * sizeof (char));
	int c; 

	// Read until EOF
	while ((c = fgetc(stdin)) != '0' && !feof(stdin)) {
						
		buffer[offset] = c;	
		if (++offset == capacity) {
			buffer = realloc(buffer, (capacity *= 2) * sizeof (char));
		}
			
	}

	// Trim and pad
	buffer = realloc(buffer, (offset + 1) * sizeof (char));
	buffer[offset] = '\0';

	return buffer;
}


// Read file into buffer
static char *load_file(char const* path) {

	char *buffer = 0;
    	long length;
    	FILE *f = fopen (path, "rb"); //was "rb"


    	if(f) {
		fseek (f, 0, SEEK_END);
      		length = ftell (f);
      		fseek (f, 0, SEEK_SET);
      		buffer = (char*)malloc((length + 1)*sizeof(char));
      		if (buffer) {
        		fread(buffer, sizeof(char), length, f);
      		}
      		fclose(f);
	}


	buffer[length] = '\0';

    
	return buffer;
}
