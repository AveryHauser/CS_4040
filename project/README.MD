# Sorting Algorithm Analyzer

This project analyzes the performance of two sorting algorithms: **Insertion Sort** and **Randomized Quicksort**. It runs these algorithms on arrays of various sizes filled with randomized elements and measures their execution time.

The project includes:

- `main.cc`: The primary C++ code for running the sorting algorithms.  
- `sort.cc` & `sort.h`: Implementations of the sorting algorithms.  
- `graphs/graph.py`: Optional Python script for visualizing performance.  
- `output/` & `graphs/*.csv`: Folders for storing results.  
- PDF documentation with infographics.

> **Note:** When visualizing results, both axes in the graphs are logarithmically scaled. Keep this in mind when comparing the plotted results.

---

## 🛠️ How to Build, Run, and Visualize

1. **Compile and run the project**

```bash
g++ -Wall main.cc sort.cc -o sorting_analyzer
./sorting_analyzer
```

Once you run the last command it will ask you which of the sorting algorithms you want to test. Which ever algorithm you choose will print the output to the respective .txt in the `output` folder. 

It will also report the size of the arrays tested the and time that it took to sort. It is recorded in microsends and stored in the respective .csv in the `graph` folder.

## How to Create Graph

To create the graph you need to get into the `graphs` folder. If you want to plot all of the sorting algorthims you will need to test all of the sorting algorithms. You need need to install the requirements which is listed in the requirements.txt. Then you need to use python to run the graph.py.

```
cd graphs
pip install -r requirements.txt
python graph.py
```
