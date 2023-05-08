#include <stdio.h>
#include <unistd.h>
#include <regex.h>
#include <string.h>

typedef struct flag{
    int e;
    char template[1000];
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
} flag;

void print_lines(char * fp, int files, flag f);
void invert(int* value);

int main(int argc, char* argv[]) {
    flag f = {}; //делает всем значениям структуры значение 0
    f.template[0] = '\0';
    f.file[0] = '\0';
    int lots_files = 1;
    int opt = 0;

    while((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
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

    if (f.e == 0 && f.f == 0) {
        strcat(f.template, argv[optind]);
        optind++;
    }

    if (f.f) {
        char buffer[500];
        FILE* fp;
        if ((fp = fopen(f.file, "r")) != NULL) {

            while (fgets(buffer, 500, fp) != NULL) {
                if (buffer[strlen(buffer) - 1] == '\n' && buffer[0] != '\n')
                    buffer[strlen(buffer) - 1] = '\0';
                    
                strcat(f.template, buffer);
                strcat(f.template, "|");

            }
            f.template[strlen(f.template) - 1] = '\0';
        }
        else {
            if (!f.s) fprintf(stderr, "There's no such file \"%s\"\n", f.file);
        } 
    }

    if (optind == argc - 1) {
        lots_files = 0;
    }

    for (int i = optind; i < argc; i++) {
        
        print_lines(argv[i], lots_files, f);

    }

    return 0;
}

void print_lines(char * fp, int files, flag f) {
    FILE* file;
    regex_t re;
    char buffer[500];
    int match;
    int count = 0;
    int line_num = 0;

    if ((file = fopen(fp, "r")) != NULL) {

        while (fgets(buffer, 500, file) != NULL) {
            line_num++;
            if (f.i) {
                regcomp(&re, f.template, REG_ICASE);
            }
            else {
                regcomp(&re, f.template, REG_EXTENDED);//0-sucses
            }
            match = regexec(&re, buffer, 0, NULL, 0);//0-match

            if (f.v) invert(&match); 
            
            if (!match) {
                count++;
                if ((!f.c) && (!f.l)) {
                    if (files && (!f.h)){
                        printf("%s:", fp);
                    }
                    if (f.n) {
                        printf("%d:", line_num);
                    }
                    printf("%s", buffer);
                    
                    int len = strlen(buffer);
                    if (buffer[len-1] != '\n') printf("\n");
                }
            }
            regfree(&re);
        }
        fclose(file);

        if (count > 0 && f.l) {
            printf("%s\n", fp);
        }

        if (f.c) {
            if (files){
                printf("%s:", fp);
            }
            printf("%d\n", count);
        }
    }
    else {
        if (!f.s) fprintf(stderr, "There's no such file \"%s\"\n", fp);
    }
}

void invert(int* value) {
    if (*value == 1) {
        *value = 0;
    }
    else {
        *value = 1;
    }
}