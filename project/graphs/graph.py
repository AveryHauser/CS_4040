import pandas as pd
import matplotlib.pyplot as plt
import os

# --- MODIFIED SCRIPT ---

# Define the folder and files to look for
# Since this script is in 'graphs/', it looks in its current directory ('.')
folder = '.' 
files_to_plot = {
    'Insertion Sort': 'insertion_plot.csv',
    'Quick Sort': 'quick_plot.csv',
    'Counting Sort': 'counting_plot.csv'
}

# Dictionary to hold data
data = {}

# Read each CSV into a DataFrame
for label, file in files_to_plot.items():
    path = os.path.join(folder, file)
    if os.path.exists(path):
        # Read CSV, no header, columns are 'Size' and 'Time'
        df = pd.read_csv(path, header=None, names=['Size', 'Time'])
        if not df.empty:
            data[label] = df
        else:
            print(f"Warning: {file} is empty!")
    else:
        print(f"Warning: {file} not found! Run the C++ program for that sort.")

# Plot all found sorting algorithms on one graph
if data:
    plt.figure(figsize=(12, 7))
    
    for label, df in data.items():
        # Plot Size (X-axis) vs. Time (Y-axis)
        plt.plot(df['Size'], df['Time'], label=label, marker='o')

    plt.title("Sorting Algorithm Performance Comparison")
    plt.xlabel("Input Size (n)")
    plt.ylabel("Time (microseconds μs)")
    plt.legend()
    plt.grid(True)
    plt.xscale('log') # Use log scale for x-axis if sizes vary widely
    plt.yscale('log') # Use log scale for time, as it grows quickly
    plt.show()
else:
    print("No data found to plot. Please run the C++ program to generate CSV files.")