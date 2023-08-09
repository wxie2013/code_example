from code_example.python.__init__py.example import *
from code_example.python.__init__py.example.example2 import *
from code_example.python.__init__py.example.example2.t2 import *

t_print();
#t1_print();  # uncomment will leads to error because it's not included in __all__
t2_print();
