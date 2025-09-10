import numpy as np
a=np.load('neuron_groups_exci_0.npz')
print('---- layer0 ------')
for i, (g, x, y, x_max, y_max) in enumerate(zip(a['neuron_groups'], a['x_local'], a['y_local'], a['x_max'], a['y_max'])):
    print(i, int(g), x, y, x_max, y_max)

print('---- layer1 ------')
a=np.load('neuron_groups_exci_1.npz')
for i, (g, x, y, x_max, y_max) in enumerate(zip(a['neuron_groups'], a['x_local'], a['y_local'], a['x_max'], a['y_max'])):
    print(i, int(g), x, y, x_max, y_max)

