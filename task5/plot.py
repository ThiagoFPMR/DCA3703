import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

df_seq = pd.read_csv('primes_seq.csv')
df_parallel = pd.read_csv('primes_parallel.csv')
df_seq['n'] = 10 ** np.arange(1, 9)
df_parallel['n'] = 10 ** np.arange(1, 9)
# import pdb; pdb.set_trace()
# Set the figure size
plt.figure(figsize=(12, 6))
sns.set_style("whitegrid")



sns.lineplot(x='n', y='Time taken', data=df_seq, label='Sequential', color='blue')
sns.scatterplot(x='n', y='Time taken', data=df_seq, color='blue')
sns.lineplot(x='n', y='Time taken', data=df_parallel, label='Parallel', color='red')
sns.scatterplot(x='n', y='Time taken', data=df_parallel, color='red')
plt.title('Time taken to find primes (Sequential vs Parallel)')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('n')
plt.ylabel('Time taken (us)')
plt.legend()
plt.savefig('task5.png', dpi=300)
plt.show()


relative_speedup = df_seq['Time taken'] / df_parallel['Time taken']
# Plot the relative speedup
plt.figure(figsize=(12, 6))
sns.set_style("whitegrid")
sns.lineplot(x=df_seq['n'], y=relative_speedup, label='Relative Speedup', color='green')
sns.scatterplot(x=df_seq['n'], y=relative_speedup, color='green')
plt.title('Relative Speedup of Parallel vs Sequential')
plt.ylabel('Time taken (Sequential) / Time taken (Parallel)')
plt.xscale('log')
plt.savefig('task5_speedup.png', dpi=300)
plt.show()