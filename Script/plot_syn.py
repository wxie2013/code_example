import csv, ROOT
file = ROOT.TFile("syn.root", "RECREATE");
nt = ROOT.TNtuple("nt", "", "i:j:w:d")
with open('rank0.csv', newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
    for row in spamreader:
        w = (', '.join(row).split(','))
        try:
            nt.Fill(int(w[0]), int(w[1]), float(w[2]), float(w[3]))
        except:
            pass
file.cd()
nt.Write()
file.Close()

