import pandas as pd
import matplotlib.pyplot as plt
import os



# Dictionary to hold data
data = {}

# Read each CSV into a DataFrame
for file in files:
    path = os.path.join(folder, file)
    if os.path.exists(path):
        # Each row in CSV is treated as one run
        df = pd.read_csv(path, header=None)
        data[file] = df
    else:
        print(f"Warning: {file} not found!")

# Plot each sorting algorithm
for file, df in data.items():
    plt.figure(figsize=(10,6))
    for idx, row in df.iterrows():
        plt.plot(row, label=f"Run {idx+1}")
    plt.title(file.replace(".csv","").capitalize() + " Performance")
    plt.xlabel("Index")
    plt.ylabel("Value")
    plt.legend()
    plt.grid(True)
    plt.show()
