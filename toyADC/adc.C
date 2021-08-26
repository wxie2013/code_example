{
  //amp: test pulse amplitude 
  //th0: threshold of comparator c0
  //th1: threshold of comparator c1
  //th2: threshold of comparator c2
  //th3: threshold of comparator c3
  //is_adc0: if 1, this pulse output adc0, if 0 this pulse produce other adc values 
  //is_adc1: if 1, this pulse output adc1, if 0 this pulse produce other adc values 
  //is_adc2: if 1, this pulse output adc2, if 0 this pulse produce other adc values 
  //is_adc3: if 1, this pulse output adc3, if 0 this pulse produce other adc values 
  TNtuple *nt = new TNtuple("nt", "", "amp:th0:th1:th2:th3:is_adc0:is_adc1:is_adc2:is_adc3");

  const int n_pulse = 50000;  // number of test pulse
  const int n_adc = 4;  //.. number of ADCs

  float amp_mean[n_adc] = {30, 40, 50, 60};  // Gaussian mean of input pulse amplitude 
  float amp_width[n_adc] = {4, 4, 4, 4};   // Gaussian width of input pulse amplitude

  float thres_mean[n_adc] = {30, 40, 50, 60};  // Gaussian mean of threshod of adc0, adc1, adc2, adc3
  float thres_width[n_adc] = {4, 4, 4, 4};  // Gaussian width of the threshold of adc0, adc1, adc2, adc3

  for(int i = 0; i<n_pulse; i++) {
    int idx = int(gRandom->Rndm()/0.25); // each amp_mean has 25% probility to generator pulse

    // amplitude of input test pulse
    float amp = gRandom->Gaus(amp_mean[idx], amp_width[idx]);

    // threshold for each comparator
    float thres[n_adc] = {0};
    for(int it = 0; it<n_adc; it++) 
      thres[it] = gRandom->Gaus(thres_mean[it], thres_width[it]);

    // now determind the ADC value of this test pulse
    bool is_adc0 = false;
    bool is_adc1 = false;
    bool is_adc2 = false;
    bool is_adc3 = false;
    if(amp >= thres[0] && amp < thres[1]) 
      is_adc0 = true;  // this test pulse output adc0
    else if(amp >= thres[1] && amp <thres[2]) 
      is_adc1 = true;  // this test pulse output adc1
    else if(amp >= thres[2] && amp <thres[3]) 
      is_adc2 = true;  // this test pulse output adc2
    else if(amp >= thres[3]) 
      is_adc3 = true;  // this test pulse output adc3

    nt->Fill(amp, thres[0], thres[1], thres[2], thres[3], is_adc0, is_adc1, is_adc2, is_adc3);
  }
  // make some plot
  TCanvas *c = new TCanvas("c", "", 1400, 1000);
  c->Divide(2,1);
  c->cd(1);
