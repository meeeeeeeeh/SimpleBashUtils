#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char buffer[256];
    if (argc < 3) {
        printf("Invalid entry");
    }
    else {
        if (!strcmp(argv[1], "-b")) {
            FILE *file;
            file = fopen(argv[2], "r");
            if (file) {
                int count=1;
                while(fgets(buffer, 200, file) != NULL) {
                    if (strcmp(buffer, "\n") != 0) {
                        printf("%d %s",count, buffer);
                        count++;
                    }
                    else {
                       printf("%s", buffer); 
                    }
                    
                }
            
            }
            fclose(file);
        }
        if (!strcmp(argv[1], "-n")) {
            FILE *file;
            file = fopen(argv[2], "r");
            if (file) {
                int count=1;
                while(fgets(buffer, 256, file) != NULL) {
                    printf("%d %s",count, buffer);
                    count++;
                }
            
            }
            fclose(file);
        }
    }
    return 0;
}