#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

FILE* openFirstFileInDir(char* dirPath, char* fOpenMode);