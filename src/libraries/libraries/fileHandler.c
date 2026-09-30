#include "fileHandler.h"

#include <stdlib.h>
#include <stdio.h>

#include <utils.h>
#include <delimiters.h>

typedef struct FilesInfoStr{
    DIR* dir;
    int numFiles;
    char** fileNames;
}FilesInfoStr;

DIR* Directory_Open(const char* directoryPath){
    DIR *dir;
    dir = opendir(directoryPath);
    if (dir == NULL) {
        perror("Error opening directory");
        return NULL;
    }

    return dir;
}

static void appendString(char*** array, int* size, const char* string){
    *array = realloc(*array, (*size + 1) * sizeof(char*));

    if(*array == NULL){
        printf("Erro na alocacao dos nomes dos arquivos.");
        exit(1);
    }

    (*array)[*size] = malloc(strlen(string) + 1);
    strcpy((*array)[*size], string);

    (*size) += 1;
}

FilesInfo Directory_ReadFiles(DIR* dir){
    FilesInfoStr* finfo = (FilesInfoStr*)malloc(sizeof(FilesInfoStr));

    char** names = NULL;
    int size = 0;

    int nFiles = 0;

    struct dirent *ent;
    for(int i = 0; (ent = readdir(dir)) != NULL; i++){
        if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0){
            appendString(&names, &size, ent->d_name);
            nFiles += 1;
        }
    }

    finfo->dir = dir;
    finfo->fileNames = names;
    finfo->numFiles = nFiles;

    return finfo;
}

char** Directory_GetFileNames(FilesInfo filesInfo){
    return ((FilesInfoStr*)filesInfo)->fileNames;
}

int Directory_GetNumFiles(FilesInfo filesInfo){
    return ((FilesInfoStr*)filesInfo)->numFiles;
}

void Directory_FreeFilesInfo(FilesInfo filesInfo){
    FilesInfoStr* finfo = (FilesInfoStr*)filesInfo;
    
    for(int i = 0; i < finfo->numFiles; i++){
        free(finfo->fileNames[i]);
    }

    free(finfo);
}

void Directory_Close(DIR* dir){
    closedir(dir);
}