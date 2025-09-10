{
    float  i, t;
    ifstream fin;

    TNtuple* nt = new TNtuple("nt", "", "i:t");

    fin.open ("out", ifstream::in);
    while (fin.good()) {
        fin >> i>>t; 
        nt->Fill(i, t);
    }
}

