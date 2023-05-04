#include <stdio.h>
#include <string.h>

void cat_n(FILE* fp);
void cat_b(FILE* fp);
void cat_e(FILE* fp);
void cat_s(FILE* fp);
void cat_t(FILE* fp);
void cat_v(FILE* fp, char* flag);
void cat(FILE* fp);

int main(int argc, char* argv[]) {
    int increase = 1; // argv[1]==file, 
    if ((argc < 2)) {
        fprintf(stderr, "Invalid entry");
    }

    else {
        
        for (int i = 1; i < argc; i++) {
            if (increase) {
               if (argv[1][0] == '-') {
                    i++;
                    increase = 0; // argv[1]==flag, argv[2]==file
                } 
            }

            FILE* file;
            
            if ((file = fopen(argv[i], "r")) != NULL) {
                
                if (!strcmp(argv[1], "-T")) 
                    cat_t(file);
    
                else if (!strcmp(argv[1], "-E")) 
                    cat_e(file);
    
                else if ((!strcmp(argv[1], "-t")) || (!strcmp(argv[1], "-e")) || (!strcmp(argv[1], "-v"))) 
                    cat_v(file, argv[1]);
    
                else if ((!strcmp(argv[1], "-s")) || (!strcmp(argv[1], "--squeeze-blank"))) 
                    cat_s(file);
    
                else if ((!strcmp(argv[1], "-b")) || (!strcmp(argv[1], "--number-nonblank"))) 
                    cat_b(file);
    
                else if ((!strcmp(argv[1], "-n")) || (!strcmp(argv[1], "--number"))) 
                    cat_n(file);

                else if (!increase)
                    fprintf(stderr, "There is no such option \"%s\"\n", argv[1]);

                else if (increase) 
                    cat(file);

                fclose(file);
            }   
            else {
                fprintf(stderr, "There's no such file \"%s\"\n", argv[i]);
            }  
        }
        
    }

    return 0;
}

void cat(FILE* fp) {
    char ch;
    while ((ch = getc(fp)) != EOF) {
        putchar(ch);
    }    
}

void cat_v(FILE* fp, char* flag) {
    int ch;
    
    while ((ch = getc(fp)) != EOF) {
        if ((!strcmp(flag, "-e"))) {
            if (ch == 10) {
                printf("$%c", ch);
            }
        }
        else if ((!strcmp(flag, "-t"))) {
            if (ch == 9) {
                printf("^I");
            }
        }
        
        if (ch == 127)
            printf("^?");

        else if ((ch >= 0 && ch <= 8) || (ch >= 11 && ch <= 31) || (ch >= 128 && ch <= 255)) {
            if (ch >= 128 && ch <= 159) printf("M-");

            printf("^%c", (ch % 128) + 64);

        } else
            printf("%c", ch);
    }
}

void cat_t(FILE* fp) {
    int ch;
    while ((ch = getc(fp)) != EOF) {
        if (ch == 9) {
            printf("^I");
        } else {
            putchar(ch);
        }
    }
}

void cat_e(FILE* fp) {
    char ch;
    while ((ch = getc(fp)) != EOF) {
        if (ch == '\n') {
            printf("$");
        }
        putchar(ch);
    }
}

void cat_s(FILE* fp) {
    int ch_first = 0;
    int ch_last = getc(fp);
    int ch_second = 0;
    
    while (ch_last != EOF) {
        if (ch_first == '\n' && ch_last == '\n' && ch_second == '\n') {
        } else
            putchar(ch_last);
        int temp = ch_second;
        ch_second = ch_last;
        ch_first = temp;
        ch_last = getc(fp);
    }   
}

void cat_b(FILE* fp) {
    char buffer[500];
    int count = 1;
    while (fgets(buffer, 500, fp) != NULL) {
        if (strcmp(buffer, "\n") != 0) {
            printf("\t%d %s", count, buffer);
            count++;
        } 
        else {
            printf("%s", buffer);
        }
    }
}

void cat_n(FILE* fp) {
    char buffer[500];
    int count = 1;
    while (fgets(buffer, 500, fp) != NULL) {
        printf("\t%d %s", count, buffer);
        count++;
    }
}