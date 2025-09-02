// gcc -o wunzip wunzip.c -Wall -Werror -O
// ./test-wunzip.sh

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // If no files are specified, print usage and exit with status 1.
    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    // Process each file provided on the command line.
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wunzip: cannot open file\n");
            exit(1);
        }

        int count;
        char character;

        // Read the file which is composed of 5-byte chunks:
        // a 4-byte integer and a 1-byte character.
        while (fread(&count, sizeof(int), 1, fp) == 1) {
            // A count must be followed by a character.
            fread(&character, sizeof(char), 1, fp);

            for (int j = 0; j < count; j++) {
                putchar(character);
            }
        }
        fclose(fp);
    }
    return 0;
}
