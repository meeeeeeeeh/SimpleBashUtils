#include <stdio.h>
#include <string.h>

void cat_n(char* fp);
void cat_b(char* fp);
void cat_e(char* fp);
void cat_s(char* fp);
void cat_t(char* fp);
void cat_v(char* fp, char* flag);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Invalid entry");
    }

    else {
        if (!strcmp(argv[1], "-T")) 
            cat_t(argv[2]);

        else if (!strcmp(argv[1], "-E")) 
            cat_e(argv[2]);

        else if ((!strcmp(argv[1], "-t")) || (!strcmp(argv[1], "-e")) || (!strcmp(argv[1], "-v"))) 
            cat_v(argv[2], argv[1]);

        else if ((!strcmp(argv[1], "-s")) || (!strcmp(argv[1], "--squeeze-blank"))) 
            cat_s(argv[2]);

        else if ((!strcmp(argv[1], "-b")) || (!strcmp(argv[1], "--number-nonblank"))) 
            cat_b(argv[2]);

        else if ((!strcmp(argv[1], "-n")) || (!strcmp(argv[1], "--number"))) 
            cat_n(argv[2]);
    }

    return 0;
}

void cat_v(char* fp, char* flag) {
    FILE* file = fopen(fp, "r");
    int ch;
    
    if ((file = fopen(fp, "r")) != NULL) {
        while ((ch = getc(file)) != EOF) {
            if ((!strcmp(flag, "-e"))) {
                if (ch == 10) {
                    printf("$%c", ch);
                }
            }
            if ((!strcmp(flag, "-t"))) {
                if (ch == 9) {
                    printf("^I");
                }
            }
            if (ch == '\t' || ch == '\n')
                printf("%c", ch);

            if (ch == 127)
                printf("^?");

            else if ((ch >= 0 && ch <= 8) || (ch >= 11 && ch <= 31) || (ch >= 128 && ch <= 255)) {
                if (ch >= 128 && ch <= 159) printf("M-");

                printf("^%c", (ch % 128) + 64);

            } else
                printf("%c", ch);
        }
        fclose(file);
    }
    else {
        printf("There's no such file \"%s\"\n", fp);
    }
    
}

void cat_t(char* fp) {
    FILE* file;
    int ch;

    if ((file = fopen(fp, "r")) != NULL) {
        while ((ch = getc(file)) != EOF) {
            if (ch == 9) {
                printf("^I");
            } else {
                putchar(ch);
            }
        }
        fclose(file);
    } 
    
    
}

void cat_e(char* fp) {
    FILE* file;
    char ch;

    if ((file = fopen(fp, "r")) != NULL) {
        while ((ch = getc(file)) != EOF) {
            if (ch == '\n') {
                printf("$");
            }
            putchar(ch);
        }
        fclose(file);
    } 
    else {
        printf("There's no such file \"%s\"\n", fp);
    }
    
}

void cat_s(char* fp) {
    FILE* file;

    if ((file = fopen(fp, "r")) != NULL) {
        int ch_first;
        int ch_last;
        int ch_second;

        ch_last = getc(file);
        while (ch_last != EOF) {
            if (ch_first == '\n' && ch_last == '\n' && ch_second == '\n') {
            } else
                putchar(ch_last);
            int temp = ch_second;
            ch_second = ch_last;
            ch_first = temp;
            ch_last = getc(file);
        }
        fclose(file);
    } 
    else {
        printf("There's no such file \"%s\"\n", fp);
    }
    
}

void cat_b(char* fp) {
    FILE* file;
    char buffer[500];

    if ((file = fopen(fp, "r")) != NULL) {
        int count = 1;
        while (fgets(buffer, 500, file) != NULL) {
            if (strcmp(buffer, "\n") != 0) {
                printf("%d %s", count, buffer);
                count++;
            } else {
                printf("%s", buffer);
            }
        }
        fclose(file);
    } 
    else {
        printf("There's no such file \"%s\"\n", fp);
    }
    
}

void cat_n(char* fp) {
    FILE* file;
    char buffer[500];

    if ((file = fopen(fp, "r")) != NULL) {
        int count = 1;
        while (fgets(buffer, 500, file) != NULL) {
            printf("%d %s", count, buffer);
            count++;
        }
        fclose(file);
    } 
    else {
        printf("There's no such file \"%s\"\n", fp);
    }
    
}