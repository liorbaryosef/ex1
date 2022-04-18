//
// Created by liorb on 18/04/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char* stringDuplicator(char* s, int times) {
    assert(s);
    assert(times > 0);
    int len = strlen(s);
    char* out = malloc(len*times);
    if (!out) {
        return NULL;
    }
    char* current = out;
    for (int i=0; i<times; i++) {
        strcpy(current,s);
        current = current + len;
    }
    return out;
}

int main() {
    char* string = "Hello";
    char* new = NULL;
    new = stringDuplicator(string, 3);
    printf("%s\n", new);
    free(new);
}