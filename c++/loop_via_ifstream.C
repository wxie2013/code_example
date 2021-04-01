#include "MyTree_3.C"

void run()
{
  ifstream file_stream("file.list");
  int nfile_tot = 2;

  string filename;
  int ifile = 0;
  while(true) {

    file_stream >> filename;

    if(file_stream.eof())
      break;

    ifile++;

    cout << "file  = " << ifile<<" name = "<<filename <<endl;

    //TFile fin(filename.c_str());

    //if(fin.IsZombie())
    //  continue;

    //TTree * tree = (TTree*)fin.Get("DecayTree");

    //MyTree_3 t(tree);

    //string output_name = "nt"+std::to_string(ii)+".root";
    //t.Loop(output_name);

    //fin.Close();
  }
}
