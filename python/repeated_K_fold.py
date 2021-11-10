import numpy as np
from sklearn.model_selection import RepeatedKFold

X = np.array([]);
for i in range(10):
    X = np.append(X, i);

#
num_splits = 4
num_repeat = 2

#
kf = RepeatedKFold(n_splits=num_splits, n_repeats=num_repeat, random_state=2652124)
kf.get_n_splits(X)

list_train_index = []
list_test_index = []
for train_index, test_index in kf.split(X):
    print(type(train_index))
    list_train_index.append(train_index)
    list_test_index.append(test_index)
    print(train_index, test_index)
