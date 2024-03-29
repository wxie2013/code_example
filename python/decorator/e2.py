'''
Applying Multiple Decorators to a Single Function

'''
from e1 import uppercase_decorator

def split_string(function):
    def wrapper():
        func = function()
        splitted_string = func.split()
        return splitted_string

    return wrapper

@split_string
@uppercase_decorator
def say_hi():
    return 'hello there'


print(say_hi())

