#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME_LEN 100
#define PATH_LEN FILE_NAME_LEN + 20

#define PATH "./comparatorLists/"
#define FILE_NAME "comparatorList_"

void getCompleteFileName(char* fileName)
{
    strcat(fileName, FILE_NAME);
    time_t currentTime = time(NULL);
    char *timeString = ctime(&currentTime);
    timeString[strlen(timeString)] = '\0';
    strcat(fileName, timeString);
    strcat(fileName, ".txt");  
}

void printComparationToFile(int32 firstIndex, int32 secondIndex){

    char fileName[FILE_NAME_LEN];
    getCompleteFileName(fileName);
    
    char filePath[PATH_LEN] = PATH;

    FILE *f = fopen(strcat(filePath, fileName), "a"); 
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(f, "%d %d\n", firstIndex, secondIndex);
}

int main(){
    int32 a = 1;
    int32 b = 2;

    printComparationToFile(a, b);

    return 0;
}