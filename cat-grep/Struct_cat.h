#ifndef STRUCT_CAT
#define STRUCT_CAT
#include <string.h>


typedef struct {
    // char *comand;
    char **flags;
    char **files_name;
}user_comand;


user_comand parsing_user_comand(char *full_string);


// int comand(char* full_string);
// //��� ������� ��������� �������� ������������� ������ �� ������� ������� cat, ���� ����� ����, ��� ������ 1, � ��������� ������ 0 
// //����� ���������� ������ �������������� cat, � ����� ������ ������� ������ 0


char** flags(char* full_string);

char** file_names(char* full_string);

chek_correction_incription();
//������ ������� ����� ��������� ������������� ����� ������������, �� �� �� ������ ����
//���������� ����� ����� ��������� ������������ ���������� �������, �� ������� ������ ������
//� ������ ���� ������� (������ ����� � ��) �� ������� � �������� ����� ����� ���������� ������



// remake for default constructor, argument - string user entered, in this constructor 
// comand,flags and files_name must be initialized with its own data, simply put,
// it is parsing a string


#endif