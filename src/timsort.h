#ifndef _TIMSORT_H_
#define _TIMSORT_H_

#include <stdio.h>

#define LONG 30  // long array
#define SHORT 10 // short array
#define ARR 4    // number of files you want to import

#define ALL 42   // size of total amount of students
#define RUN 32   // used as run size for Timsort
#define EXPO 2   // used for ^2

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

struct student {
  char first_name[LONG];
  char sur_name[LONG];
  int id;
  char course[SHORT];
};

void fill_struct(FILE **file_array, struct student *dt);
void print_list(struct student dt[], int size_array);
void insertion_sort(struct student array[], int left, int right);
void merge(struct student[], int, int, int);
void timsort(struct student[], int size_array);
int binary_search(struct student dt[], int low, int high, char key[]);
void linear_search(struct student dt[], int size);
// void insert(struct student [], int);

#endif // _TIMSORT_H_
