import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# --- Your Median Runtime Data (in milliseconds) ---
# This data is the calculated median from the 5 test runs
# you provided in the previous step.
data = [
    {'n': 10, 'k': 10, 'median_time_ms': 0.002},
    {'n': 10, 'k': 10, 'median_time_ms': 0.001}, # k=n
    {'n': 10, 'k': 100, 'median_time_ms': 0.003}, # k=n^2
    
    {'n': 100, 'k': 10, 'median_time_ms': 0.008},
    {'n': 100, 'k': 100, 'median_time_ms': 0.009}, # k=n
    {'n': 100, 'k': 10000, 'median_time_ms': 0.365}, # k=n^2
    
    {'n': 1000, 'k': 10, 'median_time_ms': 0.054},
    {'n': 1000, 'k': 1000, 'median_time_ms': 0.081}, # k=n
    {'n': 1000, 'k': 1000000, 'median_time_ms': 14.815}, # k=n^2
    
    {'n': 2000, 'k': 10, 'median_time_ms': 0.048},
    {'n': 2000, 'k': 2000, 'median_time_ms': 0.065}, # k=n
    {'n': 2000, 'k': 4000000, 'median_time_ms': 43.245}, # k=n^2
    
    {'n': 5000, 'k': 10, 'median_time_ms': 0.080},
    {'n': 5000, 'k': 5000, 'median_time_ms': 0.136}, # k=n
    {'n': 5000, 'k': 25000000, 'median_time_ms': 267.863}, # k=n^2
    
    {'n': 10000, 'k': 10, 'median_time_ms': 0.160},
    {'n': 10000, 'k': 10000, 'median_time_ms': 0.267}, # k=n
    {'n': 10000, 'k': 100000000, 'median_time_ms': 1073.804}, # k=n^2
    
    {'n': 20000, 'k': 10, 'median_time_ms': 0.320},
    {'n': 20000, 'k': 20000, 'median_time_ms': 0.542}, # k=n
    {'n': 20000, 'k': 400000000, 'median_time_ms': 4344.081} # k=n^2
]

# Create a DataFrame
df = pd.DataFrame(data)

# --- Separate Counting Sort data by k ---
count_k_10 = df[df['k'] == 10]
count_k_n = df[df['n'] == df['k']]
count_k_n2 = df[
    (df['k'] != 10) & 
    (df['n'] != df['k'])
]

# --- Create the Plot ---
plt.figure(figsize=(12, 8))
plt.style.use('seaborn-v0_8-whitegrid')

# Plot Counting Sort variations
plt.plot(count_k_10['n'], count_k_10['median_time_ms'], marker='^', linestyle=':', label='Counting Sort (k=10)')
plt.plot(count_k_n['n'], count_k_n['median_time_ms'], marker='x', linestyle='--', label='Counting Sort (k=n)')
plt.plot(count_k_n2['n'], count_k_n2['median_time_ms'], marker='D', linestyle='-', label='Counting Sort (k=n²)')

# --- Formatting ---
# Set axis labels per project requirements
plt.xlabel('Input Size (n)', fontsize=14)
plt.ylabel('Median Time (ms)', fontsize=14)
plt.title('Counting Sort Runtime vs. Input Size (n)', fontsize=16)
plt.legend(fontsize=12)
plt.grid(True, which="both", ls="--")

# --- Logarithmic Scale ---
# A log scale is ESSENTIAL to see all three trends clearly.
plt.yscale('log')
plt.xscale('log')

# Set clear Y-axis ticks (these are evenly spaced powers of 10)
plt.yticks(
    [0.001, 0.01, 0.1, 1, 10, 100, 1000, 10000], 
    ['0.001ms', '0.01ms', '0.1ms', '1ms', '10ms', '100ms', '1s', '10s']
)

# --- Removed manual plt.xticks ---
# This will let matplotlib create standard, evenly-spaced
# log ticks (e.g., 10, 100, 1000, 10000)

# Save the final plot
output_filename = 'counting_sort_runtimes.png'
plt.savefig(output_filename, dpi=300, bbox_inches='tight')

print(f"Graph saved as {output_filename}")

