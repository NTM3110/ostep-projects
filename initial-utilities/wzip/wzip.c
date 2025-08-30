// wzip.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stdout, "wzip: file1 [file2 ...]\n");
        return 1;
    }

    int prev = EOF;
    int count = 0;

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (!fp) { fprintf(stderr, "wzip: cannot open file\n"); return 1; }

        int c;
        while ((c = fgetc(fp)) != EOF) {
            if (prev == EOF) { prev = c; count = 1; }
            else if (c == prev) { count++; }
            else {
                fwrite(&count, sizeof(int), 1, stdout);
                fputc(prev, stdout);
                prev = c;
                count = 1;
            }
        }
        fclose(fp);
        // NOTE: do NOT flush here; keep prev/count for next file
    }

    if (prev != EOF) {
        fwrite(&count, sizeof(int), 1, stdout);
        fputc(prev, stdout);
    }
    return 0;
}
