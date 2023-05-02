{
    vector<pair<int,float>> a;
    vector<pair<int,float>> b;

    a.push_back(make_pair(1, 10));
    a.push_back(make_pair(2, 20));
    a.push_back(make_pair(3, 30));
    a.push_back(make_pair(4, 40));
    a.push_back(make_pair(5, 50));
    a.push_back(make_pair(6, 50));

    b.push_back(make_pair(1, 100));
    b.push_back(make_pair(2, 200));
    b.push_back(make_pair(3, 300));
    b.push_back(make_pair(4, 400));
    b.push_back(make_pair(5, 500));

    for(int i = 0; i<a.size(); i++) {
        auto c = a[i];
        auto it = find_if(b.begin(), b.end(), [&c](pair<int, float> &elem) {return elem.first==c.first;});
        if(it!=b.end())
            cout<< "a[i].first: "<<a[i].first<<" a[i].second: "<<a[i].second<<" b.first: "<<it->first<<" b.second: "<<it->second<<endl;

    }
}
