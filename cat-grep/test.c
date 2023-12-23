#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Array {
    int* data;
    int size;
};

char** flags(int count, struct Array* select_arg, char* argv[]);
char** file_names(int count, struct Array* select_arg, char* argv[]);

int main(int argc, char* argv[]) {
    struct Array* select_arg = malloc(sizeof(struct Array));
    select_arg->data = NULL;
    select_arg->size = 0;

    char** flags_p = flags(argc, select_arg, argv);
    char** file_names_p = file_names(argc, select_arg, argv);

    // Освобождение памяти после использования
    free(select_arg->data);
    free(select_arg);
    for (int i = 0; flags_p[i] != NULL; i++) {
        free(flags_p[i]);
    }
    free(flags_p);
    for (int i = 0; file_names_p[i] != NULL; i++) {
        free(file_names_p[i]);
    }
    free(file_names_p);

    return 0;
}

char** flags(int count, struct Array* select_arg, char* argv[]) {
    char** token_arr = argv;
    char** flags = NULL;
    int count_flags = 0;
    int count_element = count;
    for (int i = 0; i < count_element; i++) {
        if (token_arr[i][0] == '-') {
            flags = realloc(flags, (count_flags + 2) * sizeof(char *));
            flags[count_flags] = malloc(strlen(token_arr[i]) + 1);
            strcpy(flags[count_flags], token_arr[i]);
            count_flags++;
            select_arg->data = realloc(select_arg->data, count_flags * sizeof(int));
            select_arg->data[count_flags - 1] = i;
            select_arg->size++;
            printf("%d\n", select_arg->data[count_flags - 1]);
        }
    }
    return flags;
}

char** file_names(int count, struct Array* select_arg, char* argv[]) {
    char** token_arr = argv;
    char** file_names = NULL;
    // int count_files = 0;
    // int count_element = count;
    // bool flag = true;
    // for (int i = 0; i < count_element; i++) {
    //     flag = true;
    //         // for (int j = 0; j < select_arg->size && select_arg->size>0; j++) {
    //         //     if (i == select_arg->data[j]) {
    //         //         flag = false;
    //         //         break;
    //         //     }
    //         // }

    //     if (flag) {
    //         file_names = realloc(file_names, (count_files + 2) * sizeof(char *));
    //         file_names[count_files] = malloc(strlen(token_arr[i]) + 1);
    //         strcpy(file_names[count_files], token_arr[i]);
    //         count_files++;
    //     }
    // }
    return file_names;
}



// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>
// struct Array{
//     int* data;
//     int size = 0;
// }typedef;

// char** flags(int count, int* select_arg, char* argv[]);
// char** file_names(int count, int* select_arg, char* argv[]);

// int main(int argc, char* argv[]) {
//     char ** flags_p = NULL;
//     char ** file_names_p = NULL;
//     Array* select_arg = NULL;
//     flags_p = flags (argc, select_arg, argv);
//     file_names_p = file_names (argc, select_arg, argv);

// }

// char** flags(int count, Array* select_arg, char* argv[]) {
//     char** token_arr = argv;
//     char** flags = NULL;
//     int count_flags = 0;
//     int count_element = count;
//     for (int i = 0; i < count_element; i++) {
//         if(token_arr[i][0]=='-'){
//             flags = (char **)realloc(flags, (count_flags+1)*sizeof(char *));
//             flags[count_flags] = malloc(strlen(token_arr[i]) + 1);
//             strcpy(flags[count_flags], token_arr[i]);
//             count_flags++;
//             select_arg.data = (int *)realloc(select_arg.data, count_flags*sizeof(int *));
//             select_arg.data[count_flags-1] = i;
//             select_arg.size++;
//             printf("%d", select_arg.data[count_flags-1]);
//         }
//     }
//     return flags;
// }


// char** file_names(int count, Array* select_arg, char* argv[]) {
//     char** token_arr = argv;
//     char** file_names = NULL;
//     int count_files = 0;
//     int count_element = count;
//     bool flag = 1;
//     for (int i = 0; i < count_element; i++) {
//         for (int j = 0;j < select_arg.size;j++)  {
//             if(i==select_arg.data[j]){
//                 flag = 0;
//             }
//         }
//         if(flag){
//             file_names = (char **)realloc(file_names, (count_files+1)*sizeof(char *));
//             file_names[count_files] = malloc(strlen(token_arr[i]) + 1);
//             strcpy(file_names[count_files], token_arr[i]);
//             count_files++;
//         }
//     }
//     return file_names;
// }