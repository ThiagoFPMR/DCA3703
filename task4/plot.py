import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

sns.set_theme(style="whitegrid")

def plot_complex_series():
    complex_df = pd.read_csv('ComplexSeries.csv')
    complex_parallel_df = pd.read_csv('ComplexSeriesParallel.csv')

    plt.figure(figsize=(10, 6))
    sns.lineplot(data=complex_df, x='Num threads', y='Time taken', label='Complex Series')
    sns.lineplot(data=complex_parallel_df, x='Num threads', y='Time taken', label='Complex Parallel')
    plt.title('Complex Series vs Complex Parallel')
    plt.xlabel('Threads')
    plt.ylabel('Time (us)')
    plt.legend()
    plt.savefig('complex_series.png')
    # plt.show()

def plot_vector_sum():
    vector_sum_df = pd.read_csv('VectorSum.csv')
    vector_sum_parallel_df = pd.read_csv('VectorSumParallel.csv')
    
    plt.figure(figsize=(10, 6))
    sns.lineplot(data=vector_sum_df, x='Num threads', y='Time taken', label='Vector Sum')
    sns.lineplot(data=vector_sum_parallel_df, x='Num threads', y='Time taken', label='Vector Sum Parallel')
    plt.title('Vector Sum vs Vector Sum Parallel')
    plt.xlabel('Threads')
    plt.ylabel('Time (us)')
    plt.legend()
    plt.savefig('vector_sum.png')
    # plt.show()

if __name__ == "__main__":
    # plot_complex_series()
    plot_vector_sum()