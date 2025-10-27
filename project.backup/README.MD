This project takes different sized arrays and sorts the randomized elements. The two sorting algorithms being used is randomized quick sort and insertion sort. There is a main.cc which holds all of the code for the project and a pdf with documentation and infographics. 

To build this project run the following commands inside of the brackets.
<g++ -Wall main.cc>

To run the program run the follwing command inside of the brackets.
<./a.out>

You then chose with sorting algorithm you want to run, insertion sort or randomized quick sort. To run insertion sort enter I or i. To run randomized quick sort enter Q or q.

Currently it will print out all sorted elements from all sorted arrays. If you want ot test specific array sizes then you will have to comment out the other arrays that are getting tested. In both of the test function they have the following line of code <assert(std::equal(arr_copy_check, arr_copy_check + n, arr_sorted));>. this insures that the elements are getting sorrted corretly. 