#include "sorts.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <algorithm> 
#include <cassert>
#include <string> // Added for string manipulation

using namespace std;

void InitArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand();
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

// --- MODIFIED FUNCTION ---
void ClearFile(char c){
    string filename;
    string plot_filename; // Added for plot file

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

    // Clear output text file
    ofstream file(filename, ios::trunc); 
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << endl;
    }
    file.close();

    // Clear specific plot csv file
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

void CountingSort(int arr[], int n) {
    // Placeholder for counting sort
    // (implementation can be added later)
    // NOTE: Since this is empty, running 'c' will 
    // produce a CSV with very small (near 0) times.
}

// --- MODIFIED FUNCTION ---
void TestSort(int arr[], int n, char choice) {
    // Step 0: Verify correctness
    int* arr_check = new int[n];
    copy(arr, arr + n, arr_check);

    switch (choice) {
        case 'I': InsertionSort(arr_check, n); break;
        case 'Q': RandQuickSort(arr_check, n, 0, n - 1); break;
        case 'C': CountingSort(arr_check, n); break;
    }

    int* arr_sorted = new int[n];
    copy(arr, arr + n, arr_sorted);
    sort(arr_sorted, arr_sorted + n);
    assert(equal(arr_check, arr_check + n, arr_sorted));

    delete[] arr_check;
    delete[] arr_sorted;

    // Step 1: Choose sorting function
    auto sortFunc = (choice == 'I') ? 
        [](int* a, int n){ InsertionSort(a, n); } :
        (choice == 'Q') ?
        [](int* a, int n){ RandQuickSort(a, n, 0, n - 1); } :
        [](int* a, int n){ CountingSort(a, n); };

    // Step 2: Timing
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr, n);
    auto end = chrono::high_resolution_clock::now();

    auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    auto us = chrono::duration_cast<chrono::microseconds>(end - start).count();

    

    // Determine plot filename based on choice
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
    cout << algo << " Sort Size(" << n << "): "
         << ms << " ms, " << us << " μs\n";

    // Write to the specific CSV
    ofstream file(plot_filename, ios::app);
    if (!file.is_open()) {
        cerr << "Error: could not open " << plot_filename << endl;
        return;
    }

    if(us == 0) us = 1;

    file << n << ',' << us << endl; // Write size and time
    file.close();

}