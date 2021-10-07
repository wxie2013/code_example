import numpy as np
from sklearn.model_selection import KFold, RepeatedKFold
X = np.array([[1, 2], [3, 4], [6, 7], [8, 9]])
y = np.array([1, 2, 3, 4])
#kf = KFold(n_splits=2)
kf = RepeatedKFold(n_splits=2, n_repeats=2, random_state=2652124)
kf.get_n_splits(X)
print(kf)
for train_index, test_index in kf.split(X):
     print("TRAIN:", train_index, "TEST:", test_index)
     X_train, X_test = X[train_index], X[test_index]
     y_train, y_test = y[train_index], y[test_index]
     print('X_train: ', X_train)
     print('X_test: ', X_test)
     print('y_train: ', y_train)
     print('y_test: ', y_test)
     print('--------------------------')
