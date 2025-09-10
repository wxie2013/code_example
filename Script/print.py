import numpy as np
#a = np.load('spike_hid_booster0.npz')
#a = np.load('spike_hid_exit1.npz')
#a = np.load('spike_classifier_exci.npz')
#a = np.load('spike_hid_exci0.npz')
#a = np.load('test_spike_hid_exci0.npz')
a = np.load('spike_input.npz')
for i, t in zip(a['i'], a['t']):
    print(i, t)
