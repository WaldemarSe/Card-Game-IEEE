#ifndef _FileHandler_h_
#define _FileHandler_h_

#include <dirent.h>

typedef void* FilesInfo;

DIR* Directory_Open(const char* directoryPath);

FilesInfo Directory_ReadFiles(DIR* dir);

char** Directory_GetFileNames(FilesInfo filesInfo);

int Directory_GetNumFiles(FilesInfo filesInfo);

void Directory_FreeFilesInfo(FilesInfo filesInfo);

void Directory_Close(DIR* dir);

#endif