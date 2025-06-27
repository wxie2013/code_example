# example to show how different child classes call parent class only once
class parent:
    called_once = False
    ttt = None
    def __init__(self):
        if parent.called_once is False:
            parent.ttt = 101
            parent.called_once = True
            print('--------------------')

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
