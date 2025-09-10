import numpy as np
a = np.load('sampleidx_tstart_scaleimg.npz')
for idx, tstart, scale in zip(a['idx'], a['tstart'], a['scale']):
    print(idx, tstart, scale)
