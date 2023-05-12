import ROOT
#a = ROOT.std.vector[ROOT.std.tuple[ROOT.int, ROOT.float, ROOT.float]] () # this works too
a = ROOT.std.vector('tuple<int, float, float>') ()
for i in range(10):
    a.push_back(ROOT.std.make_tuple[ROOT.int, ROOT.float, ROOT.float](i, i*2, i*10))

for i in range(a.size()):
    x, y, z = a[i]
    print(x, y, z)
