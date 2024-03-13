def generic_function(*args):
  """
  This function takes any number of positional arguments as a tuple.
  Args:
      *args: A tuple containing the arguments.
  Returns:
      A string representation of the arguments.
  """
  # Iterate through the arguments (limited operations possible)
  for arg in args:
    print(f"Argument: {arg}")

# Example usage
generic_function(10, "hello", [1, 2, 3])

