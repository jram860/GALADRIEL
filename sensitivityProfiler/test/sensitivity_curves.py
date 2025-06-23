import numpy as np
import matplotlib.pyplot as plt

num_particles = 6000000

plt.rcParams.update({
    'font.size': 20,               # Set global font size for all text
    'axes.labelsize': 24,          # Font size for axis labels
    'axes.titlesize': 28,          # Font size for plot titles
    'xtick.labelsize': 18,         # Font size for x-axis ticks
    'ytick.labelsize': 18,         # Font size for y-axis ticks
    'legend.fontsize': 18,         # Font size for legend text
    'figure.figsize': [12, 8],     # Default figure size (width, height in inches)
    'lines.linewidth': 2.5,        # Default line width
    'lines.markersize': 8,         # Default marker size
    'axes.linewidth': 2,           # Thicker axis lines
    'xtick.major.width': 2,        # Thicker major ticks on x-axis
    'ytick.major.width': 2,        # Thicker major ticks on y-axis
    'legend.frameon': True,       # No frame around the legend
    #'savefig.dpi': 300             # High resolution for saving figures

})

def process_data(filepath):
    df = np.genfromtxt(filepath, delimiter = ' ', skip_header=1)
    return df

# df = process_data('combined_data.txt')


# fig, ax = plt.subplots()

# # Format the data, old data used 6e6 particles, new data uses 1e6
# for i in range(3,df.shape[1]):
#     for j in range(1,df.shape[0]):
#         if j <= 99: 
#             df[j,i] = df[j,i]/(df[j,1] * num_particles)
#         else:
#             df[j,i] = df[j,i]/(df[j,1] * 1000000)


# for i in range(3, df.shape[1]):
#     ax.plot(df[0:99,1], df[0:99,i], label = f'Detector {i-3}')


# ax.set_xlabel('Incident Electron Energy, $E_0$ [MeV]')
# ax.set_ylabel('Fractional Energy Deposition $E/E_0$')
# ax.set_title('Electron Sensitivity')
# ax.legend()
# ax.grid()
# plt.show()

### gamma data --------------------------

df = process_data('gamma_combined_data.txt')

fig, ax = plt.subplots()

# Format the data, old data used 6e6 particles, new data uses 1e6
for i in range(3,df.shape[1]):
    for j in range(1,df.shape[0]):
        if j <= 100: 
            df[j,i] = df[j,i]/(df[j,1] * 1000000)
        else:
            df[j,i] = df[j,i]/(df[j,1] * 1000000)


for i in range(3, df.shape[1]):
    ax.plot(df[:,1], df[:,i], label = f'Detector {i-3}')

ax.set_xlabel('Incident X-Ray Energy, $E_0$ [MeV]')
ax.set_ylabel('Fractional Energy Deposition $E/E_0$')
ax.set_title('X-Ray Sensitivity')
ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.15), ncol=3)
plt.tight_layout()
ax.grid()
plt.show()
