#include "timsort.h"
#include <string.h>

// function used to fill the array with the txt files provided and assign values
// to elements inside the struct
void fillStruct(FILE *FileArray[], struct student Dt[]) {
  int J = 0;

  // using fscanf, the program scans a string or numerical value and inserts it
  // into struct until the EOF
  for (int I = 0; I < ARR; I++) {
    while (fscanf(FileArray[I], "%s%s%d%s", Dt[J].firstName, Dt[J].surName,
                  &Dt[J].ID, Dt[J].course) != EOF) {
      J++;
    }
  }

  for (int K = 0; K < ARR; K++) {
    fclose(FileArray[K]);
  }
}

// function used to print the list of students
void printList(struct student *Dt, int SizeArray) {
  for (int I = 0; I < SizeArray; I++) {
    printf("\n===Student number: %d===", I + 1);
    printf("\nFirstname: %s\nSurname: %s\nID: %d\nCourse: %s\n",
           Dt[I].firstName, Dt[I].surName, Dt[I].ID, Dt[I].course);
  }
}

// modified insertion sort in order to receive 3 parameters instead of 2
void insertionSort(struct student *Array, int Left, int Right) {
  struct student Temp;
  for (int I = Left + 1; I <= Right; I++) {
    int J;

    Temp = Array[I];
    J = I - 1;

    while (strcmp(Array[J].surName, Temp.surName) > 0 && J >= Left) {
      Array[J + 1] = Array[J];
      J--;
    }

    Array[J + 1] = Temp;
  }
}

// modified merge in order to accommodate for the left and right side
void merge(struct student Array[], int L, int M, int R) {
  // original Array is broken in two parts Left and Right Array
  int Size1, Size2;

  Size1 = M - L + 1;
  Size2 = R - M;

  // used for storing Array of structs
  struct student Left[Size1], Right[Size2];

  for (int I = 0; I < Size1; I++) {
    Left[I] = Array[L + I];
  }

  for (int I = 0; I < Size2; I++) {
    Right[I] = Array[M + 1 + I];
  }

  int I = 0;
  int J = 0;
  int K = L;

  // after comparing, merge those two arrays in a larger sub Array
  while (I < Size1 && J < Size2) {
    if ((strcmp(Left[I].surName, Right[J].surName)) < 0 ||
        (strcmp(Left[I].surName, Right[J].surName)) == 0) {
      Array[K] = Left[I];
      I++;
    } else {
      Array[K] = Right[J];
      J++;
    }
    K++;
  }

  // copy remaining elements of Left Array
  while (I < Size1) {
    Array[K] = Left[I];
    K++;
    I++;
  }

  // copy remaining element of Right Array
  while (J < Size2) {
    Array[K] = Right[J];
    K++;
    J++;
  }
}

/* Iterative Timsort function to sort the array[0...n-1] (similar to merge sort)
 * Minimum run for our code is 32 because this number is 2^5, merge works best
 * with such number. It is a modified merge sort that has insertion sort to deal
 * with small size array, for which insertion is very good. It sort every array
 * that is the size of.
 */
void timsort(struct student DtMix[], int SizeArray) {
  // Sort individual sub arrays of size RUN
  for (int I = 0; I < SizeArray; I += RUN) {
    insertionSort(
        DtMix, I,
        MIN((I + (RUN - 1)),
            (SizeArray - 1))); // MIN used to get the smaller of the 2 values
  }

  // start merging from size of RUN, it will merge to form array sizes ^2 of
  // that such as 64, 128...
  for (int Size = RUN; Size < SizeArray; Size = EXPO * Size) {
    /* pick starting point of left sub array,  merge DtMix[left...left+Size-1]
     * and DtMix[left+Size, left+2*Size-1], after every merge, we increase left
     * by 2*Size*/
    for (int Left = 0; Left < SizeArray; Left += EXPO * Size) {
      // find ending point of Left sub array, Mid+1 is starting point of Right
      // sub array
      int Mid, Right;

      Mid = Left + Size - 1;
      Right =
          MIN((Left + EXPO * Size - 1),
              (SizeArray - 1)); // MIN used to get the smaller of the 2 values

      // merge sub arrays DtMix[Left to Mid] & DtMix[Mid+1...Right]
      merge(DtMix, Left, Mid, Right);
    }
  }
}

// binary search that uses divide and conquer technique to find a value in an
// already sorted list(case sensitive)
int binarySearch(struct student *Dt, int Low, int High, char *Key) {
  while (Low <= High) {
    int Middle;

    Middle = (Low + High) / 2;

    if (strcmp(Key, Dt[Middle].surName) == 0) {
      return Middle;
    } else {
      if (strcmp(Key, Dt[Middle].surName) < 0) {
        High = Middle - 1;
      }
      if (strcmp(Key, Dt[Middle].surName) > 0) {
        Low = Middle + 1;
      }
    }
  }

  // in case the element is not present
  return -1;
}

// linear search used as there is no need for any sorting, just match the case
// value (Full-Time) and return the struct
void linearSearch(struct student *Dt, int Size) {
  char Course[SHORT] = {"Full-Time"};

  for (int I = 0; I < Size; I++) {
    if (strcmp(Dt[I].course, Course) == 0) {
      printf("\n===Student number: %d===", I + 1);
      printf("\nFirstname: %s\nSurname: %s\nID: %d\nCourse: %s\n",
             Dt[I].firstName, Dt[I].surName, Dt[I].ID, Dt[I].course);
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

    while (((strcmp(Dt[J - 1].surName, Current.surName)) > 0) && J > 0) {
      Dt[J] = Dt[J - 1];
      J = J - 1;
    }
    if (J != I) {
      Dt[J] = Current;
    }
  }
}*/
