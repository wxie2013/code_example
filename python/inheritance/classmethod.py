from abc import ABC
class parent(ABC):
    called = False
    def __init__(self):
        if parent.called:
            return
        print("parent constructor")
        parent.build()  # if use self.build(), it create a child1.a instead of parent.a
        parent.called = True

    @classmethod
    def build(cls):
        cls.a = 2025

    @classmethod
    def get_a(cls):
        return cls.a

    @classmethod
    def set_a(cls, v_a):
        cls.a = v_a


class child1(parent):
    def __init__(self):
        super().__init__()
        print(self.a) # print 2025 which is parent.a
        self.a = 2026 # create a new child1 instance but parent.a is still 2025
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
