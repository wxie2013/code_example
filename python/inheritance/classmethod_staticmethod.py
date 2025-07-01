from abc import ABC
class parent(ABC):
    called = False
    def __init__(self):
        if parent.called: # use parent.called instead of self.called to show this is a shared variable
            return
        print("parent constructor")
        self.build() #

        # using self.build() will error b.c. self.build() create child1.a instead of parent.a
        # if cls.a is intended to be shared variable, use parent.build()
        parent.print_a()
        self.build_again()
        self.print_a()
        self.called = True

    @classmethod
    def build(cls):
        cls.a = 2025
        print('parent.build(): ', cls.a)

    @staticmethod
    def build_again():
        parent.a = 2031
        print('parent.build_again(): ', parent.a)

    @classmethod
    def get_a(cls):
        return cls.a

    @classmethod
    def set_a(cls, v_a):
        cls.a = v_a

    @staticmethod   # just a regular function
    def print_a():
        print(parent.a) # need to specify parent.a since there's no cls and self argument


class child1(parent):
    def __init__(self):
        super().__init__()
        self.a = 2026 # create a new child1 instance but parent.a is still 2025
        self.print_a()
        print('child1--: ', self.a)
        print("child constructor")

class child2(parent):
    def __init__(self):
        super().__init__()
        parent.set_a(2027)
        print("child constructor")

a = child1()
print('1--: ', parent.get_a())
b = child2()
print('2--: ', parent.get_a())
parent.set_a(2028)
print('3--: ', parent.get_a())
