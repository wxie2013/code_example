# example to show how different child classes call parent class only once
class parent:
    called_once = False
    def __init__(self):
        if parent.called_once is False:
            parent.ttt = 101
            parent.called_once = True
            print('1-------------------')
            self.assign()
    def assign(self):
        print('2------')
        parent.ttt = 102 # don't use self.ttt which will mask the parent.ttt

class child1(parent):
    def __init__(self):
        super().__init__()
        print(f'child1 ttt = {self.ttt}')

class child2(parent):
    def __init__(self):
        super().__init__()
        print(f'child2 ttt = {self.ttt}')

c1 = child1()
c2 = child2()
