#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[1000];
    char **words = NULL;
    char **uniqueWords = NULL;
    int *freqArr = NULL;
    int totalWords = 0;
    int totalUnique = 0;
    double avgLen = 0;
    const char *delimiters = " .,/:";
    
    printf("Enter a sentence: ");
    fgets(input, sizeof(input), stdin);

    size_t inputLength = strlen(input);
    if (inputLength > 0 && input[inputLength - 1] == '\n') {
        input[inputLength - 1] = '\0';
    }

    char *token = strtok(input, delimiters);

    while (token != NULL) {
        char *newWord = (char *)malloc(strlen(token) + 1);
        strcpy(newWord, token);

        avgLen += strlen(newWord);

        int isUnique = 1;
        for (int i = 0; i < totalUnique; i++) {
            if (strcmp(token, uniqueWords[i]) == 0) {
                isUnique = 0;
                freqArr[i]++;
                break;
            }
        }

        if (isUnique) {
            uniqueWords = (char **)realloc(uniqueWords, (totalUnique + 1) * sizeof(char *));
            uniqueWords[totalUnique] = newWord;
            totalUnique++;

            freqArr = (int *)realloc(freqArr, totalUnique * sizeof(int));
            freqArr[totalUnique - 1] = 1;
        }

        words = (char **)realloc(words, (totalWords + 1) * sizeof(char *));
        words[totalWords] = newWord;
        totalWords++;

        token = strtok(NULL, delimiters);
    }

    printf("There are %d unique words in the sentence:\n",totalUnique);
    printf("Unique Words in the sentence:\n");
    for (int i = 0; i < totalUnique; i++) {
        printf("%s (Frequency: %d)\n", uniqueWords[i], freqArr[i]);
        free(words[i]);
    }
    printf("Average word length: %0.2lf", avgLen/totalWords);

    return 0;
}
