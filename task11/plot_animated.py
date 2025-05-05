import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from mpl_toolkits.mplot3d import Axes3D

# Load data
df = pd.read_csv('resultados.csv')

# Sort by time just in case
df = df.sort_values(by='t')
time_steps = sorted(df['t'].unique())

# Create figure
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

# Initial frame
df0 = df[df['t'] == time_steps[0]]
quiver = ax.quiver(
    df0['i'], df0['j'], df0['k'],
    df0['u'], df0['v'], df0['w'],
    length=0.5, normalize=True, color='blue'
)

# Set labels
ax.set_xlabel('X (i)')
ax.set_ylabel('Y (j)')
ax.set_zlabel('Z (k)')
ax.set_title('3D Navier-Stokes Velocity Field')

# Update function
def update(frame):
    global quiver
    ax.collections.remove(quiver)  # Remove old quiver
    dft = df[df['t'] == time_steps[frame]]
    quiver = ax.quiver(
        dft['i'], dft['j'], dft['k'],
        dft['u'], dft['v'], dft['w'],
        length=0.5, normalize=True, color='blue'
    )
    ax.set_title(f'3D Navier-Stokes Velocity Field\nTime = {time_steps[frame]}')
    return quiver,

# Create animation
ani = FuncAnimation(fig, update, frames=len(time_steps), interval=200, blit=False)

plt.show()
