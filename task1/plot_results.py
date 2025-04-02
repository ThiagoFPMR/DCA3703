import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Load the data
df_row = pd.read_csv('task1_row-major.csv')
df_col = pd.read_csv('task1_col-major.csv')

# Plot the results
sns.set_theme(style="whitegrid")
plt.figure(figsize=(10, 5))
sns.lineplot(data=df_row.iloc[:-2, :], x='n', y='time', label='Row-major')
sns.lineplot(data=df_col.iloc[:-2, :], x='n', y='time', label='Column-major')
plt.xlabel('n')
plt.ylabel('Time (us)')
plt.title('Matrix multiplication')
plt.legend()
plt.show()