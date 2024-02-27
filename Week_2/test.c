#define _DEFAULT_SOURCE
#include <dirent.h>
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
int file_select(const struct dirent *entry)
{
   return strcmp(entry->d_name, "test2222");
}
int main(void)
{
    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, file_select, alphasort);
    if (n == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }

    while (n--) {
        printf("%s\n", namelist[n]->d_name);
        free(namelist[n]);
    }
    free(namelist);

    exit(EXIT_SUCCESS);
}