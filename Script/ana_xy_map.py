import ROOT
from Brian2.tools.general_tools import *

f = ROOT.TFile('result.root', 'RECREATE')
nt = ROOT.TNtuple('nt', 'nt', 'xe:ye:xi:yi')
nte = ROOT.TNtuple('nte', 'nt', 'x:y')
nti = ROOT.TNtuple('nti', 'nt', 'x:y')
neuron = read_data('neuron', 0)
syn = read_data('S_e2S_input2c', 0)
input2c = read_data('S_input2c', 0)

xi = []
yi = []
xe = neuron['x']
ye = neuron['y']

for i in range(784):
    xi.append(i%28)
    yi.append(28-i//28)
    nti.Fill(xi[i], yi[i])

for x, y in zip(xe, ye):
    nte.Fill(x, y)

pre_id = input2c['i']

for i, j in zip(syn['i'], syn['j']):
    ii = pre_id[j]
    nt.Fill(xe[i], ye[i], xi[ii], yi[ii])

f.cd()
nt.Write()
nti.Write()
nte.Write()
f.Close()
