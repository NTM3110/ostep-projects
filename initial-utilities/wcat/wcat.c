#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // If no files are given, do nothing (like cat)
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stdout, "wcat: cannot open file\n");
            return 1;
        }

        int c;
        while ((c = fgetc(fp)) != EOF) {
            putchar(c);
        }

        fclose(fp);
    }

    return 0;
}
