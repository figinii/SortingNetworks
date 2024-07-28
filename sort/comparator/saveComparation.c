#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "saveComparation.h"

#define PATH "./comparatorPrints/"
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

void printComparationToFile(int32 firstIndex, int32 secondIndex, bool swap){

    char fileName[FILE_NAME_LEN];
    fileName[0] = '\0';
    getCompleteFileName(fileName);
    
    char filePath[PATH_LEN] = PATH;

    FILE *f = fopen(strcat(filePath, fileName), "a"); 
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(f, "%d %d %d\n", firstIndex, secondIndex, swap ? 1 : 0);
    fclose(f);
}

// int main(){
//     int32 a = 1;
//     int32 b = 2;

//     printComparationToFile(a, b);

//     return 0;
// }