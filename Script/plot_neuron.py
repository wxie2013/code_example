import csv, ROOT
file = ROOT.TFile("neuron.root", "RECREATE");
nt = ROOT.TNtuple("nt", "", "grp:x:y:theta_RF:order_RF")
with open('rank0.csv', newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
    for row in spamreader:
        w = (', '.join(row).split(','))
        try:
            print(int(w[4]), float(w[5]), float(w[6]), float(w[7]), float(w[8]))
            nt.Fill(int(w[4]), float(w[5]), float(w[6]), float(w[7]), float(w[8]))
        except:
            print(w[4], w[5], w[6], w[7], w[8])
file.cd()
nt.Write()
file.Close()

