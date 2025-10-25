
/*Important note: I don't recommend to use
 this code seriosly, this is my very first project
 and it wasn't created for real use. Also
 this code probobly won't work correctly on Windows(TM)*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void ReadDir(DIR* dir,struct dirent* entry) {
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
}

void ScanUserInput(char CurrentDir[30],char OpenedDir[20]) {
    printf("%s/", CurrentDir);
    scanf("%s", OpenedDir);
}

void ClearCurrentUserDir(char CurrentDir[30],char OpenedDir[20]) {
    int x = strlen(CurrentDir)-strlen(OpenedDir)-1;
    while (x != strlen(CurrentDir)) {
        CurrentDir[x] = '\0';
    }
}

void ClearPreviousDir(char CurrentDir[30]) {
    for (int x = strlen(CurrentDir);CurrentDir[x] != '/'; x -= 1) {
        CurrentDir[x] = '\0';
    }
    CurrentDir[strlen(CurrentDir)-1] = '\0';
}

void ReadUserDir(char OpenedDir[20],char CurrentDir[30],DIR* dir,struct dirent* entry) {
    if (strcmp(OpenedDir, ".") == 0 || strcmp(OpenedDir, "/") == 0)  {
        ClearCurrentUserDir(CurrentDir,OpenedDir);
    }

    if (strcmp(OpenedDir, "..") == 0) {
        ClearCurrentUserDir(CurrentDir,OpenedDir);
        ClearPreviousDir(CurrentDir);
    }

    if (dir == NULL) {
        printf("ERROR: Not able to access the directory, sorry\n");
        ClearCurrentUserDir(CurrentDir,OpenedDir);
    } else {
        ReadDir(dir,entry);
    }
}

void CreateAFile(char CurrentDir[],char OpenedDir[]) {
    char File[20];
    char Touch[30] = "touch ";
    printf("The name of the file: ");
    scanf("%s", File);
    strcat(Touch, CurrentDir);
    strcat(Touch, "/");
    strcat(Touch, File);
    printf("%s\n", Touch);
    system(Touch);
    ScanUserInput(CurrentDir,OpenedDir);
}

void nano(char CurrentDir[],char OpenedDir[]) {
    char File[20];
    char nano[30] = "nano ";
    printf("File to open/create with nano: ");
    scanf("%s", File);
    strcat(nano, CurrentDir);
    strcat(nano, "/");
    strcat(nano, File);
    system(nano);
    ScanUserInput(CurrentDir,OpenedDir);
}

void vim(char CurrentDir[],char OpenedDir[]) {
    char File[20];
    char vim[30] = "vim ";
    printf("File to open/create with vim: ");
    scanf("%s", File);
    strcat(vim, CurrentDir);
    strcat(vim, "/");
    strcat(vim, File);
    system(vim);
    ScanUserInput(CurrentDir,OpenedDir);
}

void Execute(char CurrentDir[],char OpenedDir[]) {
    char File[20];
    char Execute[30] = "./";
    printf("File to execute: ");
    scanf("%s", File);
    strcat(Execute, File);
    strcat(Execute, "&");
    chdir(CurrentDir);
    system(Execute);
    ScanUserInput(CurrentDir,OpenedDir);
}

// THE MAIN function
int main () {
    char CurrentDir[30] = "/home";
    char OpenedDir[20];
    DIR *dir;
    struct dirent *entry;
    dir = opendir("/home");

    ReadDir(dir,entry);

    do {

    printf("[&createafile&; &nano/vim&; &exe&]\n");

    ScanUserInput(CurrentDir,OpenedDir);

    if (strcmp(OpenedDir, "&createafile&") == 0) {
        CreateAFile(CurrentDir,OpenedDir);
    } else if (strcmp(CurrentDir, "&nano&") == 0) {
        nano(CurrentDir,OpenedDir);
    } else if (strcmp(OpenedDir, "&vim&") == 0) {
        vim(CurrentDir,OpenedDir);
    } else if (strcmp(OpenedDir, "&exe&") == 0) {
        Execute(CurrentDir,OpenedDir);
    }

    strcat(CurrentDir, "/");
    strcat(CurrentDir, OpenedDir);

    dir = opendir(CurrentDir);

    ReadUserDir(OpenedDir,CurrentDir,dir,entry);

    } while(1);
    return 0; // Returns zero
}
