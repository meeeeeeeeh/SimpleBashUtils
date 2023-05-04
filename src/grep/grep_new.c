#include <stdio.h>
#include <unistd.h>
#include <regex.h>
#include <string.h>

void grep(char* template, char* fp);
void grep_i(char* template, char* fp);
void grep_c(char* template, char* fp);
void grep_v(char* template, char* fp);
void grep_l(char* template, char* fp);

typedef struct flag {
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
    int o;
    char file[300]; 
} flag;


int main(int argc, char* argv[]) {
    int opt = 0;

    flag f = {}; //делает всем значениям структуры значение 0
    f.template[0] = '\0';
    f.file[0] = '\0';

    //Допустимые флаги, если есть :, то после флага должен быть шаблон(то что после флага считается шаблоном)
    //шаблон заносится в переменную getopt
    //Если после флага ничего не стоит возращается NULL - для обработки ошибок

    // optind  это индекс аргумента строки который не шаблон и не флаг

    // printf("before argv: ");
    // for (int i = 0; i < argc; i++) printf("%s ", argv[i]);
    // printf("\n");

    while((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
        if (opt == 'e') {
            f.e = 1;  
            strcat(f.template, optarg); // "str1|str2|1231|"
            strcat(f.template, "|");
        }
        if (opt == 'f') {
            f.f = 1;  
            strcat(f.file, optarg); // "str1|str2|1231|"
            strcat(f.file, " ");
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

   /*printf("\ntemplates: %s\n\n", f.template);

    printf("files: ");
    for (int i = optind; i < argc; i++) printf("%s ", argv[i]);
    printf("\n\n");*/

    for (int i = optind; i < argc; i++) {
        FILE* file;
        
        if ((file = fopen(argv[i], "r")) != NULL) {
            regex_t re;
            char buffer[500];
            int match;

            while (fgets(buffer, 500, file) != NULL) {

                regcomp(&re, f.template, REG_EXTENDED);//0-sucses
                match = regexec(&re, buffer, 0, NULL, 0);//0-match
                
                if (!match) {
                    printf("%s", buffer);
                }
                regfree(&re);
            }
            fclose(file);
        } 
        else {
            fprintf(stderr, "There's no such file \"%s\"\n", argv[i]);
        }
        
    }

    /*printf("after argv: ");
    for (int i = 0; i < argc; i++) printf("%s ", argv[i]);
    printf("\n");

    printf("%d\n", optind);
    printf("%s\n", optarg);
   
    
    if (no_flags) {
        for (int i = 2; i < argc; i++) {
            grep(argv[1], argv[i]);
        }
    }
    else {
        for (int k = optind; k < argc; k++) {
            for (int i=0; i < count; i++) {
                if (flags[i] == 'e') {
                    printf("%s\n", argv[k]);
                    grep(optarg, argv[k]); 
                }
                
                if (flags[i] == 'i') {
                    printf("%s\n", argv[k]);
                    grep_i(optarg, argv[k]);
                }

                if (flags[i] == 'c') {
                    printf("%s\n", argv[k]);
                    grep_c(optarg, argv[k]);
                }

                if (flags[i] == 'v') {
                    printf("%s\n", argv[k]);
                    grep_v(optarg, argv[k]); 
                }
                if (flags[i] == 'l') {
                    printf("%s\n", argv[k]);
                    grep_l(optarg, argv[k]); 
                }
            }
        }
        
    }*/
    
    
    return 0;
}

/*void grep_l(char* template, char* fp) {
    regex_t re;
    FILE* file;
    char buffer[500];
    int match;
    int print_file = 0;

    if ((file = fopen(fp, "r")) != NULL) {
        while (fgets(buffer, 500, file) != NULL) {

            regcomp(&re, template, REG_EXTENDED);
            //0-sucsess
            match = regexec(&re, buffer, 0, NULL, 0);
            //0-match
            if (!match) {
                print_file = 1;
            }
            regfree(&re);
        }
        fclose(file);
        if(print_file) {
            printf("%s\n", fp);
        }
    } 
    else {
        printf("There's no such file \"%s\"\n", fp);
    }
}

void grep_v(char* template, char* fp) {
    regex_t re;
    FILE* file;
    char buffer[500];
    int match;

    if ((file = fopen(fp, "r")) != NULL) {
        while (fgets(buffer, 500, file) != NULL) {

            regcomp(&re, template, REG_EXTENDED);
            //0-sucsess
            match = regexec(&re, buffer, 0, NULL, 0);
            //0-match
            if (match != 0) {
                printf("%s", buffer);
            }
            regfree(&re);
        }
        fclose(file);
    } 
    else {
        printf("There's no such file \"%s\"\n", fp);
    }
}

void grep_c(char* template, char* fp) {
    regex_t re;
    FILE* file;
    char buffer[500];
    int match;
    int count = 0;

    if ((file = fopen(fp, "r")) != NULL) {
        while (fgets(buffer, 500, file) != NULL) {

            regcomp(&re, template, REG_EXTENDED);
            //0-sucsess
            match = regexec(&re, buffer, 0, NULL, 0);
            //0-match
            if (!match) {
                count++;
            }
            regfree(&re);
        }
        printf("%d", count);
        fclose(file);
    } 
    else {
        printf("There's no such file \"%s\"\n", fp);
    }
}

void grep(char* template, char* fp) {
    regex_t re;
    FILE* file;
    char buffer[500];
    int match;

    if ((file = fopen(fp, "r")) != NULL) {
        while (fgets(buffer, 500, file) != NULL) {

            regcomp(&re, template, REG_EXTENDED);
            //0-sucsess
            match = regexec(&re, buffer, 0, NULL, 0);
            //0-match
            if (!match) {
                printf("%s", buffer);
            }
            regfree(&re);
        }
        fclose(file);
    } 
    else {
        printf("There's no such file \"%s\"\n", fp);
    }
}

void grep_i(char* template, char* fp) {
    regex_t re;
    FILE* file;
    char buffer[500];
    int match;

    if ((file = fopen(fp, "r")) != NULL) {
        while (fgets(buffer, 500, file) != NULL) {

            regcomp(&re, template, REG_ICASE);
            //0-sucsess
            match = regexec(&re, buffer, 0, NULL, 0);
            //0-match
            if (!match) {
                printf("%s", buffer);
            }

            regfree(&re);
        }
        fclose(file);
    } 
    else {
        printf("There's no such file \"%s\"\n", fp);
    }
}*/