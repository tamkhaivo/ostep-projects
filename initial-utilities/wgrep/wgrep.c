// gcc -o wgrep wgrep.c -Wall -Werror -O
// ./test-wgrep.sh

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void search_stream(FILE *stream, const char *pattern) {
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, stream) != -1) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }
    free(line);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    const char* pattern = argv[1];

    // If no file is specified, read from standard input.
    if (argc == 2) {
        search_stream(stdin, pattern);
    } else {
        // Otherwise, iterate through the files provided.
        for (int i = 2; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("wgrep: cannot open file\n");
                exit(1);
            }
            search_stream(fp, pattern);
            fclose(fp);
        }
    }
    return 0;
}