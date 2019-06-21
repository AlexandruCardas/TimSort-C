/* Description: Program used for importing txt files that include lists of names. It is a modular program
 * (uses functions), in order to sort, display and find student depending on the course and surname.
 * The algorithm used for sorting is Timsort.
 * Author: Alexandru Constantin Cardas
 * Date: 19/04/2018
 * IDE: CLion
 * Compiler: GCC
 * Filename: algorithm.c
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#defines
#define LONG 30//long array
#define SHORT 10//short array
#define ARR 4//number of files you want to import
#define ALL 42//size of total amount of students
#define RUN 32//used as run size for Timsort
#define EXPO 2//used for ^2

//structs
struct student
{
    char firstname[LONG];
    char surname[LONG];
    int ID;
    char course[SHORT];
};

//prototype
void fill_struct(FILE*[], struct student[]);
void print_list(struct student [], int);
void insertion_sort(struct student [], int , int);
void merge(struct student [], int , int , int );
void Timsort(struct student [], int size_array);
int binary_search(struct student [], int, int, char []);
void linear_search(struct student [], int);
void clear();
//void insert(struct student [], int);

int main()
{
    //colour preferences
    system("COLOR F9");

    //declare variables
    int size_array, menu, exit, check, condition;
    char search_key[LONG];
    struct student DT_mix[ALL];

    exit=1;
    condition=1;

    //declare file pointer
    FILE *file_array[ARR];

    //initialising file pointer inside the array; insert extra files addresses here
    file_array[0] = fopen("DT265A.txt", "r");
    file_array[1] = fopen("DT265B.txt", "r");
    file_array[2] = fopen("DT265C.txt", "r");
    file_array[3] = fopen("DT8900.txt", "r");

    //dynamically change size of array by changing the #define
    size_array=sizeof(DT_mix)/sizeof(DT_mix[0]);

    fill_struct(file_array, DT_mix);
    //call functions

    while(exit==1)
    {
        printf("\n====================Menu====================\n");
        printf("1. Sort the list.\n");
        printf("2. Print the list.\n");
        printf("3. Display all full-time students.\n");
        printf("4. Search for a specific student by its surname.\n");
        printf("5. Clear the screen.\n");
        printf("0. Exit!\n");
        scanf("%d", &menu);
        fflush(stdin);

        switch (menu)
        {
            case 1:
            {
                //insert(DT_mix, size_array);
                Timsort(DT_mix, size_array);
                printf("\n\t***Array has been sorted***\n");
                condition=0;
                break;
            }

            case 2:
            {
                print_list(DT_mix, size_array);
                break;
            }

            case 3:
            {
                linear_search(DT_mix, size_array);
                break;
            }

            case 4:
            {
                if(condition==1)
                {
                    printf("\n!!!You must sort the list first!!!\n");
                    break;
                }
                printf("\nEnter the name you want: \n");
                scanf("%s", search_key);
                fflush(stdin);

                check=binary_search(DT_mix, 0, size_array-1, search_key);

                //perform check whether what you looking for is in the list or not
                if(check==-1)
                {
                    printf("Element is not present in the array!\n");
                }
                else
                {
                    printf("\n===Student number: %d===", check+1);
                    printf("\nFirstname: %s\nSurname: %s\nID: %d\nCourse: %s\n", DT_mix[check].firstname,
                               DT_mix[check].surname, DT_mix[check].ID, DT_mix[check].course);
                }//end if..else

                break;
            }

            case 5:
            {
                clear();
                break;
            }

            case 0:
            {
                exit=0;
                printf("\nThank you for using my program.\n");
                break;
            }

            default:
            {
                printf("\n!!!Wrong input!!!\n");
                break;
            }
        }//end switch
    }//end while

    getchar();

    return 0;
}//end main

//function used to fill the array with the txt files provided and assign values to elements inside the struct
void fill_struct(FILE* file_array[], struct student DT[])
{
    int i, j;

    j=0;

    //using fscanf, the program scans a string or numerical value and inserts it into struct until the EOF
    for (i = 0; i < ARR; i++)
    {
        while (fscanf(file_array[i], "%s%s%d%s", DT[j].firstname, DT[j].surname, &DT[j].ID, DT[j].course) !=EOF)
        {
            j++;
        }//end while
    }//end for

    for (int k = 0; k < ARR; k++)
    {
        fclose(file_array[k]);
    }//end for
}//end fx

//function used to print the list of students
void print_list(struct student DT[], int size_array)
{
    for (int i = 0; i < size_array; i++)
    {
        printf("\n===Student number: %d===", i+1);
        printf("\nFirstname: %s\nSurname: %s\nID: %d\nCourse: %s\n", DT[i].firstname, DT[i].surname,
               DT[i].ID, DT[i].course);
    }//end for
}//end fx

//modified insertion sort in order to receive 3 parameters instead of 2
void insertion_sort(struct student array[], int left, int right)
{
    struct student temp;
    for (int i = left + 1; i <= right; i++)
    {
        int j;

        temp=array[i];
        j = i - 1;

        while (strcmp(array[j].surname, temp.surname)>0 && j >= left)
        {
            array[j+1] = array[j];
            j--;
        }//end while

        array[j+1] = temp;
    }//end for
}//end fx

//modified merge in order to accommodate for the left and right side
void merge(struct student array[], int l, int m, int r)
{
    //original array is broken in two parts left and right array
    int size1, size2;

    size1=m-l+1;
    size2=r-m;

    //used for storing array of structs
    struct student left[size1], right[size2];

    for (int i = 0; i < size1; i++)
    {
        left[i] = array[l + i];
    }//end for

    for (int i = 0; i < size2; i++)
    {
        right[i] = array[m + 1 + i];
    }//end for

    int i = 0;
    int j = 0;
    int k = l;

    //after comparing, merge those two arrays in a larger sub array
    while (i < size1 && j < size2)
    {
        if ((strcmp(left[i].surname, right[j].surname))<0||(strcmp(left[i].surname, right[j].surname))==0)
        {
            array[k] = left[i];
            i++;
        }
        else
        {
            array[k] = right[j];
            j++;
        }//end else
        k++;
    } //end while

    // copy remaining elements of left array
    while (i < size1)
    {
        array[k] = left[i];
        k++;
        i++;
    }//end while

    // copy remaining element of right array
    while (j < size2)
    {
        array[k] = right[j];
        k++;
        j++;
    }//end while
}//end fx

/* Iterative Timsort function to sort the array[0...n-1] (similar to merge sort)
 * Minimum run for our code is 32 because this number is 2^5, merge works best with such number.
 * It is a modified merge sort that has insertion sort to deal with small size array, for which insertion is very good.
 * It sort every array that is the size of.
 */
void Timsort(struct student DT_mix[], int size_array)
{
    // Sort individual sub arrays of size RUN
    for (int i = 0; i < size_array; i+=RUN)
    {
        insertion_sort(DT_mix, i, min((i + (RUN-1)), (size_array - 1)));//min used to get the smaller of the 2 values
    }//end for

    // start merging from size of RUN, it will merge to form array sizes ^2 of that such as 64, 128...
    for (int size = RUN; size < size_array; size = EXPO*size)
    {
        /* pick starting point of left sub array,  merge DT_mix[left...left+size-1]
         * and DT_mix[left+size, left+2*size-1], after every merge, we increase left by 2*size*/
        for (int left = 0; left < size_array; left += EXPO*size)
        {
            // find ending point of left sub array, mid+1 is starting point of right sub array
            int mid, right;

            mid=left+ size -1;
            right=min((left + EXPO*size - 1), (size_array-1));//min used to get the smaller of the 2 values

            // merge sub arrays DT_mix[left to mid] & DT_mix[mid+1...right]
            merge(DT_mix, left, mid, right);
        }//end for
    }//end for
}//end fx

//binary search that uses divide and conquer technique to find a value in an already sorted list(case sensitive)
int binary_search(struct student DT[], int low, int high, char key[])
{
    while(low<=high)
    {
        int middle;

        middle=(low+high)/2;

        if(strcmp(key, DT[middle].surname)==0)
        {
            return middle;
        }
        else
        {
            if(strcmp(key, DT[middle].surname)<0)
            {
                high=middle-1;
            }
            if(strcmp(key, DT[middle].surname)>0)
            {
                low=middle+1;
            }
        }//end if...else
    }//end while

    //in case the element is not present
    return -1;
}

//linear search used as there is no need for any sorting, just match the case value (Full-Time) and return the struct
void linear_search(struct student DT[], int size)
{
    char course[SHORT]={"Full-Time"};

    for(int i=0; i<size; i++)
    {
        if(strcmp(DT[i].course,course)==0)
        {
            printf("\n===Student number: %d===", i+1);
            printf("\nFirstname: %s\nSurname: %s\nID: %d\nCourse: %s\n", DT[i].firstname, DT[i].surname,
                   DT[i].ID, DT[i].course);
        }
    }//end for
}//end fx

//used for clearing out the screen using CMD commands
void clear()
{
    system("@cls||clear");
}

/*Raw insertion sort for testing purposes
void insert(struct student DT[], int size)
{
    struct student current;

    for(int i=1; i<size; i++)
    {
        current=DT[i];
        int j=i;

        while(((strcmp(DT[j-1].surname, current.surname))>0) && j>0)
        {
            DT[j]=DT[j-1];
            j=j-1;
        }//end while
        if(j!=i)
        {
            DT[j]=current;
        }
    }//end for
}*/

