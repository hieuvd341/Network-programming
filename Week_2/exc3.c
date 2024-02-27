#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* s = NULL;

void Append(char** s, const char* x) {
    if (*s == NULL) {
        *s = malloc(strlen(x) + 1); 
        strcpy(*s, x); 
    } else {
        int oldLen = strlen(*s);
        int newLen = oldLen + strlen(x) + 1; 
        *s = (char*)realloc(*s, newLen);
        strcat(*s, x); 
    }
}

int main() {
    Append(&s, "Xin ");
    Append(&s, "chao ");
    Append(&s, "cac ");
    Append(&s, "ban!");
    printf("%s", s);
    free(s);
    return 0;
}
