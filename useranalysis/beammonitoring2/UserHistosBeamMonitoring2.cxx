#include "UserHistosBeamMonitoring2.h"

// ROOT
#include <TH1D.h>
#include <TH2D.h>

// Go4
#include <TGo4Analysis.h>

// Project
#include "setupconfigcppwrapper/SetupConfiguration.h"

UserHistosBeamMonitoring2::UserHistosBeamMonitoring2()
{
	TGo4Analysis* a = TGo4Analysis::Instance();
//	fTrigger = a->MakeTH1('I', "trigger", "Values of trigger_test",   5, 0., 5.);
//	fMWPCX1 = a->MakeTH1('I', "BM2/MWPCX1", "My new histogram", 32, 0, 32);
//	fMWPCY1 = a->MakeTH1('I', "BM2/MWPCY1", "My new histogram", 32, 0, 32);
//
//	fX1MultW = a->MakeTH1('I', "BM2/X1MultW", "Wire multiplicity in the X1 plane", 32, 0, 32);
//	fY1MultW = a->MakeTH1('I', "BM2/Y1MultW", "Wire multiplicity in the Y1 plane", 32, 0, 32);

	fMWPCwire[0] = a->MakeTH1('I', "BM2/X1w", "My new histogram", 32, 0, 32);
	fMWPCwire[1] = a->MakeTH1('I', "BM2/Y1w", "My new histogram", 32, 0, 32);
	fMWPCwire[2] = a->MakeTH1('I', "BM2/X2w", "My new histogram", 32, 0, 32);
	fMWPCwire[3] = a->MakeTH1('I', "BM2/Y2w", "My new histogram", 32, 0, 32);

	fMWPCmm[0] = a->MakeTH1('I', "BM2/X1mm", "X1 position in mm", 46, -23., 23.);
	fMWPCmm[1] = a->MakeTH1('I', "BM2/Y1mm", "Y1 position in mm", 46, -23., 23.);
	fMWPCmm[2] = a->MakeTH1('I', "BM2/X2mm", "X2 position in mm", 46, -23., 23.);
	fMWPCmm[3] = a->MakeTH1('I', "BM2/Y2mm", "Y2 position in mm", 46, -23., 23.);

	fMultW[0] = a->MakeTH1('I', "BM2/multX1w", "multiplicity x1", 32, 0, 32);
	fMultW[1] = a->MakeTH1('I', "BM2/multY1w", "multiplicity y1", 32, 0, 32);
	fMultW[2] = a->MakeTH1('I', "BM2/multX2w", "multiplicity x2", 32, 0, 32);
	fMultW[3] = a->MakeTH1('I', "BM2/multY2w", "multiplicity y2", 32, 0, 32);

	fMultC[0] = a->MakeTH1('I', "BM2/multX1c", "multiplicity x1", 32, 0, 32);
	fMultC[1] = a->MakeTH1('I', "BM2/multY1c", "multiplicity y1", 32, 0, 32);
	fMultC[2] = a->MakeTH1('I', "BM2/multX2c", "multiplicity x2", 32, 0, 32);
	fMultC[3] = a->MakeTH1('I', "BM2/multY2c", "multiplicity y2", 32, 0, 32);

	fMWPCwireProfile[0] = a->MakeTH2('I', "BM2/XY1wire", "Y1 vs X1: 1 fired wire", 32, 0, 32, 32, 0, 32,"X1","Y1");
	fMWPCwireProfile[1] = a->MakeTH2('I', "BM2/XY2wire", "Y2 vs X2: 1 fired wire", 32, 0, 32, 32, 0, 32,"X2","Y2");

	fMWPCProfile[0] = a->MakeTH2('I', "BM2/XY1", "Y1 vs X1: mm", 46, -23., 23., 46, -23., 23.,"X1","Y1");
	fMWPCProfile[1] = a->MakeTH2('I', "BM2/XY2", "Y2 vs X2: mm", 46, -23., 23., 46, -23., 23.,"X2","Y2");
	fMWPCProfile[2] = a->MakeTH2('I', "BM2/XYt", "Yt vs Xt: mm", 46, -23., 23., 46, -23., 23.,"Xt","Yt");

}

UserHistosBeamMonitoring2::~UserHistosBeamMonitoring2()
{
	/**
	 * Not 100% sure, but it looks as if you do not need to delete your histograms yourself.
	 * TGo4AnalysisObjectManager, as part of the singleton TGo4Analysis, will take care.
	 */
}

/*void UserHistosBeamMonitoring2::GenerateAutoHistos(void)
{
	TGo4Analysis* a = TGo4Analysis::Instance();

	const SetupConfiguration& v_SetupConfig = SetupConfiguration::GetInstance();

	std::map<unsigned int, stc_mapping*> v_mappings = v_SetupConfig.GetMappings();
	std::map<unsigned int, stc_mapping*>::const_iterator v_mapIter = v_mappings.begin();

	for ( ; v_mapIter != v_mappings.end(); ++v_mapIter) {
		unsigned int v_uid = v_mapIter->first;
		//cerr << v_uid << endl;

		unsigned short v_procid = v_SetupConfig.GetProcIdFromUID(v_uid);
		unsigned short v_addr = v_SetupConfig.GetAddrFromUID(v_uid);
		unsigned short v_ch = v_SetupConfig.GetElChFromUID(v_uid);

		TString v_station;
		TString v_detector;
		TString v_elblock;
		unsigned short v_detid;
		unsigned short v_statid;
		unsigned short v_det_ch = v_SetupConfig.GetOutput(v_procid, v_addr, v_ch, &v_station,
		                                                  &v_detector, &v_elblock, &v_detid, &v_statid);

		//cerr << v_detector << "(" << v_detid << "): " << v_station << "(" << v_statid << "): " << v_det_ch << endl;

		//TODO check duplicates
		TString newHistoName;
		// newHistoName.Form("BeamMon/AutoHistos/%d_%s_%s_%d_Beam", v_statid*100+v_det_ch, v_detector.Data(), v_station.Data(), v_det_ch);


		Int_t nBins,nLow,nUp;
		TString stationNameFull;
		stationNameFull = v_detector + "_" + v_station;
		if(v_station == "MWPC1" || v_station == "MWPC2" || v_station == "MWPC3" || v_station == "MWPC4") {
			// cout << stationNameFull << endl;
			nBins = 32;
			nLow = 0;
			nUp = 31;
			newHistoName.Form("newhistos/%s/WIRES/%s_new", v_detector.Data(), v_station.Data());
		}
		else {
			nBins = 500;
			nLow = 0;
			nUp = 10000;
			newHistoName.Form("newhistos/%s/%s/%s_%d_new", v_detector.Data(), v_station.Data(), v_station.Data(), v_det_ch);
		}
		TH1* v_histo = a->MakeTH1('D', newHistoName, newHistoName, nBins, nLow, nUp); //TODO ranges
		fAutoHistos_Beam.insert(std::pair<unsigned int, TH1*>(v_statid*100+v_det_ch, v_histo));
	}
}*/

ClassImp(UserHistosBeamMonitoring2)
