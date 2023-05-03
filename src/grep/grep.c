#include <stdio.h>
#include <unistd.h>
#include <regex.h>

void grep(char* template, char* fp);
void grep_i(char* template, char* fp);
void grep_c(char* template, char* fp);
void grep_v(char* template, char* fp);

int main(int argc, char* argv[]) {
    int opt = 0;
    int flags[100];
    int no_flags = 1;
    char options[10] = "e:i:v:c:";
    //Допустимые флаги, если есть :, то после флага должен быть шаблон(то что после флага считается шаблоном)
    //шаблон заносится в переменную getopt
    //Если после флага ничего не стоит возращается NULL - для обработки ошибок

    // optind  это индекс аргумента строки который не шаблон и не флаг

    int count = 0;
    while((opt = getopt(argc, argv, options)) != -1) {
        flags[count] = opt;
        no_flags = 0;
        count++;
    }

    // printf("%d\n", optind);
    // printf("%s\n", optarg);
   
    
    if (no_flags) {
        for (int i = 2; i < argc; i++) {
            grep(argv[1], argv[i]);
        }
    }
    else {
        for (int i=0; i < count; i++) {
            if (flags[i] == 'e') {
                for (int i = optind; i < argc; i++) {
                    printf("%s\n", argv[i]);
                    grep(optarg, argv[i]);
                }
                
            }
            if (flags[i] == 'i') {
                for (int i = optind; i < argc; i++) {
                    printf("%s\n", argv[i]);
                    grep_i(optarg, argv[i]);
                }
            }

            if (flags[i] == 'c') {
               for (int i = optind; i < argc; i++) {
                    printf("%s\n", argv[i]);
                    grep_c(optarg, argv[i]);
                }
            }

            if (flags[i] == 'v') {
                for (int i = optind; i < argc; i++) {
                    printf("%s\n", argv[i]);
                    grep_v(optarg, argv[i]);
                }
            }
        }
        
    }
    
    return 0;
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
}