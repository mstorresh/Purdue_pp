import numpy as np
import matplotlib.pyplot as plt


x   = [2.0, 5.0, 16]

#p8  = [0.02569, 0.07681, 0.3342, 0.4864, 1.322]
p9  = [-0.0267343, -0.0205258, -0.0161124]


fig, ax = plt.subplots()
# ax.tick_params(labeltop=True, labelright=True)

plt.xlabel('Multiplicity')
plt.ylabel('Fourier Coefficients')
#plt.errorbar(x, p8, yerr=p8err, fmt='.', color='blue', label='Pedestal')
plt.errorbar(x, p9, fmt='.', color='red', label='V1')

ax.minorticks_on()
# ax.tick_params(direction='in')
# ax.yaxis.tick_right() 
ax.yaxis.set_ticks_position('both')
ax.xaxis.set_ticks_position('both')

ax.tick_params(which='both', direction='in')
ax.tick_params(which='major', length=7)
ax.tick_params(which='minor', length=4)

plt.legend()
plt.show()
