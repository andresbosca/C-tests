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


/*
  Dado um vetor v e três inteiros i, m e f, sendo v[i..m] e v[m+1..f] vetores ordenados,
  coloca os elementos destes vetores, em ordem crescente, no vetor em v[i..f].
*/
void merge(int *v, int *c, int i, int m, int f) {
  int z, iv = i, ic = m + 1;

  for (z = i; z <= f; z++) c[z] = v[z];

  z = i;

  while (iv <= m && ic <= f) {
    /* Invariante: v[i..z] possui os valores de v[iv..m] e v[ic..f] em ordem crescente. */

    if (c[iv] <= c[ic]) v[z++] = c[iv++];
    else v[z++] = c[ic++];
  }

  while (iv <= m) v[z++] = c[iv++];

  while (ic <= f) v[z++] = c[ic++];
}

/*
  Dado um vetor de inteiros v e dois inteiros i e f, ordena o vetor v[i..f] em ordem crescente.
  O vetor c é utilizado internamente durante a ordenação.
*/
void sort(int *v, int *c, int i, int f) {
  if (i >= f) return;

  int m = (i + f) / 2;

  sort(v, c, i, m);
  sort(v, c, m + 1, f);

  /* Se v[m] <= v[m + 1], então v[i..f] já está ordenado. */
  if (v[m] <= v[m + 1]) return;

  merge(v, c, i, m, f);
}


// merge sort
/*
  Dado um vetor de inteiros v e um inteiro n >= 0, ordena o vetor v[0..n-1] em ordem crescente.
*/
void mergesort(int *v, int n) {
  int *c = (int *) malloc(sizeof(int) * n);
  sort(v, c, 0, n - 1);
  free(c);
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
void getRandomArray(int *arr, int n)
{
  srand(time(NULL));
  for (int i = 0; i < n; i++)
  {
    int r = rand() % n;
    arr[i] = r;

  }
}

// Process sorters and print time taken
void processSorters(int *arr2, int n)
{
  clock_t start, end;
 
  getRandomArray(arr2, n);
 
  start = clock();
  selectSort(arr2, n);
  end = clock();
  printf("Select sort took %f seconds to execute.\n", (double)(end - start) / CLOCKS_PER_SEC);
  
  getRandomArray(arr2, n);
  start = clock();
  insertSort(arr2, n);
  end = clock();
  printf("Insert sort took %f seconds to execute.\n", (double)(end - start) / CLOCKS_PER_SEC);
  
  getRandomArray(arr2, n);
  start = clock();
  bubbleSort(arr2, n);
  end = clock();
  printf("Bubble sort took %f seconds to execute.\n", (double)(end - start) / CLOCKS_PER_SEC);
  
  getRandomArray(arr2, n);
  start = clock();
  mergesort(arr2, n);
  end = clock();
  printf("Merge sort took %f seconds to execute.\n", (double)(end - start) / CLOCKS_PER_SEC);
  
  getRandomArray(arr2, n);
  start = clock();
  quickSort(arr2, 0, n - 1);
  end = clock();
  printf("Quick sort took %f seconds to execute.\n", (double)(end - start) / CLOCKS_PER_SEC);
}
const ARRAY_SIZE = 1000000;

// main function
int main()
{
  int array[1000000];
  int size = ARRAY_SIZE;
  processSorters(array, size);
  return 0;
}
