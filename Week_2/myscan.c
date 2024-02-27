#define _DEFAULT_SOURCE
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
typedef char* STRING;
void Append(STRING* v, STRING x)
{
    STRING tmp = *v;
    int oldLen = tmp == NULL ? 0 : strlen(tmp);
    int newLen = oldLen + strlen(x) + 1;
    tmp = (STRING)realloc(tmp, newLen);
    memset(tmp + oldLen, 0, newLen - oldLen);
    sprintf(tmp + oldLen, "%s", x);
    *v = tmp;
}


void myscan(const char *path, FILE *htmlFile, int level) {
    struct dirent **namelist;
    int n = scandir(path, &namelist, NULL, alphasort); 
    if (n == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        char *name = namelist[i]->d_name;
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
            free(namelist[i]);
            continue;
        }

        char *nextPath = NULL; 
        Append(&nextPath, path);
        Append(&nextPath, "/");
        Append(&nextPath, name);

        for (int j = 0; j < level; j++) {
            fprintf(htmlFile, "&nbsp;&nbsp;&nbsp;&nbsp;");
        }

        if (namelist[i]->d_type == DT_DIR) {
            fprintf(htmlFile, "<b>%s/</b><br>\n", name);
            myscan(nextPath, htmlFile, level + 1); 
        } else {
            fprintf(htmlFile, "<i>%s</i><br>\n", name);
        }

        free(nextPath); 
        free(namelist[i]);
    }

    free(namelist);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *htmlFile = fopen("myscan.html", "w");
    if (!htmlFile) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    fprintf(htmlFile, "<!DOCTYPE html>\n<html>\n<head>\n<title>Directory Listing of %s</title>\n</head>\n<body>\n", argv[1]);
    fprintf(htmlFile, "<h2>Contents of %s</h2>\n", argv[1]);

    myscan(argv[1], htmlFile, 0); 

    fprintf(htmlFile, "</body>\n</html>\n");
    fclose(htmlFile);

    return 0;
}
