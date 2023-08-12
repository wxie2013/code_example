from example import *
from example.example2 import *
from example.example2.t2 import *

t_print();
#t1_print();  # uncomment will leads to error because it's not included in __all__
t2_print();
