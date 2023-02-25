#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

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

char **unionstrarr(char **strarr1, char **strarr2) {
    char **temp;
    temp = (char **)malloc(sizeof(char *) * (strarrlen(strarr1) + strarrlen(strarr2)));
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
    char **result = rdstrarr(temp);
    free(temp);
    return result;
}

char **interstrarr(char **strarr1, char **strarr2) {
    char **temp;
    temp = (char **)malloc(sizeof(char *) * (strarrlen(strarr1) + strarrlen(strarr2)));
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
    char **result = rdstrarr(temp);
    free(temp);
    return result;
}

int main() {
    char **test1 = strarr("hi there lol hello hi", " ");
    char **test2 = strarr("hello there lol", " ");
    //char **unionsa = unionstrarr(test1, test2);
    char **intersa = interstrarr(test1, test2);
    return 0;
}
