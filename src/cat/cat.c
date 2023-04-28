#include <stdio.h>
#include <string.h>

void cat_n(char* fp);
void cat_b(char* fp);
void cat_e(char* fp);
void cat_s(char* fp);
void cat_t(char* fp);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Invalid entry");
    }
    

    else {
        if (!strcmp(argv[1], "-t")) {
            cat_t(argv[2]);
        }
        if (!strcmp(argv[1], "-e")) {
            cat_e(argv[2]);
        }
        if (!strcmp(argv[1], "-s")) {
            cat_s(argv[2]);
        }
        if (!strcmp(argv[1], "-b")) {
            cat_b(argv[2]);
        }
        if (!strcmp(argv[1], "-n")) {
            cat_n(argv[2]);
        }
    }
    return 0;
}

void cat_t(char* fp) {
    //не работает вообще
    FILE *file;
    int ch;
    if ((file = fopen(fp, "r")) != NULL) {
        while ((ch = getc(file)) != EOF) {
            if (ch == '\t') {
                printf("^I");
            }
            else {
                putchar(ch);
            }    
        }
    }
    fclose(file);
}

void cat_e(char* fp) {
    FILE *file;
    char ch;
    if ((file = fopen(fp, "r")) != NULL) {
        while ((ch = getc(file)) != EOF) {
            if (ch == '\n') {
                printf("$");
            }
            putchar(ch);
        }
    }
    fclose(file);
}

void cat_s(char* fp) {
    FILE *file;
    if ((file = fopen(fp, "r")) != NULL) {
        int ch_first;
        int ch_last;
        int ch_second;

        ch_last = getc(file);
        while ( ch_last != EOF) {
            if (ch_first == '\n' && ch_last == '\n' && ch_second == '\n') {      
                
            } else 
            putchar(ch_last);
            int temp = ch_second;
            ch_second = ch_last; 
            ch_first = temp;
            ch_last = getc(file);
            
        }
    }
    fclose(file);
}

void cat_b(char* fp) {
    FILE *file;
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
    }
    fclose(file);
}

void cat_n(char* fp) {
    FILE *file;
    char buffer[500];
    if ((file = fopen(fp, "r")) != NULL) {
        int count = 1;
        while (fgets(buffer, 500, file) != NULL) {
            printf("%d %s", count, buffer);
            count++;
        }
    }
    fclose(file);
}