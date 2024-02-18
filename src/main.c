#include <stdio.h>  // flushing stdout instantly
#include <stdint.h> // defined size types
#include <stdlib.h> // for generating random numbers
#include <time.h>   // for using time as random number generator's seed

// Fills a Array `arr` containing `numElems` elements,
// with random numbers in a sorted order (ascending).
void FillArrayWithRandom(uint32_t* arr, uint32_t numElems) {
	srand(time(NULL));
	for (uint32_t i = 0; i < numElems; i++) {
		uint32_t min = i > 0 ? arr[i - 1] : 5;
		uint32_t num = rand() % ((min + 50) + 1 - min) + min;
		arr[i] = num;
	}
}

// Uses Binary Search to find `numToSearch` number inside `arr` Array,
// containing `numElems` elements, and returns non-zero value if it finds
// `numToSearch` in the `arr` and sets the `foundIndex` to that number's index
int BinarySearch(uint32_t* arr, uint32_t numElems, uint32_t numToSearch, uint32_t* foundIndex) {
	uint32_t Left = 0;
	uint32_t Right = numElems - 1;

	while (Left <= Right) {
		uint32_t MidPoint = (Left + Right) / 2;
		if (numToSearch > arr[MidPoint]) {
			Left = MidPoint + 1;
		} else if (numToSearch < arr[MidPoint]) {
			Right = MidPoint - 1;
		} else {
			if (foundIndex != NULL) *foundIndex = MidPoint;
			return 1;
		}
	}

	return 0;
}

int main(void) {
	const uint32_t NumArrLen = 100000000; // 10,00,00,000
	uint32_t* NumArr = malloc(NumArrLen * sizeof(uint32_t));

	printf("Filling Array with %d random numbers... ", NumArrLen);
	fflush(stdout); // Flush text to terminal instantly
	FillArrayWithRandom(NumArr, NumArrLen);
	printf("Done.\n");

	uint32_t index = 0;
	// Select a Number at a Random Index in The Array
	uint32_t numToSearch = NumArr[rand() % ((NumArrLen) + 1 - 1000) + 1000];
	printf("Searching for %d... ", numToSearch);
	fflush(stdout); // Flush text to terminal instantly
	int Result = BinarySearch(NumArr, NumArrLen, numToSearch, &index);
	if (Result != 0) {
		printf("Found at Index %d\n", index);
	} else {
		printf("Not Found\n");
	}

	free(NumArr);
	return 0;
}

