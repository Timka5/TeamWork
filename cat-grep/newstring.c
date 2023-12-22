#include "newstring.h"

char** cut_str_token(char* full_string)
{
	char* copy_full_string = (char*)malloc(strlen(full_string));
	strcpy(copy_full_string, full_string);
	
	char** token_arr = NULL;
	const char delimiters[] = " ";
	char* token = strtok(copy_full_string, delimiters);
	int i = 0;
	
	while (token !=NULL) {
		token_arr = (char**)realloc(token_arr, (i + 1) * sizeof(char*));
		token_arr[i] = (char*)malloc(strlen(token) + 1);
		strcpy(token_arr[i], token);
		i++;
	}
	free(copy_full_string);
	
	return token_arr;
}
