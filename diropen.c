
/*Important note: I don't recommend to use
 this code seriosly, this is my very first project
 and it wasn't created for real use. Also
 this code probobly won't work correctly on Windows(TM)*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char CurrentDir[30] = "/";
char OpenedDir[20];
DIR *dir;
struct dirent *entry;

void ReadDir() {
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
}

void ScanUserInput() {
    if (strcmp(CurrentDir, "/") == 0) {
        printf("%s", CurrentDir);
    } else {
        printf("%s/", CurrentDir);
    }
    scanf("%s", OpenedDir);
}

void ClearCurrentDir() {
    int x = strlen(CurrentDir)-strlen(OpenedDir)-1;
    while (x != strlen(CurrentDir)) {
        CurrentDir[x] = '\0';
    }
}

void ClearPreviousDir() {
    for (int x = strlen(CurrentDir);CurrentDir[x] != '/'; x -= 1) {
        CurrentDir[x] = '\0';
    }
    CurrentDir[strlen(CurrentDir)-1] = '\0';
}

void ReadUserDir() {
    if (strcmp(OpenedDir, ".") == 0 || strcmp(OpenedDir, "/") == 0)  {
        ClearCurrentDir();
    }

    if (strcmp(OpenedDir, "..") == 0) {
        ClearCurrentDir();
        ClearPreviousDir();
    }

    if (dir == NULL) {
        printf("ERROR: Not able to access the directory, sorry\n");
        ClearCurrentDir();
    } else {
        ReadDir();
    }
}

void CreateAFile() {
    char File[20];
    char Touch[30] = "touch ";
    printf("The name of the file: ");
    scanf("%s", File);
    strcat(Touch, CurrentDir);
    strcat(Touch, "/");
    strcat(Touch, File);
    printf("%s\n", Touch);
    system(Touch);
    ScanUserInput();
}

void nano() {
    char File[20];
    char nano[30] = "nano ";
    printf("File to open/create with nano: ");
    scanf("%s", File);
    strcat(nano, CurrentDir);
    strcat(nano, "/");
    strcat(nano, File);
    system(nano);
    ScanUserInput();
}

void vim() {
    char File[20];
    char vim[30] = "vim ";
    printf("File to open/create with vim: ");
    scanf("%s", File);
    strcat(vim, CurrentDir);
    strcat(vim, "/");
    strcat(vim, File);
    system(vim);
    ScanUserInput();
}

void Execute() {
    char File[20];
    char Execute[30] = "./";
    printf("File to execute: ");
    scanf("%s", File);
    strcat(Execute, File);
    strcat(Execute, " > /dev/null & disown");
    chdir(CurrentDir);
    system(Execute);
    ScanUserInput();
}

// THE MAIN function
int main (int argc, char* argv[]) {
    if (argc > 2) {
        printf("ERROR: Too many arguments\n");
        return -1;
    }
    if (argv[1] != NULL) {
        strcpy(CurrentDir,argv[1]);
    }
    dir = opendir(CurrentDir);

    ReadDir();

    do {

    printf("[&createafile&; &nano/vim&; &exe&, &exit&]\n");

    ScanUserInput();

    if (strcmp(OpenedDir, "&createafile&") == 0) {
        CreateAFile();
    } else if (strcmp(CurrentDir, "&nano&") == 0) {
        nano();
    } else if (strcmp(OpenedDir, "&vim&") == 0) {
        vim();
    } else if (strcmp(OpenedDir, "&exe&") == 0) {
        Execute();
    } else if (strcmp(OpenedDir, "&exit&") == 0)
        break;

    if (strcmp(CurrentDir, "/") != 0) {
        strcat(CurrentDir, "/");
    }
    strcat(CurrentDir, OpenedDir);

    dir = opendir(CurrentDir);

    ReadUserDir();

    } while(1);
    closedir(dir);
    return 0; // Returns zero
}
