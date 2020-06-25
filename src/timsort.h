#ifndef TIMSORT_C_SRC_TIMSORT_H
#define TIMSORT_C_SRC_TIMSORT_H

#include <stdio.h>

//#defines
#define LONG 30  // long array
#define SHORT 10 // short array
#define ARR 4    // number of files you want to import
#define ALL 42   // size of total amount of students
#define RUN 32   // used as run size for Timsort
#define EXPO 2   // used for ^2

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

// structs
struct student {
  char firstName[LONG];
  char surName[LONG];
  int ID;
  char course[SHORT];
};

// prototype
void fillStruct(FILE *[], struct student[]);
void printList(struct student Dt[], int SizeArray);
void insertionSort(struct student Array[], int Left, int Right);
void merge(struct student[], int, int, int);
void timsort(struct student[], int SizeArray);
int binarySearch(struct student Dt[], int Low, int High, char Key[]);
void linearSearch(struct student Dt[], int Size);
// void insert(struct student [], int);

#endif // TIMSORT_C_SRC_TIMSORT_H
