#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static inline void ProfilerStart();
static inline double ProfilerEnd();

static inline void UpdateSeed();
static inline uint32_t RandNum(uint32_t min, uint32_t max);

void FillWithRandom(uint32_t* arr, uint32_t numElems);

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
	ProfilerStart();

	FillWithRandom(NumArr, NumArrLen);

	double TimeTookToFill = ProfilerEnd();
	printf("Done. Took %.2fms\n", TimeTookToFill);

	uint32_t index = 0;
	// Select a Number at a Random Index in The Array
	uint32_t numToSearch = NumArr[RandNum(10, 10000)];
	printf("Searching for %d... ", numToSearch);
	fflush(stdout); // Flush text to terminal instantly
	ProfilerStart();

	int Result = BinarySearch(NumArr, NumArrLen, numToSearch, &index);

	double TimeTookToSearch = ProfilerEnd();
	if (Result != 0) {
		printf("Found at Index %d, Took %.2fms\n", index, TimeTookToSearch);
	} else {
		printf("Not Found, Took %.2fms\n", TimeTookToSearch);
	}

	free(NumArr);
	return 0;
}

#include <time.h>   // for using time as random number generator's seed

clock_t __clockTimeRecorded = 0;
static inline void ProfilerStart() {
	__clockTimeRecorded = clock();
}

static inline double ProfilerEnd() {
	return ((double)(clock() - __clockTimeRecorded)/CLOCKS_PER_SEC) * 1000;
}

static inline void UpdateSeed() {
	srand(time(NULL));
}

static inline uint32_t RandNum(uint32_t min, uint32_t max) {
	return rand() % (max + 1 - min) + min;
}

// Fills with random number but in ascending order
void FillWithRandom(uint32_t* arr, uint32_t numElems) {
	UpdateSeed();
	for (uint32_t i = 0; i < numElems; i++) {
		uint32_t min = i > 0 ? arr[i - 1] : 5;
		uint32_t num = RandNum(min, min + 50);
		arr[i] = num;
	}
}

