import numpy as np
import matplotlib.pyplot as plt


electron_df = np.genfromtxt('new_e_energy_deposition.txt',skip_header=1)
gamma_df = np.genfromtxt('new_gamma_energy_deposition.txt', skip_header=1)
fig1,ax1 = plt.subplots()
for i in range(3,electron_df.shape[1]):
    ax1.plot(electron_df[:,1],electron_df[:,i], label=f'Detector {i-3}') 

ax1.set_ylabel('Energy Deposition [MeV]')
ax1.set_xlabel('Incident Energy, $E_0$ [MeV]')
ax1.set_title('Detector Electron Sensitivity')
ax1.legend()
ax1.grid()

fig2,ax2 = plt.subplots()
for i in range(3,electron_df.shape[1]):
    ax2.plot(electron_df[:,1],electron_df[:,i]/(electron_df[:,1]*6000000), label=f'Detector {i-3}')
    # ax2.plot(electron_df[:,1],electron_df[:,i]/electron_df[:,2], label=f'Detector {i-3}') 

ax2.set_xlabel('Incident Energy, $E_0$ [MeV]')
ax2.set_ylabel('Fractional Energy Deposition $E/E_0$')
ax2.set_title('Fractional Detector Electron Sensitivity')
ax2.legend()
ax2.grid()

fig3,ax3 = plt.subplots()
for i in range(3,electron_df.shape[1]):
    ax3.plot(electron_df[:,1],electron_df[:,i]/(electron_df[:,1]*6000000), label=f'Detector {i-3}') 
    # ax3.plot(electron_df[:,1],electron_df[:,i]/electron_df[:,2], label=f'Detector {i-3}') 
ax3.set_xscale('log')
ax3.set_yscale('log')
ax3.set_xlabel('Incident Energy, $E_0$ [MeV]')
ax3.set_ylabel('Fractional Energy Deposition $E/E_0$')
ax3.set_title('Fractional Detector Electron Sensitivity')
ax3.legend()
ax3.grid()

# ========================== Gamma Plots ===============================================
fig4,ax4 = plt.subplots()
for i in range(3,gamma_df.shape[1]):
    ax4.plot(gamma_df[:,1],gamma_df[:,i], label=f'Detector {i-3}') 

ax4.set_ylabel('Energy Deposition [MeV]')
ax4.set_xlabel('Incident Energy, $E_0$ [MeV]')
ax4.set_title('Detector Photon Sensitivity')
ax4.legend()
ax4.grid()

fig5,ax5 = plt.subplots()
for i in range(3,gamma_df.shape[1]):
    ax5.plot(gamma_df[:,1],gamma_df[:,i]/(gamma_df[:,1]*1000000), label=f'Detector {i-3}') 
    # ax5.plot(gamma_df[:,1],gamma_df[:,i]/gamma_df[:,2], label=f'Detector {i-3}') 

ax5.set_xlabel('Incident Energy, $E_0$ [MeV]')
ax5.set_ylabel('Fractional Energy Deposition $E/E_0$')
ax5.set_title('Fractional Detector Photon Sensitivity')
ax5.legend()
ax5.grid()

fig6,ax6 = plt.subplots()
for i in range(3,gamma_df.shape[1]):
    ax6.plot(gamma_df[:,1],gamma_df[:,i]/(gamma_df[:,1]*1000000), label=f'Detector {i-3}')
    # ax6.plot(gamma_df[:,1],gamma_df[:,i]/gamma_df[:,2], label=f'Detector {i-3}') 

ax6.set_xscale('log')
ax6.set_yscale('log')
ax6.set_xlabel('Incident Energy, $E_0$ [MeV]')
ax6.set_ylabel('Fractional Energy Deposition $E/E_0$')
ax6.set_title('Fractional Detector Photon Sensitivity')
ax6.legend()
ax6.grid()

fig1.savefig('electron_sens.png')
fig2.savefig('electron_frac_sens.png')
fig3.savefig('electron_log_frac_sens.png')
fig4.savefig('gamma_sens.png')
fig5.savefig('gamma_frac_sens.png')
fig6.savefig('gamma_log_frac_sens.png')

plt.show()

