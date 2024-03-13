import time
import ray

@ray.remote
class Tester:
    def __init__(self, fun, kwargs):
        self.kwargs = kwargs
        self.fun = fun

    def run(self):
        return self.fun(self.kwargs)


def ttt(param):
    for key, val in param.items():
        print(f'key: {key}, val: {val}')
    return param


params = [{'a0':0}, {'a1':1}, {'a2':2}]
# I use list comprehensions instead of for loops for terseness.
testers = [Tester.remote(ttt, p) for p in params]
not_done_ids = [tester.run.remote() for tester in testers]

# len() is not required to check that the list is empty.
while not_done_ids:
    # Replace not_done_ids with the list of object references that aren't
    # ready. Store the list of object references that are ready in done_ids.
    # timeout=1 means sleep at most 1 second, do not sleep if there are
    # new object references that are ready.
    done_ids, not_done_ids = ray.wait(not_done_ids, timeout=1)
    print(f'done_ids: {done_ids}, not_done_ids: {not_done_ids}')

    # ray.get can take an iterable of object references.
    done_return_values = ray.get(done_ids)

    # Process each result.
    for result in done_return_values:
        print(f'result: {result}')
