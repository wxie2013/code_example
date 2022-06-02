#e.g. py example.py -t 2.tmpt -d 2.dat 

import jinja2, yaml, argparse

# input template and data file
parser = argparse.ArgumentParser(description='template file and data yaml file')
parser.add_argument('-t', type=str, required=True, help='template file name')
parser.add_argument('-d', type=str, required=True, help='data file name')
args = parser.parse_args()

template_file = args.t
data_file='data/'+args.d

# find the template 
templateloader = jinja2.FileSystemLoader(searchpath="./template")
templateEnv = jinja2.Environment(loader = templateloader)
templateEnv.trim_blocks = True  # control white space
templateEnv.lstrip_blocks = True  # control white space
template = templateEnv.get_template(template_file)

#load the data as string
with open(data_file) as f:
    data_str = f.read();

# convert str to dictionary
data = yaml.safe_load(data_str)

#render
output = template.render(data)
print(output)
