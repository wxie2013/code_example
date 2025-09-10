{
    float  i, j, d, w;
    ifstream fin;

    TNtuple* nt = new TNtuple("nt", "", "i:j:d:w");

    fin.open ("out", ifstream::in);
    while (fin.good()) {
        fin >> i>>j>>w>>d; 
        nt->Fill(i, j, d, w);
    }

    c1 = new TCanvas("c1", "", 700, 500);
    c1->SetLogy(1);
    nt->Draw("w");
}

