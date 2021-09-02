{ // simulate 2-bit ADC
  TFile result("adc.root", "RECREATE");
  //amp: test pulse amplitude 
  //adc: adc value of a input pulse
  TNtuple *nt = new TNtuple("nt", "", "amp:adc");

  //th0: threshold of comparator c0
  //th1: threshold of comparator c1
  //th2: threshold of comparator c2
  //th3: threshold of comparator c3
  //c0,c1,c2,c3: 0:OFF 1:ON, comparator0, 1, 2, 3
  TNtuple *nt_detail = new TNtuple("nt_detail", "", "amp:c0:c1:c2:c3:th0:th1:th2:th3:adc");

  const int n_pulse = 50000;  // number of test pulse
  const int n_adc = 4;  //.. number of ADCs

  float amp_noise = 2;   // Gaussian width of input pulse amplitude

  float thres_mean[n_adc] = {30, 40, 50, 60};  // Gaussian mean of threshod of adc0, adc1, adc2, adc3
  float thres_width[n_adc] = {2, 2, 2, 2};  // Gaussian width of the threshold of adc0, adc1, adc2, adc3

  for(int i = 0; i<n_pulse; i++) {
    // input amplitude witha flat distribution
    float amp = gRandom->Rndm()*100;
    float amp_with_noise = gRandom->Gaus(amp, amp_noise);

    // threshold for each comparator
    float thres[n_adc] = {0};
    for(int it = 0; it<n_adc; it++) 
      thres[it] = gRandom->Gaus(thres_mean[it], thres_width[it]);

    // comparator 0-3 initially OFF
    int c0 = 0;
    int c1 = 0;
    int c2 = 0;
    int c3 = 0;
    // now determind the ADC value of this test pulse
    float adc = -1;  // initial value
    if(amp_with_noise >= thres[0] && amp_with_noise < thres[1]) {   // comparator C0 ON
      adc = 0;  // this test pulse output adc0
      c0=1;  
    } else if(amp_with_noise >= thres[1] && amp_with_noise <thres[2])  {  // comparator C0 and C1 ON
      adc = 1;  // this test pulse output adc1
      c0=1;
      c1=1;
    } else if(amp_with_noise >= thres[2] && amp_with_noise <thres[3])  {// comparator C0,C1 and C2 ON
      adc = 2;  // this test pulse output adc2
      c0=1;
      c1=1;
      c2=1;
    } else if(amp_with_noise >= thres[3]) {// comparator C0,C1,C2 and C3 ON
      c0=1;
      c1=1;
      c2=1;
      c3=1;
      adc = 3; // this test pulse output adc3
    }

    nt->Fill(amp,adc);
    nt_detail->Fill(amp, c0, c1, c2, c3, thres[0], thres[0], thres[2], thres[3], adc);
  }
  // make some plot for nt
  TCanvas *c0 = new TCanvas("c0", "", 800, 600);
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
  hall->SetMinimum(0);
  hadc->SetLineColor(1);
  h0->SetLineColor(adc_color[0]);
  h1->SetLineColor(adc_color[1]);
  h2->SetLineColor(adc_color[2]);
  h3->SetLineColor(adc_color[3]);

  hall->GetXaxis()->CenterTitle();
  hall->GetYaxis()->CenterTitle();
  hall->GetXaxis()->SetTitle("Amplitude");
  hall->GetYaxis()->SetTitle("Counts");

  TLegend* legend0 = new TLegend(0.65,0.15,0.9,0.6, "", "NDC" );
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
  c0->SaveAs("amp.gif");

  //
  TCanvas *c1 = new TCanvas("c1", "", 800, 600);
  gStyle->SetOptStat(0);
  nt->SetLineWidth(2);
  hall->Draw("same");
  hadc->Draw("same");
  nt->Draw("amp>>hi1", "adc!=-1 && adc!=0 ", "same"); // input amp with adc1 || adc2 || adc3
  nt->Draw("amp>>hi2", "adc!=-1 && adc!=0 && adc!=1", "same"); // input amp with adc2 || adc3
  nt->Draw("amp>>hi3", "adc!=-1 && adc!=0 && adc!=1 && adc!=2", "same"); // input amp with adc3

  hadc->SetLineColor(adc_color[0]);
  hi1->SetLineColor(adc_color[1]);
  hi2->SetLineColor(adc_color[2]);
  hi3->SetLineColor(adc_color[3]);

  for(int i = 0; i<n_adc; i++) {
    mean_thres[i]->SetLineWidth(5);
    mean_thres[i]->SetLineStyle(2);
    mean_thres[i]->SetLineColor(adc_color[i]);
    mean_thres[i]->Draw("same");
  }
  TLegend* legend1 = new TLegend(0.6,0.15,0.9,0.6, "", "NDC" );
  legend1->SetFillColor(0);
  legend1->SetBorderSize(0);
  legend1->Draw();

  legend1->AddEntry(hall, "all input amp", "L");
  legend1->AddEntry(hadc, "amp with adc0||adc1||adc2||adc3", "L");
  legend1->AddEntry(hi1, "amp with adc1||adc2||adc3", "L");
  legend1->AddEntry(hi2, "amp with adc2||adc3", "L");
  legend1->AddEntry(hi3, "amp with adc3", "L");
  legend1->SetTextFont(42);
  legend1->SetTextSize(0.03);

  //. now fit with error function
  TF1 *f1 = new TF1("f1","[0]+[0]*TMath::Erf((x-[1])/sqrt(2)/[2])",0, 100);
  f1->SetLineColor(1);
  f1->SetParameters(100, 20, 3);
  hadc->Fit(f1);
  f1->SetParameters(100, 20, 3);
  hi1->Fit(f1);
  f1->SetParameters(100, 20, 3);
  hi2->Fit(f1);
  f1->SetParameters(100, 60, 3);
  hi3->Fit(f1);
  c1->SaveAs("amp_int.gif");

  // save the file
  result.cd();
  nt->Write();
  nt_detail->Write();
}
