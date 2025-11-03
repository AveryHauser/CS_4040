#ifndef SORTS_H
#define SORTS_H

// --- NEW ---
// Initializes for comparison-based sorts (Insertion, Quick)
void CompInitArray(int arr[], int n);

// --- NEW ---
// Initializes for non-comparison-based sorts (Counting)
// Generates random numbers in the range [0, k]
void NonCompInitArray(int arr[], int n, int k);

void PrintArray(int arr[], int n, char c);
void InsertionSort(int arr[], int n);
int Partition(int arr[], int n, int low, int high);
void RandQuickSort(int arr[], int n, int low, int high);
int RandPartition(int arr[], int n, int low, int high);

// --- MODIFIED ---
// Now accepts 'k' to pass to CountingSort
void TestSort(int arr[], int n, int k, char choice);

// --- MODIFIED ---
// Now accepts 'k' as the max value
void CountingSort(int arr[], int n, int k);

void ClearFile(char c);

// Remove the old InitArray declaration if it's still here
// void InitArray(int arr[], int n); // <-- DELETE THIS

#endif
