void test_rand()
{
  TNtuple* nt = new TNtuple("nt", "", "x");

  float x = 0;
  for(int i = 0; i<10000; i++) {
      x = (float) rand()/RAND_MAX;
      nt->Fill(x);
  } 

  nt->Draw("x");
}
