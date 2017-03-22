void histogram_from_ascii(string filename = "output.dat"){
   
   Float_t         Nmax;
   Float_t         Xo;
   Float_t         Xmax;
   Float_t         lamda;
   Float_t         Xf_cal;
   Float_t         Xf_csk;

   ifstream inputFile(filename.c_str());

      if(inputFile.fail()) {
         cerr << "Cannot open file: " << filename << endl;
         exit(-1);
        }

   TH1F *hNmax   = new TH1F("hNmax","Nmax distribution",20,160E6,230E6);
   TH1F *hXo     = new TH1F("hXo","Xo distribution",20,-100,200);
   TH1F *hXmax   = new TH1F("hXmax","Xmax distribution",20,600,1200);
   TH1F *hlamda  = new TH1F("hlamda","lamda distribution",20,0,150);
   TH1F *hXf_cal = new TH1F("hXf_cal","Xf_cal distribution",10,-30,100);
   TH1F *hXf_csk = new TH1F("hX_csk","Xf_csk distribution",10,0,150E4);

        if (inputFile.is_open()) {
                while (!inputFile.eof()) {
                        inputFile >> Nmax >> Xo >> Xmax >> lamda >> Xf_cal >> Xf_csk;
                        if( inputFile.eof() ) break;                    // necessary to avoid reading the last line twice
                        
                         hNmax   -> Fill(Nmax);
                         hXo     -> Fill(Xo);
                         hXmax   -> Fill(Xmax);
                         hlamda  -> Fill(lamda);
                         hXf_cal -> Fill(Xf_cal);
                         hXf_csk -> Fill(Xf_csk);
                         //cout<<Xo<<endl;
                }
        }

   //hXo->Print("all");    

   TCanvas *c1 = new TCanvas("c1","c1");
   TFile *salida = new TFile("salida.root","recreate");
   //hXo->SetTitle("Average Cost per Nation");
   //hXo->DrawCopy();

   //c1->SetFillColor(42);
   c1->Divide(2,3);
 
   c1->cd(1);
   hNmax->Draw();
   hNmax->GetXaxis()->SetTitle("Numero de particulas");
   hNmax->GetXaxis()->CenterTitle();
   hNmax->GetYaxis()->SetTitle("Frecuencia");
   hNmax->GetYaxis()->CenterTitle();
   hNmax->Fit("gaus");
   hNmax->SetMarkerColor(kRed);

   c1->cd(2);
   hXo->Draw();
   hXo->GetXaxis()->SetTitle("");
   hXo->GetXaxis()->CenterTitle();
   hXo->GetYaxis()->SetTitle("Frecuencia");
   hXo->GetYaxis()->CenterTitle();

   c1->cd(3);
   hXmax->Draw();
   hXmax->GetXaxis()->SetTitle("Prof atmosferica g/cm2");
   hXmax->GetXaxis()->CenterTitle();
   hXmax->GetYaxis()->SetTitle("Frecuencia");
   hXmax->GetYaxis()->CenterTitle();

   c1->cd(4);
   hlamda->Draw();
   hlamda->GetXaxis()->SetTitle("");
   hlamda->GetXaxis()->CenterTitle();
   hlamda->GetYaxis()->SetTitle("Frecuencia");
   hlamda->GetYaxis()->CenterTitle();

   c1->cd(5);
   hXf_cal->Draw();
   hXf_cal->GetXaxis()->SetTitle("Prof atmosferica g/cm2");
   hXf_cal->GetXaxis()->CenterTitle();
   hXf_cal->GetYaxis()->SetTitle("Frecuencia");
   hXf_cal->GetYaxis()->CenterTitle();

   c1->cd(6);
   hXf_csk->Draw();
   hXf_csk->GetXaxis()->SetTitle("Prof atmosferica g/cm2");
   hXf_csk->GetXaxis()->CenterTitle();
   hXf_csk->GetYaxis()->SetTitle("Frecuencia");
   hXf_csk->GetYaxis()->CenterTitle();

   c1->SaveAs("outpud.pdf");
   
   c1->Update();
   c1->Write();
   
   salida->Close();
   inputFile.close();
   return;
}
