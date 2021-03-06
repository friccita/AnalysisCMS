#include "ttdm.h"

void CreateHistograms2( int process );

float cuentita; 

bool doLoop = 1; 

void CreateHistograms(){

	Assign();

	gSystem->mkdir( histoSite, kTRUE );

	//-----

	for(int j = 0; j < nscalar; j++ ){

		if( j != ttDM0001pseudo00100 ) continue;

		cuentita = 0.0; 

		processID[ttDM] = pseudoID[j];	b_name[ANN] = "ANN_tanh_mt2ll80_camille_" + processID[ttDM]; 

		if( doLoop == true ){

			for( int i = 0; i < nprocess; i++ ){

				if ( i == Wg || i == Zg ) continue; 

				CreateHistograms2( i ); 

			}

		}

		else{

			CreateHistograms2( ttDM );

		}

		cout << "\n\n \t yield total = " << cuentita << endl;

	}   // j 
 
	cout << "\n \n The End !!! \n \n" << endl; 

}


void CreateHistograms2( int process ){ 

	//if(  process == data || process == fakes || process == TT || process == TTV ) return; 

	//if ( process != WZ ) return;

	///if ( process == VZ ) return;

	//if ( process != ST ) return;

	//if ( process != WW ) return;

	///if ( process == DY ) return;

	//if ( process != Wg ) return;

	//if ( process != Zg ) return;

	///if ( process == VVV) return;

	if ( process == TT ) return;

	//if ( process !=ttDM) return;


	cout << "\n \t process: " << processID[process] << endl; 

	for( int k = 0; k <= toppTrwdo; k++ ){ 

		if ( k > nominal ) continue;

		//if ( processID[process] == "ttDM0001pseudo00010" && k == EleESdo ) continue;  // 1-pseudo-010 (jefferson)     VALUABLE INFORMATION, DO NOT ERASE !!! 


		if(  process == data  &&  k > nominal  ) continue; 

		cout << "\t \t" << systematicID[k] << endl; 

		TCanvas* c1 = new TCanvas("canvas", "the canvas");
	
		TFile* myfile;

		if( process == data || process == fakes || process == TTV /*|| process == Wg || process == Zg*/ ){ 

			myfile = new TFile( storageSite + minitreeDir[0] + "/TTDM/" + processID[process]  + ".root", "read" ); 

		}

		else{ 

			myfile = new TFile( storageSite + minitreeDir[k] + "/TTDM/" + processID[process] + ".root", "read" ); 

		}


		TString pathway = histoSite + processID[ttDM] + "/";	gSystem -> mkdir( pathway, kTRUE );

		TFile* storagefile; 

		//storagefile = new TFile( pathway + "simple-shapes-TH1.root", "update");

		if( k == nominal ) storagefile = new TFile( pathway + processID[process] +                         ".root", "recreate" );
		if( k >  nominal ) storagefile = new TFile( pathway + processID[process] + "_" + systematicID[k] + ".root", "recreate" );

		TTree* mytree = (TTree*) myfile -> Get( "latino" );

		TCut thecut       = ( process == data || process == fakes ) ? eventW[0] : eventW[k];

		// jefferson and after jefferson
		TCut newselection = ( process == data || process == fakes ) ? selection : selection&&RemovingFakes; 

		// fucking-mum
		//TCut newselection = ( process == TT && ( k == nominal || k == toppTrw )  ) ? selection&&RemovingFakes : selection               ; 

		// nothing
		//TCut newselection = selection; 


                                                           thecut = newselection          *thecut; 
		if ( process == TT    )                    thecut = Form("%4.2f", ttSF   )*thecut; 
		if ( process == DY    )                    thecut = Form("%4.2f", DYSF   )*thecut; 
		if ( process == TT && k != toppTrwdo )     thecut ="eventW_Toppt"         *thecut; 
                if ( process == ttDM  )                    thecut = Form("%4.2f", xs2l   )*thecut;
                if ( process != data && process != fakes ) thecut = Form("%6.3f", thelumi)*thecut;
                if ( process == fakes )                    thecut = Form("%6.3f", 1./15. )*thecut;

		if( (k >= QCDup && k <= PDFdo) && (process != data && process != ttDM && process != fakes && process != ST ) ){

			TH1F* weights = (TH1F*) myfile -> Get( "list_vectors_weights" );

			if( k == QCDup ){

				float qcd_norm_up = weights->GetBinContent(9)/weights->GetBinContent(1);

				thecut = Form("(LHEweight[8]/LHEweight[0])/%7.4f", qcd_norm_up)*thecut;
			
			}	

			if( k == QCDdo ){

				float qcd_norm_do = weights->GetBinContent(5)/weights->GetBinContent(1);

				thecut = Form("(LHEweight[4]/LHEweight[0])/%7.4f", qcd_norm_do)*thecut;
			
			}

			if( k == PDFup ){

				float PDF_norm_up = weights->GetBinContent(10)/weights->GetBinContent(1);

				thecut = Form("(LHEweight[9]/LHEweight[0])/%7.4f", PDF_norm_up)*thecut;
			
			}	

			if( k == PDFdo ){

				float PDF_norm_do = weights->GetBinContent(11)/weights->GetBinContent(1);

				thecut = Form("(LHEweight[10]/LHEweight[0])/%7.4f", PDF_norm_do)*thecut;
			
			}

		}


		TString h_name[nhisto];

		int HowManyVar = 0; 

		for( int i = 0; i < nhisto; i++ ){

			if(	//i ==  nlepton      ||
				//i == lep1pt        || 
				//i == lep1eta       || 
				//i == lep1phi       || 
				//i == lep1mass      ||
				//i == lep2pt        || 
				//i == lep2eta       || 
				//i == lep2phi       || 
				//i == lep2mass      || 
				//i == jet1pt        || 
				//i == jet1eta       || 
				//i == jet1phi       || 
				//i == jet1mass      ||
				//i == jet2pt        || 
				//i == jet2eta       || 
				//i == jet2phi       || 
				//i == jet2mass      ||
				i == metPfType1    || 
				//i == metPfType1Phi ||
				//i == m2l           || 
				i == mt2ll         || 
				//i == mt2lblb       || 
				//i == mtw1          || 
				//i == mtw2          ||
				//i == htjets        || 
				//i == htnojets      ||
				//i == njet          || 
				//i == nbjet30csvv2l || 
				//i == nbjet30csvv2m || 
				//i == nbjet30csvv2t ||  
				//i == dphijet1met   || 
				//i == dphijet2met   || 
				//i == dphijj        || 
				//i == dphijjmet     || 
				//i == dphill        || 
				//i == dphilep1jet1  || 
				//i == dphilep1jet2  || 
				//i == dphilep2jet1  || 
				//i == dphilep2jet2  || 
				//i == dphilmet1     || 
				//i == dphilmet2     ||
				i == dphillmet     ||	
				//i == nvtx          || 
				i == darkpt        ||
				i == ANN           ||
                                1 < 0               )
			{

				HowManyVar += 1; 
		 
				if ( doshape == 0 ) h_name[i] = b_name[i]; 
				if ( doshape == 1 ){ 

					if( k == nominal ) h_name[i] = processID2[process]                                ;
					if( k != nominal ) h_name[i] = processID2[process] + "_" + systematicIDdatacard[k];

				}

				//--- 1st approach: TTree::Project()
				/*if( i == ANN ){

					double cloison[] = { 0.00, 0.50, 0.95, 1.00 };

					myhisto[i] = new TH1F(h_name[i], h_name[i], 3, cloison);

				} 

				if( i == mt2ll ){

					double cloison[] = { 100.00, 140.00, 3000.00 };

					myhisto[i] = new TH1F(h_name[i], h_name[i], 2, cloison);

				}

				else{

					myhisto[i] = new TH1F(h_name[i], h_name[i], nbinraw[i], lowraw[i], upraw[i]); 

				}

				mytree -> Project( h_name[i], b_name[i], thecut );*/


				//--- 2nd approach: TTree::Draw()
				mytree -> Draw( Form("%s >> %s( %d, %f, %f )", b_name[i].Data(), h_name[i].Data(), nbinraw[i], lowraw[i], upraw[i] ), thecut );

				myhisto[i] = (TH1F*) gDirectory -> Get( h_name[i] );
	


				myhisto[i] -> Write(); 



				if( HowManyVar == 1 ){ 

					float yield;

					if( process == data                     ) yield = myhisto[i]-> Integral(-1, -1);
					if( process == fakes                    ) yield = myhisto[i]-> Integral(-1, -1);
		                        if( process != data && process != fakes ) yield = myhisto[i]-> Integral(-1, -1);

					//cout << "\t\t\t" << myhisto[i] -> GetEntries() << "\t\t" << yield << endl; 

					cout << Form("\t\t\t %8.0f \t\t %8.2f", myhisto[i]->GetEntries(), yield) << endl; 
 
					if( k == nominal && process != data && process != ttDM ) cuentita += yield;

				}

			}

		}

		storagefile -> Close();

		myfile -> Close();

		c1 -> Destructor();

	}  // k 

}
