import jinja2, yaml

# find the template 
templateloader = jinja2.FileSystemLoader(searchpath="./template")
templateEnv = jinja2.Environment(loader = templateloader)
template_file = "3.tmpt"
template = templateEnv.get_template(template_file)

#load the data as string
with open('data/3.dat') as f:
    data_str = f.read();

# convert str to dictionary
data = yaml.safe_load(data_str)

#render
output = template.render(data)
print(output)
