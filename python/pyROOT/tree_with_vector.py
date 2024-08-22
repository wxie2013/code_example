import ROOT
from ROOT import TFile, TTree, addressof, gROOT
gROOT.ProcessLine(
"struct data_t {\
   int  m;\
   std::string  *n;\
   std::vector<int> *E;\
};")

data = ROOT.data_t()
data.E = ROOT.vector[int]() # define it here 
data.n = ROOT.string();

t1 = TTree("t1", "EMC Photons");
t1.Branch("m", addressof(data, 'm'), 'm/I');
t1.Branch("E", data.E);
t1.Branch("n", data.n);

data.n.assign("hello");
data.m = 10;
for i in range(data.m):
    data.E.push_back(i);

t1.Fill()
t1.Print()
t1.Scan("E:m:n")
