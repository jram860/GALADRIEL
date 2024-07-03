import numpy as np
import matplotlib.pyplot as plt


df = np.genfromtxt('energy_deposition.txt', skip_header=1)

fig,ax = plt.subplots()

for i in range(3,df.shape[1]):
    ax.plot(df[:,1],df[:,i]/(df[:,2]*6000000),label = ('detector',i-3))   



ax.set_xlabel('Fractional Energey Deposition $E_dep/E_0$')
ax.set_ylabel('Energy Deposition (MeV)')
#ax.set_xscale('log')
#ax.set_yscale('log')
ax.set_title('')
ax.legend()
ax.grid()
plt.show()