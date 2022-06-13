'''
Defining General Purpose Decorators
To define a general purpose decorator that can be applied to any function we use args and **kwargs. args and **kwargs collect all positional and keyword arguments and stores them in the args and kwargs variables. args and kwargs allow us to pass as many arguments as we would like during function calls.
'''

def a_decorator_passing_arbitrary_arguments(function_to_decorate):
    def a_wrapper_accepting_arbitrary_arguments(*args,**kwargs):
        print('The positional arguments are', args)
        print('The keyword arguments are', kwargs)
        function_to_decorate(*args)
    return a_wrapper_accepting_arbitrary_arguments

@a_decorator_passing_arbitrary_arguments
def function_with_arguments(a, b, c):
    print(a, b, c)

function_with_arguments(1,2,3, tt = 'test keywork')
