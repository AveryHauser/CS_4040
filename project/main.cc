#include <iostream>
#include <cstdlib>
#include <ctime>
#include "sorts.h"  

using namespace std;


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

