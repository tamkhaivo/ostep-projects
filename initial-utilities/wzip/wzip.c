// gcc -o wzip wzip.c -Wall -Werror -O
// ./test-wzip.sh
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    int count;
    char current_char;
    char prev_char = '\0'; // Initialize with a character that won't match any input

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        
        if (fp == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        while (fread(&current_char, 1, 1, fp) == 1) {
            if (prev_char == '\0') { // First character encountered
                prev_char = current_char;
                count = 1;
            } else if (current_char == prev_char) {
                count++;
            } else {
                fwrite(&count, sizeof(int), 1, stdout);
                fwrite(&prev_char, sizeof(char), 1, stdout);
                prev_char = current_char;
                count = 1;
            }
        }
        fclose(fp);
    }

    // Handle the last sequence of characters
    if (prev_char != '\0') {
        fwrite(&count, sizeof(int), 1, stdout);
        fwrite(&prev_char, sizeof(char), 1, stdout);
    }

    return 0;
}
