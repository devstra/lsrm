#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

static void listFilesRecursively(char * basePath, const char * searchTerm) {
    char path[1000];
    struct dirent * dp;
    DIR * dir = opendir(basePath);

    // Unable to open directory stream
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp -> d_name, ".") != 0 && strcmp(dp -> d_name, "..") != 0) {
            if (strcasestr(dp->d_name, searchTerm)) {
                printf("%s/%s\n",basePath,dp->d_name);
//printf("\"%s/%s\"\n", fpath, fname);
                listFilesRecursively(path, searchTerm);
            } else {
                // Construct new path from our base path
                strcpy(path, basePath);
                strcat(path, "/");
                strcat(path, dp -> d_name);

                listFilesRecursively(path, searchTerm);
            }
        }
    }

    closedir(dir);
}


int main(int argc, const char * argv[]) {
    char * home = getenv("HOME");

    if (argc == 2) {
        listFilesRecursively(home, argv[1]);
    } else {
        printf("Please provide one argument");
    }
    return 0;
}
