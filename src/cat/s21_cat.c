#include <stdio.h>
#include <string.h>

#define LINE_SIZE 2048

void cat_n(FILE* fp);
void cat_b(FILE* fp);
void cat_e(FILE* fp);
void cat_s(FILE* fp);
void cat_t(FILE* fp);
void cat_v(FILE* fp, char* flag);
void cat(FILE* fp);

int main(int argc, char* argv[]) {
  int increase = 1;  // argv[1]==file,
  if ((argc < 2)) {
    fprintf(stderr, "Invalid entry");
  }

  else {
    for (int i = 1; i < argc; i++) {
      if (increase) {
        if (argv[1][0] == '-') {
          i++;
          increase = 0;  // argv[1]==flag, argv[2]==file
        }
      }

      FILE* file;

      if ((file = fopen(argv[i], "r")) != NULL) {
        if (!strcmp(argv[1], "-T"))
          cat_t(file);

        else if (!strcmp(argv[1], "-E"))
          cat_e(file);

        else if ((!strcmp(argv[1], "-t")) || (!strcmp(argv[1], "-e")) ||
                 (!strcmp(argv[1], "-v")))
          cat_v(file, argv[1]);

        else if ((!strcmp(argv[1], "-s")) ||
                 (!strcmp(argv[1], "--squeeze-blank")))
          cat_s(file);

        else if ((!strcmp(argv[1], "-b")) ||
                 (!strcmp(argv[1], "--number-nonblank")))
          cat_b(file);

        else if ((!strcmp(argv[1], "-n")) || (!strcmp(argv[1], "--number")))
          cat_n(file);

        else if (!increase)
          fprintf(stderr, "There is no such option \"%s\"\n", argv[1]);

        else if (increase)
          cat(file);

        fclose(file);
      } else {
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
        printf("$");
      }
    } else if ((!strcmp(flag, "-t"))) {
      if (ch == 9) {
        printf("^I");
        continue;
      }
    }
    if ((!strcmp(flag, "-e")) || (!strcmp(flag, "-t")) ||
        (!strcmp(flag, "-v"))) {
      if (ch == 127) {
        printf("^?");
      }

      else if ((ch >= 0 && ch <= 8) || (ch >= 11 && ch <= 31)) {
        printf("^%c", ch + 64);

      } else if (ch > 127) {
        ch = ch % 128;
        printf("M-");
        if (ch >= 0 && ch <= 31) {
          printf("^%c", ch + 64);
        } else if (ch == 127) {
          printf("^?");
        } else {
          printf("%c", ch);
        }
      } else {
        putchar(ch);
      }
    }
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
  int ch_start = getc(fp);
  int ch_next = 0;

  if (ch_start == '\n') {
    while (ch_start != EOF && ch_start == '\n') {
      if (ch_start == '\n' && ch_next == '\n') {
      } else
        putchar(ch_start);

      ch_next = ch_start;
      ch_start = getc(fp);
    }
  }

  int ch_last = ch_start;
  int ch_first = 0;
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
  int ch_first = getc(fp);
  int ch_second = 0;
  int new_line = 1;
  int count = 1;

  while (ch_first != EOF) {
    if ((new_line) && ch_first == '\n') {
      printf("%c", ch_first);
      ch_first = getc(fp);
      continue;
    }

    if (ch_first != '\n') {
      if (new_line) {
        printf("%6d\t", count);
        new_line = 0;
        count++;
      }
    } else {
      new_line = 1;
    }
    printf("%c", ch_first);
    ch_first = getc(fp);
  }
}

void cat_n(FILE* fp) {
  int ch_first = getc(fp);
  int ch_second = 0;
  int count = 1;

  if (ch_first != EOF) {
    printf("%6d\t", count);
    count++;
  }

  while (ch_first != EOF) {
    ch_second = ch_first;
    ch_first = getc(fp);

    if (ch_second == '\n' && ch_first != EOF) {
      printf("%c", ch_second);
      printf("%6d\t", count);
      count++;
    } else {
      printf("%c", ch_second);
    }
  }
}