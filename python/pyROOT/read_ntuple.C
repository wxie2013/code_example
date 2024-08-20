import ROOT

fout = ROOT.TFile("result.root", "recreate")
nt = ROOT.TNtuple("nt", "nt", "x:y:z")
for i in range(10):
    nt.Fill(i, i+1, i+2)
nt.Write()

fin = ROOT.TFile("result.root")
nt2 = fin.Get("nt")
for entry in nt2:
  print(entry.x, entry.y, entry.z)
