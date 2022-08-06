// All sorts in C
#include <stdio.h>
#include <time.h>

// select sort
void selectSort(int *arr, int n)
{
  int i, j, min, temp;
  for (i = 0; i < n - 1; i++)
  {
    min = i;
    for (j = i + 1; j < n; j++)
    {
      if (arr[j] < arr[min])
      {
        min = j;
      }
    }
    temp = arr[i];
    arr[i] = arr[min];
    arr[min] = temp;
  }
}

// insert sort
void insertSort(int *arr, int n)
{
  int i, j, temp;
  for (i = 1; i < n; i++)
  {
    temp = arr[i];
    for (j = i - 1; j >= 0 && arr[j] > temp; j--)
    {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = temp;
  }
}

// bubble sort
void bubbleSort(int *arr, int n)
{
  int i, j, temp;
  for (i = 0; i < n - 1; i++)
  {
    for (j = 0; j < n - 1 - i; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

// implement merge sort
void mergeSort(int *arr, int n)
{
  int i, j, k, *temp;
  temp = (int *)malloc(sizeof(int) * n);
  for (i = 1; i < n; i *= 2)
  {
    for (j = 0; j < n - i; j += 2 * i)
    {
      for (k = 0; k < i; k++)
      {
        temp[j + k] = arr[j + k];
      }
      for (k = 0; k < i; k++)
      {
        temp[j + k + i] = arr[j + k + i];
      }
      for (k = j; k < j + 2 * i; k++)
      {
        if (temp[k] < temp[k + 1])
        {
          arr[k] = temp[k];
        }
        else
        {
          arr[k] = temp[k + 1];
        }
      }
    }
  }

}

// function to swap elements
void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
int partition(int array[], int low, int high)
{

  // select the rightmost element as pivot
  int pivot = array[high];

  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++)
  {
    if (array[j] <= pivot)
    {

      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;

      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);

  // return the partition point
  return (i + 1);
}

void quickSort(int array[], int low, int high)
{
  if (low < high)
  {

    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);

    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);

    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}

// function to print array elements
void printArray(int array[], int size)
{
  for (int i = 0; i < size; ++i)
  {
    printf("%d  ", array[i]);
  }
  printf("\n");
}

// get array of n random integers
void getRandomArray(int array[], int size)
{
  for (int i = 0; i < size; ++i)
  {
    array[i] = rand() % 100;
  }
}

const ARRAY_SIZE = 100000;

// main function
int main()
{
  int array[100000];
  getRandomArray(array, sizeof(array));

}

// Process sorters and print time taken
void processSorters(int *arr, int n)
{
  clock_t start, end;
  start = clock();
  selectSort(arr, n);
  end = clock();
  printf("Select sort took %f seconds to execute.\n", (double)(end - start) / CLOCKS_PER_SEC);
  start = clock();
  insertSort(arr, n);
  end = clock();
  printf("Insert sort took %f seconds to execute.\n", (double)(end - start) / CLOCKS_PER_SEC);
  start = clock();
  bubbleSort(arr, n);
  end = clock();
  printf("Bubble sort took %f seconds to execute.\n", (double)(end - start) / CLOCKS_PER_SEC);
  start = clock();
  mergeSort(arr, n);
  end = clock();
  printf("Merge sort took %f seconds to execute.\n", (double)(end - start) / CLOCKS_PER_SEC);
  start = clock();
  quickSort(arr, 0, n - 1);
  end = clock();
  printf("Quick sort took %f seconds to execute.\n", (double)(end - start) / CLOCKS_PER_SEC);
}