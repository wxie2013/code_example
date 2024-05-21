class MyClass:
  def __init__(self):
    self.tt0 = 10
    self.tt100 = 3

  def get_attribute(self, attr_name):
    # Check if the attribute name starts with "tt" and is within the valid range (0 to 100)
    if not attr_name.startswith("tt") or not (0 <= int(attr_name[2:]) <= 100):
      raise AttributeError(f"Invalid attribute name: {attr_name}")

    # Access the attribute using getattr() for clarity (optional, direct access also works)
    return getattr(self, attr_name)

  def some_method(self):
    # Example 1: Accessing a known attribute using get_attribute
    desired_value = "tt0"
    value = self.get_attribute(desired_value)
    print(f"Value of {desired_value}: {value}")

    print(self.get_attribute("tt100"))


# Create an object of the class
obj = MyClass()

# Call some_method to demonstrate usage
obj.some_method()
