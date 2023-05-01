#include <stdio.h>
#include <unistd.h>
#include <regex.h>

int main(int argc, char* argv[]) {
    int opt = 0;
    int no_flags = 1;
    
    while((opt = getopt(argc, argv, "e:")) != -1) {
        putchar(opt);
        no_flags = 0;
    }
    printf("%s", optarg);

    if (no_flags) {
        printf("%d", argv[3]);
        printf("nope");

    
    return 0;
}