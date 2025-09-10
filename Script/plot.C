{
    float  i, j, w, d;
    ifstream fin;

    TNtuple* nt = new TNtuple("nt", "", "i:j:w:d");

    fin.open ("out", ifstream::in);
    while (fin.good()) {
        fin >> i>>j>>w>>d; 
        nt->Fill(i, j, w, d);
    }
}

