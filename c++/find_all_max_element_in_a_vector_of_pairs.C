//.. note: run it in ROOT as a macro
{
  vector<pair<int, vector<pair<int, int>>>> spike_rate_for_each_label(5);
  for(int i = 0; i<5; i++) {
    for(int m =0; m<10; m++) {
      spike_rate_for_each_label[i].second.push_back(std::make_pair(i, gRandom->Rndm(0)*10));
    }
  }
  for(int i = 0; i<5; i++) {
    for(int m = 0; m<spike_rate_for_each_label[i].second.size(); m++) {
      cout<<spike_rate_for_each_label[i].second[m].second<<" ";
    }
    cout<<endl;
  }
  for(int i = 0; i<5; i++) {
    vector<int> pos;
    auto it_max = std::max_element(spike_rate_for_each_label[i].second.begin(), 
        spike_rate_for_each_label[i].second.end(), 
        [](const auto &e1, const auto &e2) {return e1.second < e2.second;});

    while(it_max != spike_rate_for_each_label[i].second.end()) {
      pos.push_back(std::distance(spike_rate_for_each_label[i].second.begin(), it_max));
      it_max = std::find(std::next(it_max), spike_rate_for_each_label[i].second.end(), *it_max);
    }

    cout<<"________________________"<<endl;
    for(int m = 0; m<pos.size(); m++) {
      int idx = pos[m];
      cout<<idx<<" "<<spike_rate_for_each_label[i].second[idx].second<<endl;
    }

  }
}
