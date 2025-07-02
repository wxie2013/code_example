from abc import ABC
from dataclasses import dataclass

@dataclass
class run_config:
    val: float

class parent(ABC):
    called = False
    def __init__(self):
        if parent.called: # use parent.called instead of self.called to show this is a shared variable
            return
        print("parent constructor")
        parent.build() #

        # using self.build() will error b.c. self.build() create child1.a instead of parent.a
        # if cls.a is intended to be shared variable, use parent.build()
        parent.print_a()
        self.build_again()
        self.print_a()
        self.called = True

    @classmethod
    def build(cls):
        cls.a = 2025
        cls.cfg = run_config(val = 0.9)
        print('parent.build(): ', cls.a, cls.cfg.val)

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
        print(parent.a, parent.cfg.val) # need to specify parent.a since there's no cls and self argument


class child1(parent):
    def __init__(self):
        super().__init__()
        self.a = 2026 # create a new child1 instance but parent.a is still 2025
        self.cfg.val = 1.9
        self.print_a()
        print('child1--: ', self.a)
        print("child constructor")

class child2(parent):
    def __init__(self):
        super().__init__()
        parent.set_a(2027)
        self.cfg.val = 2.9
        print("child constructor")

print('1--: ') 
a = child1()
parent.print_a()
b = child2()
print('2--: ')
parent.print_a()
parent.set_a(2028)
parent.print_a()
