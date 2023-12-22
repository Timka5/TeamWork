#ifndef STRUCT_CAT
#define STRUCT_CAT
#include <string.h>


typedef struct {
    char *comand;
    char **flags;
    char **files_name
}user_comand;


user_comand parsing_user_comand(char *full_string);


int comand(char* full_string);
//эта функция проверяет вводимую пользователем строку на наличие команды cat, если такая есть, она вернет 1, в противном случае 0 
//также учитвается случай множественного cat, в таком случае функция вернет 0
char* flags(char* full_string);

char* file_names(char* full_string);

chek_correction_incription();
//данная функция будет проверять коррекстность ввода пользователя, то ли он вообще ввел
//реализация будет через сравнение изначального количества токенов, на которые бьется строка
//с суммой всех токенов (флагов имени и тд) на которые в конечном итоге будет распаршена строка



// remake for default constructor, argument - string user entered, in this constructor 
// comand,flags and files_name must be initialized with its own data, simply put,
// it is parsing a string


#endif