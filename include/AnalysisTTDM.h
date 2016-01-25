#ifndef AnalysisTTDM_h
#define AnalysisTTDM_h

#include "AnalysisCMS.h"


class AnalysisTTDM : public AnalysisCMS
{
 public :

  AnalysisTTDM(TTree* tree = 0);

  void FillAnalysisHistograms(int     ichannel,
			      int     icut,
			      int     ijet);

  void FillLevelHistograms   (int     icut,
			      bool    pass);

  void Loop                  (TString analysis,
			      TString sample,
			      float   luminosity);


  // MET filters histograms
  //----------------------------------------------------------------------------
  TH1D*                  met_Flag[nfilter];
};

#endif