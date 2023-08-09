from pathlib import Path
import importlib, sys
home_dir = Path.home()
current_dir = Path.cwd()
path_head = str(current_dir.relative_to(home_dir))
path_head = path_head[:len('Brian2')]
if path_head != 'Brian2':
    sys.exit('!!!! Brian2 directory not found !!!!')
input_param = importlib.import_module('Brian2.jobs_sub.ray_tune.input_param')
print(str(path_head)+'.common_import')
common_import = importlib.import_module(str(path_head)+'.common_import')
print(input_param.switch_norm)
