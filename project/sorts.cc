#include "sorts.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <algorithm> 
#include <cassert>
#include <string>
#include <vector> // Needed for CountingSort

using namespace std;

// --- NEW IMPLEMENTATION ---
// For Milestone 1: Insertion Sort, Quicksort
// Generates large random numbers
void CompInitArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand();
}

// --- NEW IMPLEMENTATION (Corrected) ---
// For Milestone 2: Counting Sort
// Generates numbers in the specific range [0, k]
void NonCompInitArray(int arr[], int n, int k) {
    if (k < 0) k = 0; // Safety check
    for (int i = 0; i < n; i++) {
        // Use (k + 1) to get the range [0, k] inclusive
        arr[i] = rand() % (k + 1);
    }
}

void InsertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 && arr[j] < arr[j - 1]) {
            swap(arr[j], arr[j - 1]);
            j--;
        }
    }
}

void RandQuickSort(int arr[], int n, int low, int high) {
    if (low < high) {
        int q = RandPartition(arr, n, low, high);
        RandQuickSort(arr, n, low, q - 1);
        RandQuickSort(arr, n, q + 1, high);
    }
}

int RandPartition(int arr[], int n, int low, int high) {
    int i = low + (rand() % (high - low + 1));
    swap(arr[high], arr[i]);
    return Partition(arr, n, low, high);
}

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

void ClearFile(char c){
    string filename;
    string plot_filename;

    switch (toupper(c)) {
        case 'I': 
            filename = "output/insertionsort.txt"; 
            plot_filename = "graphs/insertion_plot.csv";
            break;
        case 'Q': 
            filename = "output/quicksort.txt"; 
            plot_filename = "graphs/quick_plot.csv";
            break;
        case 'C': 
            filename = "output/countingsort.txt"; 
            plot_filename = "graphs/counting_plot.csv";
            break;
        default:
            cerr << "Invalid sort type. Nothing written.\n";
            return;
    }

    ofstream file(filename, ios::trunc); 
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << endl;
    }
    file.close();

    ofstream plot(plot_filename, ios::trunc);
    if (!plot.is_open()) {
        cerr << "Error: could not open " << plot_filename << endl;
    }
    plot.close();
}

void PrintArray(int arr[], int n, char c) {
    string filename;
    switch (toupper(c)) {
        case 'I': filename = "output/insertionsort.txt"; break;
        case 'Q': filename = "output/quicksort.txt"; break;
        case 'C': filename = "output/countingsort.txt"; break;
        default:
            cerr << "Invalid sort type. Nothing written.\n";
            return;
    }

    ofstream file(filename, ios::app); 
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << endl;
        return;
    }

    for (int i = 0; i < n; i++)
        file << arr[i] << endl;
    file << endl;
    file.close();
}

// --- NEW IMPLEMENTATION (From previous step) ---
void CountingSort(int arr[], int n, int k) {
    if (n <= 0) return;
    if (k < 0) return; // k cannot be negative

    // Step 1: Create a counting array C of size k + 1
    std::vector<int> C(k + 1, 0);
    std::vector<int> B(n); // Output array

    // Step 2: Store the count of each element
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0 && arr[i] <= k) {
            C[arr[i]]++;
        }
        // Handle values outside the [0, k] range if necessary,
        // or assume valid input per project spec.
    }

    // Step 3: Store cumulative counts
    for (int i = 1; i <= k; i++) {
        C[i] += C[i - 1];
    }

    // Step 4 & 5: Build the output array B (stable)
    for (int i = n - 1; i >= 0; i--) {
        if (arr[i] >= 0 && arr[i] <= k) {
            B[C[arr[i]] - 1] = arr[i];
            C[arr[i]]--;
        }
    }

    // Step 6: Copy B back to arr
    for (int i = 0; i < n; i++) {
        arr[i] = B[i];
    }
}

// --- MODIFIED FUNCTION ---
// Now accepts 'k' to pass to CountingSort
void TestSort(int arr[], int n, int k, char choice) {
    // Step 0: Verify correctness
    int* arr_check = new int[n];
    copy(arr, arr + n, arr_check);

    switch (choice) {
        case 'I': InsertionSort(arr_check, n); break;
        case 'Q': RandQuickSort(arr_check, n, 0, n - 1); break;
        case 'C': CountingSort(arr_check, n, k); break; // Pass k
    }

    int* arr_sorted = new int[n];
    copy(arr, arr + n, arr_sorted);
    sort(arr_sorted, arr_sorted + n);
    
    // Using a loop for clearer assertion failure output
    for(int i = 0; i < n; ++i) {
        if (arr_check[i] != arr_sorted[i]) {
            cerr << "Sort FAILED for n=" << n << " k=" << k << " at index " << i << endl;
            cerr << "Expected " << arr_sorted[i] << " but got " << arr_check[i] << endl;
            assert(false); // Fail the program
        }
    }
    
    delete[] arr_check;
    delete[] arr_sorted;

    // Step 1: Choose sorting function (lambda now accepts k)
    auto sortFunc = (choice == 'I') ? 
        [](int* a, int n, int k_val){ InsertionSort(a, n); } :
        (choice == 'Q') ?
        [](int* a, int n, int k_val){ RandQuickSort(a, n, 0, n - 1); } :
        [](int* a, int n, int k_val){ CountingSort(a, n, k_val); };

    // Step 2: Timing
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr, n, k); // Pass k to the lambda
    auto end = chrono::high_resolution_clock::now();

    auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    auto us = chrono::duration_cast<chrono::microseconds>(end - start).count();

    string plot_filename;
    string algo;
    switch (choice) {
        case 'I': 
            plot_filename = "graphs/insertion_plot.csv"; 
            algo = "Insertion";
            break;
        case 'Q': 
            plot_filename = "graphs/quick_plot.csv"; 
            algo = "Randomized Quick";
            break;
        case 'C': 
            plot_filename = "graphs/counting_plot.csv"; 
            algo = "Counting";
            break;
    }

    PrintArray(arr, n, choice);
    
    // Step 3: Output to console
    // For Counting Sort, also print the 'k' value
    if (choice == 'C') {
        cout << algo << " Sort Size(" << n << "), k(" << k << "): "
             << ms << " ms, " << us << " μs\n";
    } else {
        cout << algo << " Sort Size(" << n << "): "
             << ms << " ms, " << us << " μs\n";
    }

    ofstream file(plot_filename, ios::app);
    if (!file.is_open()) {
        cerr << "Error: could not open " << plot_filename << endl;
        return;
    }

    if(us == 0) us = 1; // Avoid divide by zero or log(0) in plots

    // For Counting Sort, we need to log 'k' in the CSV
    // We'll add it as a new column: n,k,time
    if (choice == 'C') {
        file << n << ',' << k << ',' << us << endl;
    } else {
        file << n << ',' << us << endl; // Old format for MS1
    }
    file.close();
}
