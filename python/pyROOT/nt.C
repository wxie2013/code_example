void nt(TNtuple* nt)
{
    vector<float> a;
    for(int i = 0; i<20; i++) {
        a.push_back(i);
    }

    nt->Fill(a.data());
}
