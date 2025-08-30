// wgrep.c - minimal grep-like program
// Usage: wgrep <searchterm> [file ...]
// - If <searchterm> missing: print "wgrep: searchterm missing" and exit 1
// - If a file can't be opened: print "wgrep: cannot open file" and exit 1
// - If no files are given: read from stdin
// - Print any line that contains <searchterm> as a substring

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void grep_stream(const char *needle, FILE *fp) {
    char *line = NULL;
    size_t cap = 0;
    ssize_t n;
    while ((n = getline(&line, &cap, fp)) != -1) {
        if (strstr(line, needle) != NULL) {
            fputs(line, stdout);
        }
    }
    free(line);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stdout, "wgrep: searchterm [file ...]\n");
        return 1;
    }

    const char *needle = argv[1];

    if (argc == 2) {
        // read from stdin
        grep_stream(needle, stdin);
        return 0;
    }

    // read from each file
    for (int i = 2; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stdout, "wgrep: cannot open file\n");
            return 1;
        }
        grep_stream(needle, fp);
        fclose(fp);
    }

    return 0;
}
