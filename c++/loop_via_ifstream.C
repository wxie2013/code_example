//////
void loop_via_ifstream(int istart, int iend)
{
  ifstream file_stream("file.list");
  int nfile_tot = 2;

  string filename;
  int ifile = 0;
  while(true) {

    file_stream >> filename;

    if(file_stream.eof())
      break;

    if(ifile < istart) {
      ifile++;
      continue;
    }

    if(ifile >= iend)
      break;

    cout << "file  = " << ifile<<" name = "<<filename <<endl;

    //____ your analysis code
    TFile fin(filename.c_str());

    if(fin.IsZombie()) {
      ifile ++;   // you need this here to keep track of the file
      continue;
    }

    //TTree * tree = (TTree*)fin.Get("DecayTree");

    string output_name = "nt"+std::to_string(istart)+"_"+std::to_string(iend)+".root";
    cout<<" output_name: "<<output_name<<endl;

    fin.Close();
    //_____ end of your analysis code

    //
    ifile++;
  }
}
