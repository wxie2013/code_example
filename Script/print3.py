from statistics import mean
import numpy as np
#a = np.load('adpt_thres_exci__hid1.npz')
a = np.load('adpt_thres_exci__hid0.npz')
for i in range(len(a['vt'])):
    print(i, a['vt'][i])

print("mean: ", mean(a['vt']))

