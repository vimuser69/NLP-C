#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char **strarr(char *string, char *delim) {
    char **result;
    char *token;
    size_t i = 0;
    token = strtok(strdup(string), delim);
    while (token != NULL) {
        i++;
        token = strtok(NULL, delim);
    }
    result = (char **)malloc(sizeof(char *) * i + 1);
    i = 0;
    token = strtok(strdup(string), delim);
    while (token != NULL) {
        result[i] = (char *)malloc(sizeof(char) * strlen(token));
        strcpy(result[i], token);
        i++;
        token = strtok(NULL, delim);
    }
    result[i+1] = NULL;
    free(token);
    return result;
}

size_t strarrlen(char **strarr) {
    size_t i = 0;
    while (strarr[i] != NULL) {
        i++;
    }
    return i;
}

bool instrarr(char **strarr, char *string) {
    for (size_t i=0; i<strarrlen(strarr); i++) {
        if (strcmp(strarr[i], string) == 0) {
            return true;
        }
    }
    return false;
}

char **rdstrarr(char **strarr) {
    char **temp;
    temp = (char **)malloc(sizeof(char *) * strarrlen(strarr));
    size_t k = 0;
    for (size_t i=0; i<strarrlen(strarr); i++) {
        for (size_t e=0; e<strarrlen(strarr); e++) {
            if (strcmp(strarr[i], strarr[e]) == 0 && instrarr(temp, strarr[i]) == false) {
                temp[k] = (char *)malloc(sizeof(char) * strlen(strarr[i]));
                strcpy(temp[k], strarr[i]);
                k++;
            }
        }
    }
    char **result;
    result = (char **)malloc(sizeof(char *) * strarrlen(temp) + 1);
    for (size_t i=0; i<strarrlen(temp); i++) {
        result[i] = (char *)malloc(sizeof(char) * strlen(temp[i]));
        strcpy(result[i], temp[i]);
    }
    result[strarrlen(temp)] = NULL;
    free(temp);
    return result;
}

int main() {
    char **test = strarr("hello this is aa test test aa test gagagagaa", " ");
    char **remtest = rdstrarr(test);
    printf("%lu\n", strarrlen(test));
    printf("%lu\n", strarrlen(remtest));
    if (test[9] == NULL) {
        printf("YES TEST!\n");
    }
    if (remtest[6] == NULL) {
        printf("YES REMTEST!\n");
    }
    return 0;
}
