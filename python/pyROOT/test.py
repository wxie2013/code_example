import ROOT

ROOT.gROOT.LoadMacro('dict.C')
ROOT.gROOT.LoadMacro('nt.C')
ROOT.gInterpreter.Declare('''
            void oo(float t)
            {cout<<t<<endl;};
            ''')

ROOT.oo(2023)
#
a = ROOT.std.map[ROOT.std.string, ROOT.float]()
a['test'] =  99
ROOT.dict(a)

# python dictionary to std::map
b = {'test': 2999, 'try':2022}
list_keys = list(b.keys())
list_vals = list(b.values())

c = ROOT.std.map[ROOT.std.string, ROOT.float]()
for k,v in zip(list_keys, list_vals):
    c.insert(ROOT.std.make_pair(k,v))

ROOT.dict(c)

# define ntuple in python but fill it in c++ macro. ntuple in pyROOT has a limit of 15
# argument. 
nt = ROOT.TNtuple('nt', '', 'a1:a2:a3:a4:a5:a6:a7:a8:a9:a10:a11:a12:a13:a14:a15:a16:a17:a18:a19:a20')
ROOT.nt(nt)
nt.Print()
nt.Scan('a1:a2:a3:a4:a5:a6:a7:a8:a9:a10:a11:a12:a13:a14:a15:a16:a17:a18:a19:a20')
