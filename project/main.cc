#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <algorithm> 
#include <cassert>
using namespace std;

//function definitions
void PrintArray(int arr[], int n);
void InsertionSort(int arr[], int n);
int Partition(int arr[], int n, int low, int high);
void RandQuickSort(int arr[], int n, int low, int high);
int RandPartition(int arr[], int n, int low, int high);
void TestQuickSort(int arr[], int n);
void TestInsertionSort(int arr[], int n);

int main(){
    //initalizing array sizes
    int arr0[10];
    int arr1[100];
    int arr2[1000];
    int arr3[2000];
    int arr4[5000];
    int arr5[10000];
    int arr6[20000];

    //generating the random seed
    srand(time(0));

    //tells you to make a choice and records your input
    cout << "Please select which sort you would like to test. i for Insertion Sort. q for Quick Sort." << endl;
    char choice = 0;
    cin >> choice;
    
    //this will run your choice, Insertion sort is the first choice. Randomized quick sort is the second.
    if ((choice = toupper(choice)) == 'I'){
        //all of the following blocks of code are the same until the end of the if statement
        // sets n to the value that is need for the array and then calls the test function
        //if you only want to test a certian size array you will have to comment the other
        //in the if statement section
        int n = 10;
        for (int i = 0; i < n; i++) arr0[i] = rand();
        TestInsertionSort(arr0, n);

        n = 100;
        for (int i = 0; i < n; i++) arr1[i] = rand();
        TestInsertionSort(arr1, n);

        n = 1000;
        for (int i = 0; i < n; i++) arr2[i] = rand();
        TestInsertionSort(arr2, n);

        n = 2000;
        for (int i = 0; i < n; i++) arr3[i] = rand();
        TestInsertionSort(arr3, n);

        n = 5000;
        for (int i = 0; i < n; i++) arr4[i] = rand();
        TestInsertionSort(arr4, n);

        n = 10000;
        for (int i = 0; i < n; i++) arr5[i] = rand();
        TestInsertionSort(arr5, n);

        n = 20000;
        for (int i = 0; i < n; i++) arr6[i] = rand();
        TestInsertionSort(arr6, n);
    }else if ((choice = toupper(choice)) == 'Q'){
        int n = 10;
        for (int i = 0; i < n; i++) arr0[i] = rand();
        TestQuickSort(arr0, n);

        n = 100;
        for (int i = 0; i < n; i++) arr1[i] = rand();
        TestQuickSort(arr1, n);

        n = 1000;
        for (int i = 0; i < n; i++) arr2[i] = rand();
        TestQuickSort(arr2, n);

        n = 2000;
        for (int i = 0; i < n; i++) arr3[i] = rand();
        TestQuickSort(arr3, n);

        n = 5000;
        for (int i = 0; i < n; i++) arr4[i] = rand();
        TestQuickSort(arr4, n);

        n = 10000;
        for (int i = 0; i < n; i++) arr5[i] = rand();
        TestQuickSort(arr5, n);

        n = 20000;
        for (int i = 0; i < n; i++) arr6[i] = rand();
        TestQuickSort(arr6, n);
    }else{cerr << "The choice that you inputed was not vaild please input either i or q" << endl;}

    return 0;
}
void InsertionSort(int arr[], int n){
    for (int i = 1 ; i < n; i++){
        int j = i;

        while (j > 0 && arr[j] < arr[j-1]){
            swap(arr[j-1], arr[j]);
            j--;
        }
    }
}
void RandQuickSort(int arr[], int n, int low, int high){
    if (low < high){
        int q = RandPartition(arr,n,low,high);
        RandQuickSort(arr, n, low, q - 1);
        RandQuickSort(arr, n, q + 1, high);
    }
}
//used so that quick sort will know the next partition in each itereation
int RandPartition(int arr[], int n, int low, int high){
    int i = low + (rand()%(high - low + 1));
    swap(arr[high],arr[i]);
    return Partition(arr, n, low, high);
}
//used to return the randomized partition
int Partition(int arr[], int n, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}
//for testing
void PrintArray(int arr[], int n){
    for (int i = 0; i < n; i++){cout << arr[i] << endl;}
}
void TestInsertionSort(int arr[], int n) {
    // Step 0: Make a copy for correctness check
    int* arr_copy_check = new int[n];
    std::copy(arr, arr + n, arr_copy_check);

    // Sort the copy using your insertion sort
    InsertionSort(arr_copy_check, n);

    // Verify against std::sort
    int* arr_sorted = new int[n];
    std::copy(arr, arr + n, arr_sorted);
    std::sort(arr_sorted, arr_sorted + n);
    assert(std::equal(arr_copy_check, arr_copy_check + n, arr_sorted));

    // Step 1: Timing your sort (optional, keep existing code)
    auto start = std::chrono::high_resolution_clock::now();
    InsertionSort(arr, n);
    auto end = std::chrono::high_resolution_clock::now();

    PrintArray(arr,n);
    auto milliDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto microDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Insertion Sort Size(" << n << "): "
              << milliDuration.count() << " ms, "
              << microDuration.count() << " μs\n";

    delete[] arr_copy_check;
    delete[] arr_sorted;
}
void TestQuickSort(int arr[], int n) {
    // Step 0: Make a copy for correctness check
    int* arr_copy_check = new int[n];
    std::copy(arr, arr + n, arr_copy_check);

    // Sort the copy using your randomized quicksort
    RandQuickSort(arr_copy_check, n, 0, n - 1);

    // Verify against std::sort
    int* arr_sorted = new int[n];
    std::copy(arr, arr + n, arr_sorted);
    std::sort(arr_sorted, arr_sorted + n);
    assert(std::equal(arr_copy_check, arr_copy_check + n, arr_sorted));

    // Step 1: Timing your sort
    auto start = std::chrono::high_resolution_clock::now();
    RandQuickSort(arr, n, 0, n - 1);
    auto end = std::chrono::high_resolution_clock::now();

    PrintArray(arr,n); // remove to see just the time that is required
    auto milliDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto microDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Randomized Quick Sort Size(" << n << "): "
              << milliDuration.count() << " ms, "
              << microDuration.count() << " μs\n";

    delete[] arr_copy_check;
    delete[] arr_sorted;
}
