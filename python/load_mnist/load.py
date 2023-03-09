from sklearn.model_selection import train_test_split
from sklearn.datasets import fetch_openml
mnist = fetch_openml('mnist_784', parser="auto")
x = mnist.data
y = mnist.target

x_train, x_test, y_train, y_test = train_test_split(x, y, test_size = 10000)
print(len(x), len(y))
print(len(x_train), len(y_train))
print(len(x_test), len(y_test))
