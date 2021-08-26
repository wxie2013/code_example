{
  //amp: test pulse amplitude 
  //th0: threshold of comparator c0
  //th1: threshold of comparator c1
  //th2: threshold of comparator c2
  //th3: threshold of comparator c3
  //adc: adc value of a input pulse
  TNtuple *nt = new TNtuple("nt", "", "amp:th0:th1:th2:th3:adc");

  const int n_pulse = 50000;  // number of test pulse
  const int n_adc = 4;  //.. number of ADCs

  float amp_mean[n_adc] = {30, 40, 50, 60};  // Gaussian mean of input pulse amplitude 
  float amp_width[n_adc] = {5, 5, 5, 5};   // Gaussian width of input pulse amplitude

  float thres_mean[n_adc] = {30, 40, 50, 60};  // Gaussian mean of threshod of adc0, adc1, adc2, adc3
  float thres_width[n_adc] = {2, 2, 2, 2};  // Gaussian width of the threshold of adc0, adc1, adc2, adc3

  for(int i = 0; i<n_pulse; i++) {
    int idx = int(gRandom->Rndm()/0.25); // each amp_mean has 25% probility to generator pulse

    // amplitude of input test pulse
    float amp = gRandom->Gaus(amp_mean[idx], amp_width[idx]);

    // threshold for each comparator
    float thres[n_adc] = {0};
    for(int it = 0; it<n_adc; it++) 
      thres[it] = gRandom->Gaus(thres_mean[it], thres_width[it]);

    // now determind the ADC value of this test pulse
    float adc = -1;  // initial value
    if(amp >= thres[0] && amp < thres[1]) 
      adc = 0;  // this test pulse output adc0
    else if(amp >= thres[1] && amp <thres[2]) 
      adc = 1;  // this test pulse output adc1
    else if(amp >= thres[2] && amp <thres[3]) 
      adc = 2;  // this test pulse output adc2
    else if(amp >= thres[3]) 
      adc = 3; // this test pulse output adc3

    nt->Fill(amp, thres[0], thres[1], thres[2], thres[3], adc);
  }
  // make some plot
  TCanvas *c = new TCanvas("c", "", 800, 600);
  gStyle->SetOptStat(0);
  nt->SetLineWidth(2);
  TH1F *hall = new TH1F("hall", "", 200, 8, 100);
  hall->SetLineWidth(2);
  nt->Draw("amp>>hall");  // all input test amp include those below lowest threshold
  nt->Draw("amp>>hadc", "adc !=-1", "same"); // input amp with a certain adc value
  nt->Draw("amp>>h0", "adc ==0 ", "same"); // input amp with adc0
  nt->Draw("amp>>h1", "adc ==1 ", "same"); // input amp with adc1
  nt->Draw("amp>>h2", "adc ==2 ", "same"); // input amp with adc2
  nt->Draw("amp>>h3", "adc ==3 ", "same"); // input amp with adc3

  TLine * mean_thres[n_adc];
  int adc_color[n_adc] = {2, 3, 4, 6};
  for(int i = 0; i<n_adc; i++) {
    mean_thres[i] = new TLine(thres_mean[i], 0, thres_mean[i], 500);
    mean_thres[i]->SetLineWidth(5);
    mean_thres[i]->SetLineStyle(2);
    mean_thres[i]->SetLineColor(adc_color[i]);
    mean_thres[i]->Draw("same");
  }
  hall->SetLineStyle(2);
  hadc->SetLineColor(1);
  h0->SetLineColor(adc_color[0]);
  h1->SetLineColor(adc_color[1]);
  h2->SetLineColor(adc_color[2]);
  h3->SetLineColor(adc_color[3]);

  hall->GetXaxis()->CenterTitle();
  hall->GetYaxis()->CenterTitle();
  hall->GetXaxis()->SetTitle("Amplitude");
  hall->GetYaxis()->SetTitle("Counts");

  TLegend* legend0 = new TLegend(0.65,0.50,0.9,0.9, "", "NDC" );
  legend0->SetFillColor(0);
  legend0->SetBorderSize(0);
  legend0->Draw();

  legend0->AddEntry(hall, "all input amp", "L");
  legend0->AddEntry(hadc, "amp with any adc ", "L");
  legend0->AddEntry(h0, "amp with adc0", "L");
  legend0->AddEntry(h1, "amp with adc1", "L");
  legend0->AddEntry(h2, "amp with adc2", "L");
  legend0->AddEntry(h3, "amp with adc3", "L");
  legend0->SetTextFont(42);
  legend0->SetTextSize(0.03);

}
