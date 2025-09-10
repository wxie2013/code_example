import ROOT
import numpy as np

file = ROOT.TFile("pattern.root", "RECREATE");
nt = ROOT.TNtuple("nt", "", "label:layer:nid:rate:tot:evt");
nt_KL = ROOT.TNtuple("nt_KL", "", "KL:ievt:jevt");

f =  open("/home/wxie/mm.txt") 

previous_tot = 0
evt = -1
prob = ROOT.vector[ROOT.vector[ROOT.vector[ROOT.pair[int, float]]]](1000)
n_hlayer=2
for v in prob:
    v.resize(n_hlayer);

for line in f:
    label, layer, nid, rate, tot_spike_rate = [float(s) for s in line.split() if s.replace('.','').isdigit()]
    if(tot_spike_rate != previous_tot):
        evt+=1
        previous_tot = tot_spike_rate

    prob[evt][int(layer)].push_back(ROOT.std.make_pair(nid, rate))
    nt.Fill(label, layer, nid, rate, tot_spike_rate, evt)

c1 = ROOT.TCanvas("c1", "", 1000, 1000)
c1.Divide(5, 5)
nt.SetMarkerStyle(20);
for i in range(evt+1):
    c1.cd(i+1)
    nt.Draw("rate:nid", "layer==0 && evt=="+str(i+1))
c1.SaveAs("pattern.pdf")

# calculate KL Divergence
for i in range(evt+1):
    for j in range(evt+1):
        KL=0
        for l in range(n_hlayer): # same layer
            for p in prob[i][l]:
                for q in prob[j][l]:
                    if p.first==q.first:
                        KL += p.second*np.log(p.second/q.second)
                        print(i, j, l, p.first, q.first, p.second, q.second, KL)
        if KL<0:
            print('---: ', i, j, KL)

        nt_KL.Fill(KL, i, j)

file.cd()
nt.Write()
nt_KL.Write()
file.Close()
f.close()
