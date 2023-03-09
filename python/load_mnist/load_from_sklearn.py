from sklearn.model_selection import train_test_split
from sklearn.datasets import fetch_openml

X, Y = fetch_openml("mnist_784", version=1, return_X_y=True, as_frame=False, parser="auto")
X = X.reshape(70000, 28, 28)
x_train, x_test, y_train, y_test = train_test_split(X, Y, test_size = 10000)
