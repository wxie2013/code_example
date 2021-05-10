typedef tuple<string, float, float, float> mytuple;

//
bool compare_fun(const mytuple &a, const mytuple &b)
{
  return get<3>(a) > get<3>(b);
}

//
void std_tuple()
{
  ifstream file_stream("eff_nt.lis");

  float eff = 0;
  float correct_entries = 0;
  float tot_entries = 0;
  string filename;
  int ifile = 0;
  
  vector<mytuple> result;

  while(true) {

    file_stream >> filename;

    if(file_stream.eof())
      break;

    ifile++;


    TFile fin(filename.c_str());
    if(fin.IsZombie())
      continue;

    TNtuple * eff_nt = (TNtuple*)fin.Get("eff_nt");
    eff_nt->SetBranchAddress("eff", &correct_entries);

    tot_entries = eff_nt->GetEntries();
    eff_nt->GetEntry(0);

    eff = correct_entries/tot_entries;

    result.push_back(std::make_tuple(filename, tot_entries, correct_entries, eff));

    fin.Close();
  }

  //
  sort(result.begin(), result.end(), compare_fun);
  for(int i = 0; i<result.size(); i++) {
    cout <<"...: "<<i<<" name = "<<get<0>(result[i]) <<" ... total: "<<get<1>(result[i])<<" correct entries: "<<get<2>(result[i])<<" . eff: "<<get<3>(result[i])<<endl;
  }
}

