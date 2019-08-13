{
    float  x;
    ifstream fin;

    TNtuple* nt = new TNtuple("nt", "", "x");

    fin.open ("oo.dat", ifstream::in);
    while (fin.good()) {
        fin >> x; 
        nt->Fill(x);
    }

    nt->Draw("x");

}

