import numpy as np
a = np.load('spike_hid_exci0.npz', allow_pickle=True)
#a = np.load('spike_hid_exci1.npz', allow_pickle=True)
for i, t, l, g, idx, strength in zip(a['i'], a['t'], a['label'], a['group'], a['idx'], a['strength']):
    print(i, t, l, g, idx, strength)
    #print(t, l, g, idx)
