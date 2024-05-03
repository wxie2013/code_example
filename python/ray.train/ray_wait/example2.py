import ray, time
times = [10, 1, 1, 1, 1, 1]

@ray.remote
def busy(time_val):
  # Simulate some work for the specified time
  import time
  time.sleep(time_val)

  return f"Worker finished task with time: {time_val}"


def main():
  ray.init()

  # Create remote tasks
  ids = [busy.remote(t) for t in times]

  # Wait for the first worker (id[0]) to finish
  result = ray.get(ids[0])
  print(f"First worker finished: {result}")

  time.sleep(5)
  # Run the rest of the tasks asynchronously
  ray.wait(ids, num_returns=len(ids))  # Wait for all remaining tasks to finish

  # All workers are done, print a message
  print("All workers finished their tasks!")

  results = ray.get(ids)
  for result in results:
    print(result)


  ray.shutdown()



if __name__ == "__main__":

  main()

