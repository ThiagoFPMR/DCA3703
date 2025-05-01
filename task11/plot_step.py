import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Example DataFrame (replace this with your actual data)
# Columns: i, j, k (positions), u, v, w (velocity components)
data = {
    'i': [0, 0, 0, 1, 1, 1, 2, 2, 2],
    'j': [0, 1, 2, 0, 1, 2, 0, 1, 2],
    'k': [0, 0, 0, 1, 1, 1, 2, 2, 2],
    'u': [1, 0, -1, 0, 1, 0, -1, 0, 1],
    'v': [0, 1, 0, -1, 0, 1, 0, -1, 0],
    'w': [0, 0, 1, 0, 0, -1, 1, 0, 0],
    't': [0, 0, 0, 0, 0, 0, 0, 0, 0]  # Time is constant
}
df = pd.read_csv('resultados.csv')
df = df[df.t == 0]  # Filter for time = 0

import pdb; pdb.set_trace()
# Sample the data
sample_rate = 1000  # Adjust this to sample every nth point
df = df.iloc[::sample_rate, :]
import pdb; pdb.set_trace()


# Extract position and velocity components
x = df['i']
y = df['j']
z = df['k']
u = df['u']
v = df['v']
w = df['w']

# Create a 3D quiver plot
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

# Plot the vectors
ax.quiver(x, y, z, u, v, w, length=0.5, normalize=True, color='blue')

# Set labels
ax.set_xlabel('X (i)')
ax.set_ylabel('Y (j)')
ax.set_zlabel('Z (k)')
ax.set_title('3D Navier-Stokes Velocity Field')

# Show the plot
plt.savefig('3D_velocity_field.png', dpi=300)