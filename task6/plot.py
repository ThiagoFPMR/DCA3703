import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt


df_seq = pd.read_csv('monte_carlo_pi.csv')
df_parallel = pd.read_csv('monte_carlo_pi_parallel.csv')
df_fixed = pd.read_csv('monte_carlo_pi_parallel_fixed.csv')

df_parallel['N'] = df_parallel['N'].astype(int)
df_fixed['N'] = df_fixed['N'].astype(int)

# Set the figure size
plt.figure(figsize=(12, 6))
sns.set_style("whitegrid")

sns.lineplot(x='N', y='Time taken', data=df_seq, label='Sequential', color='blue')
sns.scatterplot(x='N', y='Time taken', data=df_seq, color='blue')
sns.lineplot(x='N', y='Time taken', data=df_parallel, label='Parallel', color='red')
sns.scatterplot(x='N', y='Time taken', data=df_parallel, color='red')
sns.lineplot(x='N', y='Time taken', data=df_fixed, label='Parallel Fixed', color='green')
sns.scatterplot(x='N', y='Time taken', data=df_fixed, color='green')
plt.title('Time taken to find pi (Sequential vs Parallel)')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('N')
plt.ylabel('Time taken (us)')
plt.show()
plt.savefig('task6_time.png', dpi=300)
plt.clf()

pi = np.pi

df_seq['Estimation Error'] = np.abs(pi - df_seq['Estimated Pi'])
df_parallel['Estimation Error'] = np.abs(pi - df_parallel['Estimated Pi'])
df_fixed['Estimation Error'] = np.abs(pi - df_fixed['Estimated Pi'])

import pdb; pdb.set_trace()

plt.figure(figsize=(12, 6))
sns.set_style("whitegrid")

sns.lineplot(x='N', y='Estimation Error', data=df_seq, label='Sequential', color='blue')
sns.scatterplot(x='N', y='Estimation Error', data=df_seq, color='blue')
sns.lineplot(x='N', y='Estimation Error', data=df_parallel, label='Parallel', color='red')
sns.scatterplot(x='N', y='Estimation Error', data=df_parallel, color='red')
sns.lineplot(x='N', y='Estimation Error', data=df_fixed, label='Parallel Fixed', color='green')
sns.scatterplot(x='N', y='Estimation Error', data=df_fixed, color='green')
plt.title('Estimated Pi Error (Sequential vs Parallel)')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('N')
plt.ylabel('Estimated Pi Error')
plt.show()
plt.savefig('task6_pi_error.png', dpi=300)