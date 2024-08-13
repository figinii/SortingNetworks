#include "./fileUtils.h"

#define MAX_FILE_PATH_LEN 1024

typedef struct{
    char *filePath;
    time_t timestamp;

}file_with_time;

FILE* openFirstFileInDir(char* dirPath, char* fOpenMode)
{
    struct dirent *entry = NULL;
    DIR *dirPointer = NULL;

    dirPointer = opendir(dirPath);
    if (dirPointer == NULL) {
        perror("opendir - failed to open directory");
        return NULL;
    }

    file_with_time newestFilePath;
    newestFilePath.filePath = NULL;
    newestFilePath.timestamp = 0;

    char* fullPath = malloc(MAX_FILE_PATH_LEN * sizeof(char));
    struct stat fileStat;

    while((entry = readdir(dirPointer)) != NULL){
        if(entry->d_type == DT_REG)
        {   
            snprintf(fullPath, MAX_FILE_PATH_LEN, "%s%s", dirPath, entry->d_name);

            if(stat(fullPath, &fileStat) == -1){
                perror("stat - unable to read file specs");
                return NULL;
            }

            if(fileStat.st_mtime > newestFilePath.timestamp)
            {
                newestFilePath.timestamp = fileStat.st_mtime;
                newestFilePath.filePath = fullPath;
            }
        }
    }

    free(dirPointer);
    free(entry);

    FILE *newestFile = fopen(newestFilePath.filePath, fOpenMode);
    free(newestFilePath.filePath);
    return newestFile;
}

