import ROOT
from ROOT import TFile, TTree, addressof, gROOT
gROOT.ProcessLine(
"struct data_t {\
   int  m;\
   Char_t  n[5];\
   std::vector<int> *E;\
};")

data = ROOT.data_t()
data.E = ROOT.std.vector(int)() # define it here 

t1 = TTree("t1", "EMC Photons");
t1.Branch("m", addressof(data, 'm'), 'm/I');
t1.Branch("E", data.E);
t1.Branch("n", addressof(data, 'n'), "n/C");

data.n = "1234";
data.m = 10;
for i in range(data.m):
    data.E.push_back(i);

t1.Fill()
t1.Print()
t1.Scan("E:m:n")
