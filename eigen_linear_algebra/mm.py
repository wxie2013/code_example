import numpy as np
a = np.full((2, 2), np.nan);
a[0,0] = 1
a[0,1] = 2
a[1,0] = 3
a[1,1] = 4

b = (2, 3)
c = a*b
print(c)
flattened = c.flatten()
print(flattened)
print(~np.isnan(flattened))
print(flattened[~np.isnan(flattened)])

