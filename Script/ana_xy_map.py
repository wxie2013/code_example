import ROOT
from Brian2.tools.general_tools import *

project_dir = "/home/wxie/Brian2/model"
dir_neuron_in = f"{project_dir}/neuron_group/neurons_in"
dir_neuron_FE = f"{project_dir}/neuron_group/neurons_FE0"
dir_in2fe0 = f"{project_dir}/syn_out/epoch_0/seg_0_10/in2fe0"

f = ROOT.TFile('result.root', 'RECREATE')
nt = ROOT.TNtuple('nt', 'nt', 'xi:yi:xe:ye:theta:order')
nte = ROOT.TNtuple('nte', 'nt', 'x:y:theta:order')
nti = ROOT.TNtuple('nti', 'nt', 'x:y')

neuron_in = read_data(dir_neuron_in, 0)
neuron_FE = read_data(dir_neuron_FE, 0)
S_in2fe0 = read_data(dir_in2fe0, 0)

xi = neuron_in['x']
yi = neuron_in['y']
xe = neuron_FE['x']
ye = neuron_FE['y']
theta_RF = neuron_FE['theta_RF']
order_RF = neuron_FE['order_RF']

for x, y in zip(xi, yi):
    nti.Fill(x, y)

for x, y, t, o in zip(xe, ye, theta_RF, order_RF):
    nte.Fill(x, y, t, o)

for i, j in zip(S_in2fe0['i'], S_in2fe0['j']):
    nt.Fill(xi[i], yi[i], xe[j], ye[j], theta_RF[j], order_RF[j])

cc = ROOT.TCanvas()
cc.cd()
nte.SetMarkerStyle(20)
nte.SetMarkerSize(2)
nt.SetMarkerStyle(24)
nti.Draw("y:x")
nte.Draw("y:x", "", "same")

for x, y in set(zip(xe, ye)):
    for xt, yt, t in set(zip(xe, ye, theta_RF)):
        if x != xt or y != yt:
            continue
        for j,t1 in enumerate(list(set(theta_RF))):
            #nti.Draw("y:x")
            #nte.Draw("y:x", "", "same")
            if t != t1:
                continue 
            for i, o in enumerate(list(set(order_RF))):
                nt.SetMarkerColor(i%5+j%5+1)
                condition = f"abs(theta -{t})<0.1 && order == {o} && abs(ye-{y})<0.1 && abs(xe-{x})<0.1"
                nt.Draw("yi:xi", condition, "same")
                cc.Modified()
                cc.Update()
                input(f"x: {x}, y: {y}, theta: {t}, order: {o}")
            #cc.Clear()

ROOT.gDirectory.Clear()

f.cd()
nt.Write()
nti.Write()
nte.Write()
f.Close()
