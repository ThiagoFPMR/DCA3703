import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df = pd.read_csv('resultados-O0.csv')

sns.set_style('whitegrid')
plt.figure(figsize=(10, 6))

sns.lineplot(data=df, x='N', y='tempo_inicializacao', label='Inicialização')
sns.lineplot(data=df, x='N', y='tempo_soma_dependente', label='Soma com dependência')
sns.lineplot(data=df, x='N', y='tempo_soma_independente', label='Soma sem dependência')

plt.title('Tempo de execução em função de N')
plt.xlabel('N')
plt.ylabel('Tempo (s)')
plt.legend()  # Adiciona a legenda
plt.savefig('plot-O0.png')
# plt.show()
