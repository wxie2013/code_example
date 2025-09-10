import numpy as np
#a = np.load('S_input2e1.npz')
#a = np.load('S_input2e0.npz')
#a = np.load('S_efe_syn0.npz')
a = np.load('S_e2e_same_group_hid0.npz')
for i, j, w, delay, delay_dendritic in zip(a['i'], a['j'], a['w'], a['delay'], a['delay_dendritic']):
    print(i, j, w, delay, delay_dendritic)

#a = np.load('S_e2e_diff_group_hid0.npz')
#for i, j, delay, dW_e2e in zip(a['i'], a['j'], a['delay'], a['dW_e2e']):
#    print(i, j, delay, dW_e2e)
