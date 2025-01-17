#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
//add additional prototypes here


int setup_buff(char *buff, char *user_str, int len){
    //TODO: #4:  Implement the setup buff as per the directions
    char *input = user_str;		// Pointer to traverse input string
    char *output = buff;		// Pointer to traverse buffer
    int input_length = 0;		// Tracks the length of the input
    int output_length = 0;		// Tracks the length of the output
    int whitespace = 0;			// Tracks any extra whitespace

    // Trim leading whitespace
    while (*input == ' ' || *input == '\t') {
    	input++;
    }


	// Navigates through input string
    while (*input != '\0') {
    	// Check for whitespace
    	if (*input == ' ' || *input == '\t') {
    		// Add one space for consecutive spaces
    		if (!whitespace) { 
    			*output++ = ' ';
    			output_length++;
    			whitespace = 1;
    		}
    	}
    	else {
    		// Copy non-whitespace to the buffer
    		*output++ = *input;
    		output_length++;
    		whitespace = 0;
    	}

    	input++;
		// Error if input is larger than the buffer
    	if (input_length > len + 1) {
    		return -1;
    	}
    }
	// Trim trailing whitespace
	if (output > buff && *(output - 1) == ' ') {
		output--;
		output_length--;
	}

	// Fill the rest of the buffer with '.'
	while (output_length < len + 1) {
		*output++ = '.';
		output_length++;
	}
	// Get length of initial input without any extra whitespace
	while (*buff != '.'){
		input_length++;
		buff++;
	}

	return input_length;
}

void print_buff(char *buff, int len){
    printf("Buffer:  [");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    putchar(']');
    putchar('\n');
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}

int count_words(char *buff, int len, int str_len){
    //YOU MUST IMPLEMENT
    int count = 0;		// Variable to track count of words
    int word = 0;		// Varianle to track if currently in a word
    for (int i = 0; i < str_len; i++) {
    	if (buff[i] != ' ') {
    		if (!word){
    			count++;
    			word = 1;
    		}
    	}
    	else {
    		word = 0;
    	}
    }

    return count;
}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

void reverse_buffer(char *buff,int str_len, int len) {
	char *reversed = (char *)malloc((len + 1) * sizeof(char));
	int rev_len = 0;
	for (int i = 0; i < str_len; i++) {
		reversed[i] = buff[str_len - 1 - i];
		rev_len++;
	}
	
	while (rev_len < len) {
		reversed[rev_len] = '.';
		rev_len++;
	}
	
	for (int i = 0; i < len; i++) {
		buff[i] = reversed[i];
	}
	free(reversed);

}

void word_print(char *buff, int str_len) {
	int start = 0;
	int len = 0;
	int count = 0;
	printf("Word Print\n");
	printf("----------\n");

	for (int i = 0; i <= str_len; i++){
		if (i == str_len || buff[i] == ' ') {
			count++;
			printf("%d. ", count);

			for (int j = 0; j < len; j++) {
				printf("%c", buff[start + j]);
			}
			
			printf("(%d)\n", len);

			len = 0;

		}
		else {
			if (len == 0) {
				start = i;
			}
			len++;
		}
	}
}

int main(int argc, char *argv[]){
    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
	/*
		This code will always check if there are two arguments before it checks if argv[1]
		exists. Therefore if argv[1] doesn't exist the code will immediately exit and show
		usage. Otherwise the program will run with argv[1] as neccessary.
	*/
    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
    /*
		This if statement's purpose to make sure that when the program is run
		it is rn with no less than 3 arguments. If it is ran with less than 3
		arguments then a usage page is diplayed.

    */
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }
    input_string = argv[2]; //capture the user input string
   //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    // CODE GOES HERE FOR #3
	buff = (char *)malloc(BUFFER_SZ * sizeof(char));
	if (buff == NULL) {
		printf("Error allocating memory for buffer.");
		exit(99);
	}

    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options

        case 'r':
			reverse_buffer(buff,user_str_len, BUFFER_SZ);
			break;
        case 'w':
			word_print(buff, user_str_len);        	
			printf("\n");
			rc = count_words(buff, BUFFER_SZ, user_str_len);
			printf("Number of words returned: %d\n", rc);
			break;
		case 'x':
			printf("Not Implemented!\n");
			exit(0);

        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    print_buff(buff,BUFFER_SZ);
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          PLACE YOUR ANSWER HERE
/*
			Providing both the buffer and it's length is a good practice
			due to the flexibility it adds to the code. If the code ever
			needed to modify the buffer size then it wouldn't require recoding
			of hard coded buffer size values. Furthermore if we ever wanted
			to reuse this function in a similar program this makes the process
			much easier.

*/
