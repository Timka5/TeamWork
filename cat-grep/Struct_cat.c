#include  "Struct_cat.h"
#include "newstring.h"

user_comand parsing_user_comand(char *full_string){
    user_comand st_u_c;

    int substring_lenth;
    
    char *u_comand = (char *)malloc(count_symbols_substring * sizeof(char *))
}

int comand(char* full_string) {
    char** token_arr = cut_str_token(full_string);
    int count_element = sizeof(token_arr) / sizeof(token_arr[0]);
    int count_comand = 0;
    for (int i = 0; i < count_element; i++) {
        if (strcmp(token_arr[i], "cat") == 0) {
            count_comand++;
        }
    }
    if (count_comand == 1) {

        return 1;
    }
    else {
        return 0;
    }

}
char* flags(char* full_string) {
    //тут будет происходить парсинг токенов на флаги, пока думаю, что это можно слелать путем проверки строки:
    //if (пока хз, надо подумать)
}
char* file_names(char* full_string) {


}