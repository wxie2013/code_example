# usage: python unbuffered.py >out&
# one can also use python -u unbuffered.py w/o involving sys.stdout.flush
# or add flush=True in print function
import time
import sys 
for i in range(100000):
    print('---------------------', i)
    sys.stdout.flush() 
    time.sleep(1)

