import sys
sys.path.append('/home/wxie/Brian2/pkgs')
from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

if rank == 0:
    a = 1
else:
    a = None
a = comm.bcast(a, root=0)
print('rank: ', rank, ' a: ', a)
s = comm.reduce(a, op=MPI.SUM)
if rank == 0:
    print('From process 0, sum =', s)

if rank == 1:
    b = 2
else:
    b = None

b = comm.bcast(b, root=1)
x = comm.reduce(b, op=MPI.SUM, root=1)

if rank == 1:
    print('From process 1, sum =', x)

