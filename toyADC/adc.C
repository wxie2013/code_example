{
  TNtuple *nt = new TNtuple("nt", "", "amp:pass0:pass1:th0:th1:adc0:adc1");
  for(int i = 0; i<10000; i++) {
    float amp = gRandom->Gaus(30, 4);
    if (gRandom->Rndm() > 0.5)
      amp = gRandom->Gaus(40, 4);


    float thres0 = gRandom->Gaus(30, 4);
    float thres1 = gRandom->Gaus(40, 4);

    int pass0 = 0;
    int pass1 = 0;
    if(amp > thres0) 
      pass0 = 1;

    if(amp > thres1) 
      pass1 = 1;

    float adc0 = 0;
    float adc1 = 0;
    if(pass0 ==1 && pass1==0) 
      adc0 = 1;
    
    if(pass0==1 && pass1==1) 
      adc1=1;

    nt->Fill(amp, pass0, pass1, thres0, thres1, adc0, adc1);
  }
}
