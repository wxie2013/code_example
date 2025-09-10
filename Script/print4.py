import numpy as np
#a = np.load('S_bfe_syn0.npz')
#a = np.load('S_bbe_syn0.npz')
a = np.load('S_input2e0.npz')
for i, j, delay, w in zip(a['i'], a['j'], a['delay'], a['w']):
    print(i, j, delay, w)

#a = np.load('S_i2e_hid1.npz')
#a = np.load('S_i2e_hid0.npz')
#a = np.load('S_e2i_hid0.npz')
#a = np.load('S_e2i_hid1.npz')
#for i, j, delay in zip(a['i'], a['j'], a['delay']):
#    print(i, j, delay)

#a = np.load('S_e2b_hid0.npz')
#a = np.load('S_e2b_hid1.npz')
#for i, j in zip(a['i'], a['j']):
#    print(i, j)
