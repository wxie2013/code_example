from pathlib import Path
import importlib, sys
home_dir = Path.home()
current_dir = Path.cwd()
path_head = str(current_dir.relative_to(home_dir))
path_head = path_head[:path_head.index('Brian2')+len('Brian2')].replace('/', '.')
print('path_head: ', path_head)
if 'Brian2' not in path_head:
    sys.exit('!!!! Brian2 directory not found !!!!')
common_import = importlib.import_module(str(path_head)+'.common_import')

# is there an __all__?  if so respect it
if "__all__" in common_import.__dict__:
    names = common_import.__dict__["__all__"]
else:
    # otherwise we import all names that don't begin with _
    names = [x for x in common_import.__dict__ if not x.startswith("_")]

# now drag them in
globals().update({k: getattr(common_import, k) for k in names})

print(input_param.switch_norm)
print('1---: ', isNotEmpty('/home/wxie'))
