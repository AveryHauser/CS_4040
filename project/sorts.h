#ifndef SORTS_H  // These are "include guards"
#define SORTS_H  // They prevent the file from being included multiple times

void InitArray(int arr[], int n);
void PrintArray(int arr[], int n, char c);
void InsertionSort(int arr[], int n);
int Partition(int arr[], int n, int low, int high);
void RandQuickSort(int arr[], int n, int low, int high);
int RandPartition(int arr[], int n, int low, int high);
void TestSort(int arr[], int n, char choice);
void CountingSort(int arr[], int n);
void ClearFile(char c);

#endif