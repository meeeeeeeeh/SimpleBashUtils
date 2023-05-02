#include <stdio.h>
#include <unistd.h>
#include <regex.h>

void grep(char* template, char* fp);
void grep_i(char* template, char* fp);

int main(int argc, char* argv[]) {
    int opt = 0;
    int flags[100];
    int no_flags = 1;
    char options[10] = "e:i:";
    //Допустимые флаги, если есть :, то после флага должен быть шаблон(то что после флага считается шаблоном)
    //шаблон заносится в переменную getopt
    //Если после флага ничего не стоит возращается NULL - для обработки ошибок

    int count = 0;
    while((opt = getopt(argc, argv, options)) != -1) {
        flags[count] = opt;
        no_flags = 0;
        count++;
    }

    if (no_flags) {
       grep(argv[1], argv[2]);
    }
    else {
        for (int i=0; i < count; i++) {
            if (flags[i] == 'e') {
                grep(optarg, argv[argc-1]);
            }
            if (flags[i] == 'i') {
                grep_i(optarg, argv[argc-1]);
            }
        }
        // printf("%s", argv[argc-1]);
        // printf("%s", optarg);
    }
    
    return 0;
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
            if (match == 0) {
                printf("matched\n");
            }
            else{
                printf("not matched\n");
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
            if (match == 0) {
                printf("matched\n");
            }
            else{
                printf("not matched\n");
            }
            regfree(&re);
        }
        fclose(file);
    } 
    else {
        printf("There's no such file \"%s\"\n", fp);
    }
}