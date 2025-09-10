import ROOT, math
from Brian2.tools.general_tools import *

def read():
    f = ROOT.TFile('result.root', 'RECREATE')
    nt = ROOT.TNtuple('nt', 'nt', 'xin:yin:xfe:yfe:theta:order')
    nte = ROOT.TNtuple('nte', 'nt', 'x:y')
    nti = ROOT.TNtuple('nti', 'nt', 'x:y')
    neuron = read_data('/home/wxie/Brian2/model/neuron_group/neurons_FE0/', 0)
    input2fe = read_data('/home/wxie/Brian2/model/syn_out/epoch_0/seg_0_1/S_in2fe0/', 0)
    
    xin = []
    yin = []
    xfe = neuron['x']
    yfe = neuron['y']
    theta_RF = neuron['theta_RF']
    order_RF = neuron['order_RF']
    
    for i in range(784):
        xin.append(i%28)
        yin.append(28-i//28)
        nti.Fill(xin[i], yin[i])
    
    for x, y in zip(xfe, yfe):
        nte.Fill(x, y)
    
    pre_id = input2fe['i']
    
    for i, j in zip(input2fe['i'], input2fe['j']):
        nt.Fill(xin[i], yin[i], xfe[j], yfe[j], theta_RF[j], order_RF[j])
    
    f.cd()
    nt.Write()
    nti.Write()
    nte.Write()
    f.Close()

#read()
# plot: one has to copy/past the following code to python prompt to make the marker stype effective
import ROOT
f = ROOT.TFile('result.root', 'READ')
nt = f.Get('nt')
nti = f.Get('nti')
nte = f.Get('nte')
c1 = ROOT.TCanvas("c1", "", 1000, 1000)
nte.SetMarkerStyle(20)

sqrt_nfe = 5
scale = (28-1)/sqrt_nfe
xfe = []
yfe = []
for i in range(sqrt_nfe**2):
    xfe.append(i%sqrt_nfe)
    yfe.append(sqrt_nfe-i//sqrt_nfe-1)

xfe = [(xfe[i]+0.5)*scale for i in range(len(xfe))]
yfe = [(yfe[i]+0.5)*scale for i in range(len(yfe))]

theta = [0, 0.7853981, 1.5707963, 2.3561945]
order = [-1, 0, 1]

nt.SetMarkerStyle(24)
for i in range(sqrt_nfe**2):
    for j in range(len(theta)):
        nti.Draw("y:x")
        nte.Draw("y:x", "", "same")
        for k in range(len(order)):
            nt.SetMarkerColor((k+1)%len(order))
            cond = f"abs(xfe-{xfe[i]})<1e-3 && abs(yfe-{yfe[i]})<1e-3 && abs(theta-{theta[j]})<1e-3 && abs(order-{order[k]})<1e-3"
            print(cond)
            nt.Draw("yin:xin", cond, "same")
            input("")

