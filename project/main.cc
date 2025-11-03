#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>   // For std::numeric_limits
#include "sorts.h"  

using namespace std;

int main() {
    int sizes[] = {10, 100, 1000, 2000, 5000, 10000, 20000};
    int arr0[10], arr1[100], arr2[1000], arr3[2000], arr4[5000], arr5[10000], arr6[20000];
    int* arrays[] = {arr0, arr1, arr2, arr3, arr4, arr5, arr6};
    int num_sizes = 7;

    srand(time(0));

    cout << "Please select which sort to test (i = Insertion, q = Quick, c = Counting): ";
    char choice;
    cin >> choice;
    choice = toupper(choice);

    if (choice != 'I' && choice != 'Q' && choice != 'C') {
        cout << "Invalid choice. Please enter i, q, or c.\n";
        return 1;
    }
    
    ClearFile(choice); // Clear the output/plot files

    // Loop through each array size
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int* current_array = arrays[i];

        if (choice == 'C') {
            // --- Milestone 2: Counting Sort Logic ---
            cout << "\n--- Testing n = " << n << " ---" << endl;

            // Per project spec: k = 10
            int k_10 = 10;
            NonCompInitArray(current_array, n, k_10);
            TestSort(current_array, n, k_10, choice);

            // Per project spec: k = n
            int k_n = n;
            NonCompInitArray(current_array, n, k_n);
            TestSort(current_array, n, k_n, choice);

            // Per project spec: k = n^2
            // Use long long to prevent overflow during calculation
            long long k_n2_long = (long long)n * n;
            int k_n2;

            // Cap k at a reasonable max value (e.g., RAND_MAX or int max)
            // to avoid memory errors, as instructed.
            int k_max_limit = std::numeric_limits<int>::max();
            if (k_n2_long > k_max_limit || k_n2_long < 0) {
                k_n2 = k_max_limit;
                cout << "Note: k=n^2 (" << k_n2_long << ") exceeds int max. Capping k at " << k_n2 << endl;
            } else {
                k_n2 = (int)k_n2_long;
            }
            
            // Further cap at RAND_MAX if your rand() % (k+1) logic requires it
            if (k_n2 > RAND_MAX) {
                 k_n2 = RAND_MAX;
                 cout << "Note: Capping k at RAND_MAX (" << k_n2 << ")" << endl;
            }

            NonCompInitArray(current_array, n, k_n2);
            TestSort(current_array, n, k_n2, choice);

        } else {
            // --- Milestone 1: Insertion/Quick Sort Logic ---
            CompInitArray(current_array, n);
            // Pass k=0 as a dummy value, it won't be used
            TestSort(current_array, n, 0, choice); 
        }
    }

    return 0;
}
