import ROOT 

ROOT.gROOT.LoadMacro('test.C')
a = ROOT.std.map[ROOT.std.string, ROOT.float]()
a['test'] =  99
ROOT.test(a)

b = {'test': 2999, 'try':2022}
list_keys = list(b.keys())
list_vals = list(b.values())

c = ROOT.std.map[ROOT.std.string, ROOT.float]()
for k,v in zip(list_keys, list_vals):
    c.insert(ROOT.std.make_pair(k,v))

ROOT.test(c)
