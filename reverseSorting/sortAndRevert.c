#include <stdio.h>
#include "../utils/arrayUtils.h"
#include "../sort/comparator/compare.h"
#include "../sort/sort.h"
#include "../utils/comparatorList.h"
#include "../utils/fileUtils.h"
#include "../utils/configs.h"

#define Dlong int64_t
#define int32 int32_t

int main()
{
  	Dlong length;
  	char c;
	int32* arr;
	int32* originalArr;

	printf("max arr Length? ");
  	scanf("%lld", &length);

	arr = generate_random_array(length, &length, false);
	printArray(arr, length);
	originalArr = copyArray(arr, length);
  	mergExchange(arr, length, compareAndSave);
  	printArray(arr, length);

	FILE *file = openFirstFileInDir(PATH, "r");
	if(file == NULL)
	{
		perror("openFirstFileInDir - unable to open file");
		return 1;
	}

	comparatorList *head = buildComparatorListFromFile(file);
	comparatorList *last = NULL;

	// for(comparatorList *current = head; current != NULL; current = current->next){
    //     printf("%d %d %d\n", current->comparator->firstIndex, current->comparator->secondIndex, current->comparator->swap);
    // }

	for(last = head; last->next != NULL; last = last->next);
	for(comparatorList* current = last; current != NULL; current = current->prev){
		
		// printf("%d %d %d\n", current->comparator->firstIndex, current->comparator->secondIndex, current->comparator->swap);

		if(current->comparator->swap)
		{
			int32 tmp = arr[current->comparator->firstIndex];
			arr[current->comparator->firstIndex] = arr[current->comparator->secondIndex];
			arr[current->comparator->secondIndex] = tmp;	
		}
	}

	printArray(arr, length);

	printf("revert %s\n", areEqual(arr, originalArr, length) ? "success" : "fail");

	free(file);
	freeList(head);

  	return 0;
}