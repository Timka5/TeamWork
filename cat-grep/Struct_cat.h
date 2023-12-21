#ifndef STRUCT_CAT
#define STRUCT_CAT

typedef struct {
    char *comand;
    char **flags;
    char **files_name
}user_comand;


void parsing_user_comand(char *full_string);
// remake for default constructor, argument - string user entered, in this constructor 
// comand,flags and files_name must be initialized with its own data, simply put,
// it is parsing a string


#endif