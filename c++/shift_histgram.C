void shifted_hist(TH1F* h_org, TH1F* h_new, float offset = 0)
{
  for(int i =0; i<h_org->GetNbinsX(); i++) {
    float x = h_org->GetBinCenter(i+1);
    int bincontent = h_org->GetBinContent(i+1);

    float x_new = x - offset;  // new bin center

    int new_bin_id = h_new->FindBin(x_new);
    h_new->SetBinContent(new_bin_id, bincontent);
  }
}
//
void shift_histgram()
{
  // histogram before shift
  TH1F* h = new TH1F("h", "", 100, 0, 100);
  for(int i = 0; i<10000; i++) {
    h->Fill(gRandom->Gaus(50, 5));
  }

  // after shift
  float offset = 10;
  TH1F* hnew = new TH1F("hnew", "", 100, 0, 100);
  shifted_hist(h, hnew, offset);

  // add up the two histogram
  TH1F* htot = (TH1F*)h->Clone("htot");
  htot->Add(hnew);

  // plot
  h->SetLineWidth(2);
  hnew->SetLineWidth(2);
  htot->SetLineWidth(2);
  h->SetLineColor(1);
  hnew->SetLineColor(4);
  htot->SetLineColor(2);
  h->SetMaximum(1200);
  h->Draw();
  hnew->Draw("same");
  htot->Draw("same");
}
