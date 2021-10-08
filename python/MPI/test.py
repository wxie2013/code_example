import numpy as np
from mpi4py import MPI
import code_example.python.repeated_K_fold as rkf

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

print('train_index@rank', rank, ':', rkf.list_train_index[rank])
print('test_index@rank', rank, ':', rkf.list_test_index[rank])

sum_train = np.zeros(1)
sum_test = np.zeros(1)
sum_train[0] = sum(rkf.list_train_index[rank])
sum_test[0] = sum(rkf.list_test_index[rank])
print('sum_train@rank', rank, ': ', sum_train[0]) 
print('sum_test@rank', rank, ': ', sum_test[0])

##
total_sum_train = np.zeros(1)
total_sum_test = np.zeros(1)
comm.Reduce(sum_train, total_sum_train, op=MPI.SUM, root=0)
comm.Reduce(sum_test, total_sum_test, op=MPI.SUM, root=0)

if rank == 0:
    print('total_sum_train: ', total_sum_train, ' total_sum_test: ', total_sum_test)
