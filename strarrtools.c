#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char **strarr(char *string, char *delim) {
    char **result;
    size_t i = 0;
    char *token = strtok(strdup(string), delim);
    while (token != NULL) {
        i++;
        token = strtok(NULL, delim);
    }
    result = (char **)malloc(sizeof(char *) * (i + 1));
    i = 0;
    token = strtok(strdup(string), delim);
    while (token != NULL) {
        result[i] = (char *)malloc(sizeof(char) * strlen(token));
        strcpy(result[i], token);
        i++;
        token = strtok(NULL, delim);
    }
    result[i] = NULL;
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

char **shstrarr(char **strarr) {
    char **result = (char **)malloc(sizeof(char *) * strarrlen(strarr));
    for (size_t i=0; i<strarrlen(strarr); i++) {
        result[i] = (char *)malloc(sizeof(char) * strlen(strarr[i]));
        strcpy(result[i], strarr[i]);
    }
    result[strarrlen(strarr)] = NULL;
    return result;
}

char **rdstrarr(char **strarr) {
    char **temp = (char **)malloc(sizeof(char *) * strarrlen(strarr));
    for (size_t i = 0; i < strarrlen(strarr); i++) {
        temp[i] = NULL;
    }
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
    temp[k] = NULL;
    char **result = shstrarr(temp);
    free(temp);
    return result;
}

char **unionstrarr(char **strarr1, char **strarr2) {
    char **temp = (char **)malloc(sizeof(char *) * (strarrlen(strarr1) + strarrlen(strarr2)));
    for (size_t i=0; i<(strarrlen(strarr1) + strarrlen(strarr2)); i++) {
        temp[i] = NULL;
    }
    size_t k = 0;
    for (size_t i=0; i<strarrlen(strarr1); i++) {
        temp[k] = (char *)malloc(sizeof(char) * strlen(strarr1[i]));
        strcpy(temp[k], strarr1[i]);
        k++;
    }
    for (size_t i=0; i<strarrlen(strarr2); i++) {
        temp[k] = (char *)malloc(sizeof(char) * strlen(strarr2[i]));
        strcpy(temp[k], strarr2[i]);
        k++;
    }
    temp[k] = NULL;
    char **result = rdstrarr(temp);
    free(temp);
    return result;
}

char **interstrarr(char **strarr1, char **strarr2) {
    char **temp = (char **)malloc(sizeof(char *) * (strarrlen(strarr1) + strarrlen(strarr2)));
    for (size_t i=0; i<(strarrlen(strarr1) + strarrlen(strarr2)); i++) {
        temp[i] = NULL;
    }
    size_t k = 0;
    for (size_t i=0; i<strarrlen(strarr1); i++) {
        for (size_t e=0; e<strarrlen(strarr2); e++) {
            if (strcmp(strarr1[i], strarr2[e]) == 0) {
                temp[k] = (char *)malloc(sizeof(char) * strlen(strarr1[i]));
                strcpy(temp[k], strarr1[i]);
                k++;
            }
        }
    }
    temp[k] = NULL;
    char **result = rdstrarr(temp);
    free(temp);
    return result;
}

double jaccardstrarr(char **strarr1, char **strarr2) {
    return (double)strarrlen(interstrarr(strarr1, strarr2)) / strarrlen(unionstrarr(strarr1, strarr2));
}

int main() {
    char **test1 = strarr("cat dog hippo monkey", " ");
    char **test2 = strarr("monkey rhino ostrich salmon", " ");
    printf("%lf\n", jaccardstrarr(test1, test2)); // 1/7 = 0.142857 CORRECT!
    return 0;
}
