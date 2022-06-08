'''
Debugging Decorators
As we have noticed, decorators wrap functions. The original function name, its docstring, and parameter list are all hidden by the wrapper closure: For example, when we try to access the decorated_function_with_arguments metadata, we'll see the wrapper closure's metadata. This presents a challenge when debugging.

In order to solve this challenge Python provides a functools.wraps decorator. This decorator copies the lost metadata from the undecorated function to the decorated closure. Let's show how we'd do that.

'''
import functools

def uppercase_decorator(func):
    @functools.wraps(func)
    def wrapper():
        return func().upper()
    return wrapper

@uppercase_decorator
def say_hi():
    "This will say hi"
    return 'hello there'

print(say_hi())
print(say_hi.__name__)
print(say_hi.__doc__)



