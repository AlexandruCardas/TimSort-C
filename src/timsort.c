/// \file Used for the function itself.
#include "timsort.h"
#include <string.h>

/// \brief Function used to fill the array with the txt files provided and
/// assign values to elements inside the struct.
/// \param file_array
/// \param dt
void fill_struct(FILE **file_array, struct student *dt) {
  int j = 0;

  // using fscanf, the program scans a string or numerical value and inserts it
  // into struct until the EOF
  for (int i = 0; i < ARR; i++) {
    while (fscanf(file_array[i], "%s%s%d%s", dt[j].first_name, dt[j].sur_name,
                  &dt[j].id, dt[j].course) != EOF) {
      j++;
    }
  }

  for (int k = 0; k < ARR; k++) {
    fclose(file_array[k]);
  }
}

/// \brief Function used to print the list of students
/// \param dt
/// \param size_array
void print_list(struct student *dt, int size_array) {
  for (int i = 0; i < size_array; i++) {
    printf("\n===Student number: %d===", i + 1);
    printf("\nFirstname: %s\nSurname: %s\nID: %d\nCourse: %s\n",
           dt[i].first_name, dt[i].sur_name, dt[i].id, dt[i].course);
  }
}

/// \brief Modified insertion sort in order to receive 3 parameters instead of 2
/// \param array
/// \param left
/// \param right
void insertion_sort(struct student *array, int left, int right) {
  struct student temp;

  for (int i = left + 1; i <= right; i++) {
    int j;

    temp = array[i];
    j = i - 1;

    while (strcmp(array[j].sur_name, temp.sur_name) > 0 && j >= left) {
      array[j + 1] = array[j];
      j--;
    }

    array[j + 1] = temp;
  }
}

/// \brief Modified merge in order to accommodate for the left and right side
/// \param array
/// \param l
/// \param m
/// \param r
void merge(struct student array[], int l, int m, int r) {
  // original array is broken in two parts left and right array
  int size_1, size_2;

  size_1 = m - l + 1;
  size_2 = r - m;

  // used for storing array of structs
  struct student left[size_1], right[size_2];

  for (int i = 0; i < size_1; i++) {
    left[i] = array[l + i];
  }

  for (int i = 0; i < size_2; i++) {
    right[i] = array[m + 1 + i];
  }

  int i = 0;
  int j = 0;
  int k = l;

  // after comparing, merge those two arrays in a larger sub array
  while (i < size_1 && j < size_2) {
    if ((strcmp(left[i].sur_name, right[j].sur_name)) < 0 ||
        (strcmp(left[i].sur_name, right[j].sur_name)) == 0) {
      array[k] = left[i];
      i++;
    } else {
      array[k] = right[j];
      j++;
    }
    k++;
  }

  // copy remaining elements of left array
  while (i < size_1) {
    array[k] = left[i];
    k++;
    i++;
  }

  // copy remaining element of right array
  while (j < size_2) {
    array[k] = right[j];
    k++;
    j++;
  }
}

/* Iterative Timsort function to sort the array[0...n-1] (similar to merge sort)
 * Minimum run for our code is 32 because this number is 2^5, merge works best
 * with such number. It is a modified merge sort that has insertion sort to deal
 * with small size array, for which insertion is very good. It sort every array
 * that is the size of.
 */
void timsort(struct student dt_mix[], int size_array) {
  // Sort individual sub arrays of size RUN
  for (int i = 0; i < size_array; i += RUN) {
    insertion_sort(
        dt_mix, i,
        MIN((i + (RUN - 1)),
            (size_array - 1))); // MIN used to get the smaller of the 2 values
  }

  // start merging from size of RUN, it will merge to form array sizes ^2 of
  // that such as 64, 128...
  for (int size = RUN; size < size_array; size = EXPO * size) {
    /* pick starting point of left sub array,  merge dt_mix[left...left+size-1]
     * and dt_mix[left+size, left+2*size-1], after every merge, we increase left
     * by 2*size*/
    for (int left = 0; left < size_array; left += EXPO * size) {
      // find ending point of left sub array, mid+1 is starting point of right
      // sub array
      int mid, right;

      mid = left + size - 1;
      right =
          MIN((left + EXPO * size - 1),
              (size_array - 1)); // MIN used to get the smaller of the 2 values

      // merge sub arrays dt_mix[left to mid] & dt_mix[mid+1...right]
      merge(dt_mix, left, mid, right);
    }
  }
}

// binary search that uses divide and conquer technique to find a value in an
// already sorted list(case sensitive)
int binary_search(struct student *dt, int low, int high, char *key) {
  while (low <= high) {
    int middle;

    middle = (low + high) / 2;

    if (strcmp(key, dt[middle].sur_name) == 0) {
      return middle;
    } else {
      if (strcmp(key, dt[middle].sur_name) < 0) {
        high = middle - 1;
      }
      if (strcmp(key, dt[middle].sur_name) > 0) {
        low = middle + 1;
      }
    }
  }

  // in case the element is not present
  return -1;
}

// linear search used as there is no need for any sorting, just match the case
// value (Full-Time) and return the struct
void linear_search(struct student *dt, int size) {
  char course[SHORT] = {"Full-Time"};

  for (int i = 0; i < size; i++) {
    if (strcmp(dt[i].course, course) == 0) {
      printf("\n===Student number: %d===", i + 1);
      printf("\nFirstname: %s\nSurname: %s\nID: %d\ncourse: %s\n",
             dt[i].first_name, dt[i].sur_name, dt[i].id, dt[i].course);
    }
  }
}

// Raw insertion sort for testing purposes
/*
void insert(struct student Dt[], int Size) {
  struct student Current;

  for (int I = 1; I < Size; I++) {
    Current = Dt[I];
    int J = I;

    while (((strcmp(Dt[J - 1].sur_name, Current.sur_name)) > 0) && J > 0) {
      Dt[J] = Dt[J - 1];
      J = J - 1;
    }
    if (J != I) {
      Dt[J] = Current;
    }
  }
}*/
