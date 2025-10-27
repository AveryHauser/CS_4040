#include <iomanip>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <algorithm> 
#include <cassert>

using namespace std;

// Function definitions
void InitArray(int arr[], int n);
void PrintArray(int arr[], int n, char c);
void InsertionSort(int arr[], int n);
int Partition(int arr[], int n, int low, int high);
void RandQuickSort(int arr[], int n, int low, int high);
int RandPartition(int arr[], int n, int low, int high);
void TestSort(int arr[], int n, char choice);
void CountingSort(int arr[], int n);
void ClearFile(char c);

int main() {
    int sizes[] = {10, 100, 1000, 2000, 5000, 10000, 20000};
    int arr0[10], arr1[100], arr2[1000], arr3[2000], arr4[5000], arr5[10000], arr6[20000];
    int* arrays[] = {arr0, arr1, arr2, arr3, arr4, arr5, arr6};

    srand(time(0));

    cout << "Please select which sort to test (i = Insertion, q = Quick, c = Counting): ";
    char choice;
    cin >> choice;
    choice = toupper(choice);

    if (choice != 'I' && choice != 'Q' && choice != 'C') {
        cout << "Invalid choice. Please enter i, q, or c.\n";
        return 1;
    }
    
    ClearFile(choice);
    for (int i = 0; i < 7; i++) {
        InitArray(arrays[i], sizes[i]);
        TestSort(arrays[i], sizes[i], choice);
    }

    return 0;
}

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
void ClearFile(char c){
    string filename;
    switch (toupper(c)) {
        case 'I': filename = "output/insertionsort.txt"; break;
        case 'Q': filename = "output/quicksort.txt"; break;
        case 'C': filename = "output/countingsort.txt"; break;
        default:
            cerr << "Invalid sort type. Nothing written.\n";
            return;
    }

    ofstream file(filename,ios::trunc); // append instead of overwrite
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << endl;
        return;
    }
    file.close();

    ofstream plot("graphs/plot.csv",ios::trunc);
    if (!plot.is_open()) {
        cerr << "Error: could not open " << "plot.csv" << endl;
        return;
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

    ofstream file(filename, ios::app); // append instead of overwrite
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
}

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

    ofstream file("graphs/plot.csv", ios::app);
    if (!file.is_open()) {
        cerr << "Error: could not open plot.csv" << endl;
        return;
    }

    file << n << ',' << us << endl;
    file.close();

    // Step 3: Output
    string algo = (choice == 'I') ? "Insertion" :
                  (choice == 'Q') ? "Randomized Quick" : "Counting";

    cout << algo << " Sort Size(" << n << "): "
         << ms << " ms, " << us << " μs\n";
}
