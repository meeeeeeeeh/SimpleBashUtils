#include <stdio.h>
#include <unistd.h>
#include <regex.h>
#include <string.h>

//optind инициализируется как 1. (!!)
//Если getopt возвращает -1 (флагов больше нет) 
//optind становится индексом первого элемента коммандной строки который не является опцией

//void print_lines(char * fp, int files, char flag, char* templ);

typedef struct flag{
    int e;
    char template[300];
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    char file[300]; 
    int o;
    int is_flag;
} flag;

void print_lines(char * fp, int files, flag f);

int main(int argc, char* argv[]) {
    flag f = {}; //делает всем значениям структуры значение 0
    f.template[0] = '\0';
    f.file[0] = '\0';
    int lots_files = 0;
    int opt = 0;

    while((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
        f.is_flag = 1; //какой-то флаг есть
        if (opt == 'e') {
            f.e = 1;  
            strcat(f.template, optarg); // "str1|str2|1231|"
            strcat(f.template, "|");
        }
        if (opt == 'f') {
            f.f = 1;  
            strcat(f.file, optarg); // из файла берутся шаблоны
        }
        else if (opt == 'i') f.i = 1;
        else if (opt == 'v') f.v = 1;
        else if (opt == 'c') f.c = 1;
        else if (opt == 'l') f.l = 1;
        else if (opt == 'n') f.n = 1;
        else if (opt == 'h') f.h = 1;
        else if (opt == 's') f.s = 1;
        else if (opt == 'o') f.o = 1;
    }
     
    f.template[strlen(f.template) - 1] = '\0'; // "str1|str2|1231"

    if (f.e == 0) {
        strcat(f.template, argv[optind]);
        optind++;
    }

    if (optind == argc - 1) {
        lots_files = 1;
    }

    for (int i = optind; i < argc; i++) {

        if (f.e == 1 || f.is_flag == 0) {
            print_lines(argv[i], lots_files, f);
        }
        else if (f.is_flag == 0){
            print_lines(argv[i], lots_files, f);
        }
        else if (f.i == 1){
            print_lines(argv[i], lots_files, f);
        }
        else if (f.v == 1){
            //no enter between files. Check output(!)
            print_lines(argv[i], lots_files, f);
        }
        else if (f.h == 1){
            print_lines(argv[i], lots_files, f);
        }
        else if (f.s == 1){
            print_lines(argv[i], lots_files, f);
        }
    }

    return 0;
}

void print_lines(char * fp, int files, flag f) {
    FILE* file;
    regex_t re;
    char buffer[500];
    int match;

    if ((file = fopen(fp, "r")) != NULL) {

        while (fgets(buffer, 500, file) != NULL) {
            
            if (f.i) {
                regcomp(&re, f.template, REG_ICASE);
            }
            else {
                regcomp(&re, f.template, REG_EXTENDED);//0-sucses
            }
            match = regexec(&re, buffer, 0, NULL, 0);//0-match

            if (f.v) {
                if (match != 0) {
                    if (files){
                        printf("%s", buffer);
                    }
                    else {
                        printf("%s:%s", fp, buffer);
                    }
                }
            }
            if (f.e || f.i || (!f.is_flag) || f.s) {
                if (!match) {
                    if (files){
                        printf("%s", buffer);
                    }
                    else {
                        printf("%s:%s", fp, buffer);
                    }
                }
            }
            if (f.h) {
                if (match != 0) {
                    printf("%s", buffer);
                }
            }

            regfree(&re);
        }
        fclose(file);
    }

    else {
        if (!f.s) fprintf(stderr, "There's no such file \"%s\"\n", fp);
    }
    
}