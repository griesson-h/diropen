
/*Important note: I don't recommend to use
 this code seriosly, this is my very first project
 and it wasn't created for real use. Also
 this code probobly won't work correctly on Windows(TM)*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void clearcurrentuserdir(char CurrentDir[30],char thedir[20]) {
    int x = strlen(CurrentDir)-strlen(thedir)-1;
    while (x != strlen(CurrentDir)) {
        CurrentDir[x] = '\0';
    }
}

void clearpreviousdir(char CurrentDir[30]) {
    for (int x = strlen(CurrentDir);CurrentDir[x] != '/'; x -= 1) {
        CurrentDir[x] = '\0';
    }
    CurrentDir[strlen(CurrentDir)-1] = '\0';
}

void readuserdir(char thedir[20],char CurrentDir[30],DIR* dir,struct dirent* entry) {
    if (strcmp(thedir, ".") == 0 || strcmp(thedir, "/") == 0)  {
        clearcurrentuserdir(CurrentDir,thedir);
    }

    if (strcmp(thedir, "..") == 0) {
        clearcurrentuserdir(CurrentDir,thedir);
        clearpreviousdir(CurrentDir);
    }

    if (dir == NULL) {
        printf("ERROR: Not able to access the directory, sorry\n");
        clearcurrentuserdir(CurrentDir,thedir);
    } else {
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }
    }
}

void createafile(char CurrentDir[],char dir2[]) {
    char ufile[20];
    printf("The name of the file: ");
    scanf("%s", ufile);
    char cmd2[30] = "touch ";
    strcat(cmd2, CurrentDir);
    strcat(cmd2, "/");
    strcat(cmd2, ufile);
    printf("%s\n", cmd2);
    system(cmd2);
    printf("%s/", CurrentDir);
    scanf("%s", dir2);
}

void nano(char CurrentDir[],char dir2[]) {
    char nanor[20];
    printf("File to open/create with nano: ");
    scanf("%s", nanor);
    char cmd3[30] = "nano ";
    strcat(cmd3, CurrentDir);
    strcat(cmd3, "/");
    strcat(cmd3, nanor);
    system(cmd3);
    printf("%s/", CurrentDir);
    scanf("%s", dir2);
}

void vim(char dir1[],char dir2[]) {
    char vimr[20];
    printf("File to open/create with vim: ");
    scanf("%s", vimr);
    char cmd4[30] = "vim ";
    strcat(cmd4, dir1);
    strcat(cmd4, "/");
    strcat(cmd4, vimr);
    system(cmd4);
    printf("%s/", dir1);
    scanf("%s", dir2);
}

void exe(char dir1[],char dir2[]) {
    char uexe[20];
    printf("File to execute: ");
    scanf("%s", uexe);
    char cmd5[30] = "./";
    strcat(cmd5, uexe);
    strcat(cmd5, " > /dev/null & disown");
    chdir(dir1);
    system(cmd5);
    printf("%s/", dir1);
    scanf("%s", dir2);
}

// THE MAIN function
int main () {

    DIR *dir;
    struct dirent *entry;
    dir = opendir("/home");

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    char CurrentDir[30] = "/home";
    char thedir[20];
    do {

    printf("[&createafile&; &nano/vim&; &exe&]\n");

    printf("%s/", CurrentDir);
    scanf("%s", thedir);

    if (strcmp(thedir, "&createafile&") == 0) {
        createafile(CurrentDir,thedir);
    } else if (strcmp(CurrentDir, "&nano&") == 0) {
        nano(CurrentDir,thedir);
    } else if (strcmp(thedir, "&vim&") == 0) {
        vim(CurrentDir,thedir);
    } else if (strcmp(thedir, "&exe&") == 0) {
        exe(CurrentDir,thedir);
    }

    strcat(CurrentDir, "/");
    strcat(CurrentDir, thedir);

    dir = opendir(CurrentDir);

    readuserdir(thedir,CurrentDir,dir,entry);

    } while(1);
    return 0; // Returns zero
}
