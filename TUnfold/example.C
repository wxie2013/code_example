#include <iostream>
#include <TRandom3.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TMath.h>
#include <TArrayD.h>
#include "TUnfoldDensity.h"

// -----------------------------------------------------------------------------
// 1. Physical Functions
// -----------------------------------------------------------------------------
// True pT distribution following a power-law: dN/dpT ~ pT^(-5)
Double_t true_density_data(Double_t pt) {
    return 1e7 * TMath::Power(pt, -5.0);
}

// Efficiency function: gradually rises from 1e-4 at 2.0 GeV to 1.0 at 30.0 GeV
// Formula: eff(pt) = 1e-4 * (pt / 2.0)^k where k = 4.0 / log10(30/2)
Double_t efficiency(Double_t pt) {
    Double_t const xmin = 2.0;
    Double_t const xmax = 30.0;
    Double_t k = 4.0 / TMath::Log10(xmax / xmin);
    Double_t eff = 1e-4 * TMath::Power(pt / xmin, k);
    return TMath::Min(eff, 1.0);
}

// Helper to create Logarithmic Bins (Crucial for Power-Law distributions!)
TArrayD GetLogBins(Int_t nBins, Double_t min, Double_t max) {
    TArrayD bins(nBins + 1);
    Double_t logMin = TMath::Log10(min);
    Double_t logMax = TMath::Log10(max);
    Double_t delta = (logMax - logMin) / nBins;
    for (Int_t i = 0; i <= nBins; i++) {
        bins[i] = TMath::Power(10.0, logMin + i * delta);
    }
    return bins;
}

// -----------------------------------------------------------------------------
// 2. Main Macro
// -----------------------------------------------------------------------------
void example() {
    gSystem->Load("libunfold.so");
    gStyle->SetOptStat(0);
    TRandom3* rnd = new TRandom3(42);

    // Binning bounds
    Double_t const xminGen = 2.0;
    Double_t const xmaxGen = 30.0;
    Int_t const nGen = 15; // 15 generator bins

    Double_t const xminDet = 2.0;
    Double_t const xmaxDet = 30.0;
    Int_t const nDet = 30; // 30 detector bins (2x finer)

    // Generate Logarithmic Bins
    TArrayD binsGenArray = GetLogBins(nGen, xminGen, xmaxGen);
    TArrayD binsDetArray = GetLogBins(nDet, xminDet, xmaxDet);

    // --- Step A: Define Histograms with Log Binning ---
    TH1D *histMgenData = new TH1D("MgenData", "True Data", nGen, binsGenArray.GetArray());
    TH1D *histMdetData = new TH1D("MdetData", "Measured Data", nDet, binsDetArray.GetArray());

    // 2D Response Matrix
    TH2D *histMdetGenMC = new TH2D("MdetgenMC", "Response Matrix;p_{T}^{det};p_{T}^{gen}",
                                   nDet, binsDetArray.GetArray(),
                                   nGen, binsGenArray.GetArray());

    // --- Step B: Fill MC Response Matrix (With extremely low efficiency) ---
    // Generate flat MC sample so we have high statistics in the very-low efficiency region
    Int_t const nEventsMC = 100000000; // 10 million events to capture 1e-4 probability
    for (Int_t i = 0; i < nEventsMC; ++i) {
        Double_t mGen = rnd->Uniform(xminGen, xmaxGen); 
        Double_t eff = efficiency(mGen);
        
        if (rnd->Rndm() < eff) {
            // Reconstructed event: smear by 10% resolution (standard for pT resolution)
            Double_t mDet = rnd->Gaus(mGen, 0.10 * mGen); 
            if (mDet >= xminDet && mDet <= xmaxDet) {
                histMdetGenMC->Fill(mDet, mGen);
            } else {
                // Migrated out of detector bounds -> Underflow
                histMdetGenMC->Fill(-1.0, mGen);
            }
        } else {
            // Lost event -> Fill the Underflow bin of the Detector axis
            histMdetGenMC->Fill(-1.0, mGen);
        }
    }

    // --- Step C: Fill Pseudo-Data (Power-Law Distribution) ---
    // We use inverse transform sampling to generate pure pT^(-5) events
    Int_t const nEventsData = 20000000; // 2 million data events
    Double_t pow_min = TMath::Power(xminGen, -4.0);
    Double_t pow_max = TMath::Power(xmaxGen, -4.0);

    for (Int_t i = 0; i < nEventsData; ++i) {
        Double_t u = rnd->Rndm();
        Double_t mGen = TMath::Power(u * (pow_max - pow_min) + pow_min, -0.25);
        histMgenData->Fill(mGen);

        Double_t eff = efficiency(mGen);
        if (rnd->Rndm() < eff) {
            Double_t mDet = rnd->Gaus(mGen, 0.10 * mGen);
            if (mDet >= xminDet && mDet <= xmaxDet) {
                histMdetData->Fill(mDet);
            }
        }
    }

    // --- Step D: Set up TUnfoldDensity ---
    TUnfoldDensity unfold(histMdetGenMC, TUnfold::kHistMapOutputVert);
    if (unfold.SetInput(histMdetData) >= 10000) {
        std::cerr << "Unfolding matrix system is under-constrained!" << std::endl;
        return;
    }

    // --- Step E: Run Unfolding with L-Curve Scan ---
    Int_t nScan = 30;
    Double_t tauMin = 0.0;
    Double_t tauMax = 0.0;
    TGraph *lCurve = nullptr;
    TSpline *logTauX = nullptr;
    TSpline *logTauY = nullptr;

    unfold.ScanLcurve(nScan, tauMin, tauMax, &lCurve, &logTauX, &logTauY);
    Double_t bestTau = unfold.GetTau();
    std::cout << "🎯 Optimal Tau: " << bestTau << std::endl;

    // --- Step F: Retrieve Output and Total Uncertainties ---
    TH1 *histUnfolded = unfold.GetOutput("Unfolded");
    TH2 *histEmatTotal = unfold.GetEmatrixTotal("EmatTotal");

    TH1D *histTotalError = new TH1D("TotalError", "Unfolded Result", nGen, binsGenArray.GetArray());
    for (Int_t bin = 1; bin <= nGen; bin++) {
        histTotalError->SetBinContent(bin, histUnfolded->GetBinContent(bin));
        histTotalError->SetBinError(bin, TMath::Sqrt(histEmatTotal->GetBinContent(bin, bin)));
    }

    // --- Step G: Plotting (Strictly as dN/dpT using Bin Width Scale) ---
    TCanvas *c1 = new TCanvas("c1", "Power-Law pT Unfolding", 800, 600);
    c1->SetLogx();
    c1->SetLogy();

    // Scale by "width" to display density (dN/dpT) correctly across logarithmic bins
    histMgenData->Scale(1.0, "width");
    histMdetData->Scale(1.0, "width");
    histTotalError->Scale(1.0, "width");

    // Plot true spectrum
    histMgenData->SetLineColor(kRed);
    histMgenData->SetLineWidth(2);
    histMgenData->SetTitle("TUnfold Power-Law pT Unfolding (10^{-4} #rightarrow 1.0 Efficiency);p_{T} [GeV];dN/dp_{T} [GeV^{-1}]");
    histMgenData->GetYaxis()->SetRangeUser(5.0, histMgenData->GetMaximum() * 5.0);
    histMgenData->Draw("HIST");

    // Plot raw measured data
    histMdetData->SetLineColor(kBlack);
    histMdetData->SetLineStyle(2);
    histMdetData->SetLineWidth(2);
    histMdetData->Draw("SAME HIST");

    // Plot unfolded results
    histTotalError->SetMarkerStyle(20);
    histTotalError->SetMarkerSize(1.2);
    histTotalError->SetMarkerColor(kGreen + 2);
    histTotalError->SetLineColor(kGreen + 2);
    histTotalError->SetLineWidth(2);
    histTotalError->Draw("SAME E1");

    TLegend *leg = new TLegend(0.5, 0.65, 0.88, 0.88);
    leg->SetBorderSize(1);
    leg->AddEntry(histMgenData, "Ground Truth dN/dp_{T}", "l");
    leg->AddEntry(histMdetData, "Measured dN/dp_{T} (Smeared, Inefficient)", "l");
    leg->AddEntry(histTotalError, "Unfolded dN/dp_{T} (Efficiency Corrected)", "pe");
    leg->Draw();

    c1->SaveAs("PowerLaw_Unfolding_Result.png");
}

