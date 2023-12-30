#include <stdio.h>
#include <unistd.h>
#include  "Struct_cat.h"

int sort_argv_and_find_file_p(int argc,char * argv[]);
void switch_flags(char *character_1,char *character_2, FILE* file, int * count_n, int* count_b);
void work_with_file(char *file_name, int *count_n, int * count_b);
void b_realiz(char *character_1, char* character_2, int * count_b);
void n_realiz(char *character_1, char* character_2,int * count_n);
void s_realiz(char *character_1, char *character_2, FILE* file, int * count_n);
void t_realiz(char *character_1, char* character_2);
void  v_realiz(char *character_1, char* character_2);
void e_realiz(char *character_1, char* character_2);
void flags_use(FILE *file, int*count_n, int *count_b);

int main(int argc, char * argv[]){
    int ind;
    ind = sort_argv_and_find_file_p(argc, argv);
    int count_n=1;
    int count_b=1;
    for(int i=optind;i<argc;i++){
        work_with_file(argv[i], &count_n, &count_b);
    }

}

void flags_use(FILE *file, int*count_n, int *count_b){
        char character_1;
        char character_2 = '0';
        while ((character_1=fgetc(file))!= EOF){
            switch_flags(&character_1, &character_2, file, count_n, count_b);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
            if(character_1=='\t' && flags[4].availability==true){
            }else if ((character_1 < 32 || (character_1 > 126 && character_1<192)) && character_1!=9 && character_1!=10){
            }else{
                printf("%c", character_1);
            }
            character_2 = character_1;
        }
}

void work_with_file(char *file_name, int *count_n, int * count_b){
    FILE *file = fopen(file_name, "r");
    if(file == NULL){
        printf("File %s not open", file_name);
    }else{
        flags_use(file, count_n, count_b);
    }
}  

void switch_flags(char *character_1,char *character_2, FILE* file, int * count_n, int * count_b){
    for(int i=0;i<5;i++){
        if (flags[i].availability==true){
            char opt=flags[i].flag;
            switch (opt) {
                case 's':
                    s_realiz(character_1, character_2, file, count_n);
                    break;
                case 'n':
                    n_realiz(character_1,character_2,count_n);
                    break;
                case 'b':
                    b_realiz(character_1,character_2, count_b);
                    break;
                case 'e':
                    e_realiz(character_1,character_2);
                    break;
                case 't':
                    t_realiz(character_1,character_2);
                    break;
                default:
                    break;
            }
        }   
        
    }

}

int sort_argv_and_find_file_p(int argc,char * argv[]){
    int opt;
    while ((opt=getopt_long(argc, argv,"beEnstv", long_options, NULL))!=-1){
        switch (opt){     
        case 'b':
            flags[2].availability=true;
            break;
        case 'e':
            flags[3].availability=true;
            flags[5].availability=true;
            break;
        case 'E':
            flags[3].availability=true;
            break;
        case 'n':
            flags[1].availability=true;
            break;
        case 's':
            flags[0].availability=true;
            break;
        case 'T':
            flags[4].availability=true;
            break; 
        case 't':
            flags[4].availability=true;
            flags[5].availability=true;
        case 'v':
            flags[5].availability=true;
            break;
        case '?':
            fprintf (stderr, "Unknown flag\n");
            exit(1);
            break;
        default:
            break;
        }
    }   
    if(flags[2].availability==true){
        flags[1].availability=false;
    }

    return optind;
}


void e_realiz(char *character_1, char* character_2){
    if(* character_1== '\n'){
        printf("%c",'$');
    }
}
void b_realiz(char *character_1, char* character_2, int * count_b){
    if(*count_b == 1 || (*character_2=='\n' && *character_1!='\n')){
        printf("%6d  ", *count_b);
        *count_b+=1;
    }
}
void n_realiz(char *character_1, char* character_2, int * count_n){
    if(*count_n == 1 || *character_2=='\n'){
        printf("%6d  ", *count_n);
        *count_n+=1;
    }
}
void s_realiz(char *character_1, char* character_2, FILE *file, int * count_n){
    if(*character_1=='\n' && *character_2=='\n'){
        while (*character_1 == '\n'){
            *character_1=fgetc(file);
            true;
        }if(flags[1].availability==true){
            printf("%6d  \n", *count_n);
            *count_n+=1;
        }else if(flags[3].availability==true){
            printf("$\n");
        }else{
            printf("\n");
        }
    }
}
void t_realiz(char *character_1, char* character_2){
    if(* character_1== '\t'){
        character_1=(char)0;
        printf("^I");
    }
}
void  v_realiz(char *character_1, char* character_2){
    if((*character_1 < 32 || (*character_1 > 126 && *character_1<192)) && *character_1!=9 && *character_1!=10){
        printf("^");
    }
}