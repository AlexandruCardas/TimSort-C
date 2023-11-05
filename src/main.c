/// \file Program used for importing txt files that include lists of
/// names. It is a modular program (uses functions), in order to sort, display
/// and find student depending on the course and surname. The algorithm used for
/// sorting is Timsort.

#include "timsort.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  // declare variables
  int size_array;
  int menu;
  int exit;
  int check;
  int condition;
  char search_key[LONG];
  struct student dt_mix[ALL];

  exit = 1;
  condition = 1;

  FILE *file_array[ARR];

  // Initialising file pointer inside the array; insert extra files addresses
  // here
  file_array[0] = fopen("DT265A.txt", "r");
  file_array[1] = fopen("DT265B.txt", "r");
  file_array[2] = fopen("DT265C.txt", "r");
  file_array[3] = fopen("DT8900.txt", "r");

  // dynamically change size of array by changing the #define
  size_array = sizeof(dt_mix) / sizeof(dt_mix[0]);

  fill_struct(file_array, dt_mix);

  while (exit == 1) {
    printf("\n====================menu====================\n");
    printf("1. Sort the list.\n");
    printf("2. Print the list.\n");
    printf("3. Display all full-time students.\n");
    printf("4. Search for a specific student by its surname.\n");
    printf("0. exit!\n");
    scanf("%d", &menu);
    fflush(stdin);

    switch (menu) {
    case 1: {
      timsort(dt_mix, size_array);

      printf("\n\t***Array has been sorted***\n");
      condition = 0;

      break;
    }

    case 2: {
      print_list(dt_mix, size_array);

      break;
    }

    case 3: {
      linear_search(dt_mix, size_array);

      break;
    }

    case 4: {
      if (condition == 1) {
        printf("\n!!!You must sort the list first!!!\n");

        break;
      }

      printf("\nEnter the name you want: \n");

      scanf("%10s", search_key);

      fflush(stdin);

      check = binary_search(dt_mix, 0, size_array - 1, search_key);

      // perform check whether what you looking for is in the list or not
      if (check == -1) {
        printf("Element is not present in the array!\n");
      } else {
        printf("\n===Student number: %d===", check + 1);
        printf("\nFirstname: %s\nSurname: %s\nID: %d\nCourse: %s\n",
               dt_mix[check].first_name, dt_mix[check].sur_name,
               dt_mix[check].id, dt_mix[check].course);
      }

      break;
    }

    case 0: {
      exit = 0;
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

  return EXIT_SUCCESS;
}
