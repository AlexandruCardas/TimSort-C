/* Description: Program used for importing txt files that include lists of
 * names. It is a modular program (uses functions), in order to sort, display
 * and find student depending on the course and surname. The algorithm used for
 * sorting is Timsort. Author: Alexandru Constantin Cardas Date: 19/04/2018 IDE:
 * CLion Compiler: GCC Filename: algorithm.c
 */

#include "timsort.h"
#include <stdio.h>

int main() {
  // declare variables
  int SizeArray, Menu, Exit, Check, Condition;
  char SearchKey[LONG];
  struct student DtMix[ALL];

  Exit = 1;
  Condition = 1;

  // declare file pointer
  FILE *FileArray[ARR];

  // initialising file pointer inside the array; insert extra files addresses
  // here
  FileArray[0] = fopen("DT265A.txt", "r");
  FileArray[1] = fopen("DT265B.txt", "r");
  FileArray[2] = fopen("DT265C.txt", "r");
  FileArray[3] = fopen("DT8900.txt", "r");

  // dynamically change size of array by changing the #define
  SizeArray = sizeof(DtMix) / sizeof(DtMix[0]);

  fillStruct(FileArray, DtMix);
  // call functions

  while (Exit == 1) {
    printf("\n====================Menu====================\n");
    printf("1. Sort the list.\n");
    printf("2. Print the list.\n");
    printf("3. Display all full-time students.\n");
    printf("4. Search for a specific student by its surname.\n");
    printf("0. Exit!\n");
    scanf("%d", &Menu);
    fflush(stdin);

    switch (Menu) {
    case 1: {
      // insert(DtMix, SizeArray);
      timsort(DtMix, SizeArray);
      printf("\n\t***Array has been sorted***\n");
      Condition = 0;
      break;
    }

    case 2: {
      printList(DtMix, SizeArray);
      break;
    }

    case 3: {
      linearSearch(DtMix, SizeArray);
      break;
    }

    case 4: {
      if (Condition == 1) {
        printf("\n!!!You must sort the list first!!!\n");
        break;
      }
      printf("\nEnter the name you want: \n");
      scanf("%s", SearchKey);
      fflush(stdin);

      Check = binarySearch(DtMix, 0, SizeArray - 1, SearchKey);

      // perform check whether what you looking for is in the list or not
      if (Check == -1) {
        printf("Element is not present in the array!\n");
      } else {
        printf("\n===Student number: %d===", Check + 1);
        printf("\nFirstname: %s\nSurname: %s\nID: %d\nCourse: %s\n",
               DtMix[Check].firstName, DtMix[Check].surName, DtMix[Check].ID,
               DtMix[Check].course);
      }

      break;
    }

    case 0: {
      Exit = 0;
      printf("\nThank you for using my program.\n");
      break;
    }

    default: {
      printf("\n!!!Wrong input!!!\n");
      break;
    }
    }
  }

  getchar();

  return 0;
}