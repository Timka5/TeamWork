#include  "Struct_cat.h"
#include "newstring.h"

user_comand parsing_user_comand(char *argv){
    user_comand st_u_c;

    int substring_lenth;
    
    char *u_comand = (char *)malloc(count_symbols_substring * sizeof(char *))
}

// int comand(int* select_arg,char* argv) {
//     char** token_arr = argv;
//     int count_element = sizeof(token_arr) / sizeof(token_arr[0]);
//     int count_comand = 0;
//     for (int i = 0; i < count_element; i++) {
//         if (strcmp(token_arr[i], "s-21cat") == 0) {
//             count_comand++;
//         }
//     }
//     free(token_arr);
//     if (count_comand == 1) {

//         return 1;
//     }
//     else {
//         return 0;
//     }

// }

char** flags(int* select_arg, char* argv[]) {
    char** token_arr = argv;
    char** flags = NULL;
    int count_flags = 0;
    int count_element = sizeof(token_arr) / sizeof(token_arr[0]);
    for (int i = 0; i < count_element; i++) {
        if(token_arr[i][0]=='-'){
            flags = (char **)realloc(flags, (count_flags+1)*sizeof(char *));
            flags[count_flags] = malloc(strlen(token_arr[i]) + 1);
            strcpy(flags[count_flags], token_arr[i]);
            count_flags++;
            select_arg = (int *)realloc(select_arg(), count_flags*sizeof(int *));
            select_arg[count_flags-1] = i;
        }
    }
    return flags;
}


char** file_names(int* select_arg, char* argv[]) {
    char** token_arr = argv;
    char** file_names = NULL;
    int count_files = 0;
    int count_element = sizeof(select_arg) / sizeof(select_arg[0]);
    int count_ind = sizeof(select_arg) / sizeof(select_arg[0]);
    bool flag = 1;
    for (int i = 0; i < count_element; i++) {
        for (int j = 0;j < count_ind;j++)  {
            if(i==select_arg[j]){
                flag = 0;
            }
        }
        if(flag){
            file_names = (char **)realloc(file_names, (count_files+1)*sizeof(char *));
            file_names[count_files] = malloc(strlen(token_arr[i]) + 1);
            strcpy(file_names[count_files], token_arr[i]);
            count_files++;
        }
    }
    return flags;
}