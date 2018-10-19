
#include "UserProcBeamMonitoring2.h"

// STD
#include <fstream>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

// ROOT
#include <TClonesArray.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TRandom3.h>

// Project
#include "data/DetEventFull.h" // input event
#include "data/DetEventCommon.h"
#include "data/DetEventStation.h"
#include "data/DetMessage.h"

#include "UserHistosBeamMonitoring2.h"
#include "UserParameter.h"
#include "setupconfigcppwrapper/SetupConfiguration.h"
#include "UserParameterBeamDetector.h"

#include <stdlib.h>

using namespace std;
/**
  Uncomment this if you want to see all the debug information.
  This allows you to analyze the raw bytes and bits by your eyes.
  This option produces A LOT OF DATA - run your analysis with a
  small number of events (~10-100)
*/
//#define DEBUGBeamMON

UserProcBeamMonitoring2::UserProcBeamMonitoring2(const char* name) :
	TGo4EventProcessor(name),
	fEventCounter(0),
	fSetupConfig(0),
	v_input(0)
{
	fHistoMan = new UserHistosBeamMonitoring2();
	// cerr << " UserProcBeamMonitoring CALLED !!! ## &Y$@!UHNEFJNASJDf " << endl;
	fFileSummary = fopen("textoutput/summaryBeamMonitoring.txt", "w");
	if (fFileSummary == NULL) {
		//TODO error
		cerr << "[WARN  ] " << "Could not open output text summary file '" << "summaryBeamMonitoring.txt" << "'" << endl;
	}

	fParBD = (UserParameterBeamDetector*)MakeParameter("BeamDetPar", "UserParameterBeamDetector");
//	fParBD = new UserParameterBeamDetector();
//	AddParameter(fParBD);

//	fBeamDetName = "Beam_detector";
//	fMWPCx1Name = "MWPC1";
//	fMWPCy1Name = "MWPC2";
//	fMWPCx2Name = "MWPC3";
//	fMWPCy2Name = "MWPC4";
}

UserProcBeamMonitoring2::~UserProcBeamMonitoring2()
{
	if (fHistoMan) delete fHistoMan;
	if (fFileSummary != NULL) {
		fclose(fFileSummary);
	}
	if (v_input) {
		v_input = NULL;
	}
}

Bool_t UserProcBeamMonitoring2::BuildEvent(TGo4EventElement* p_dest)
{
	// cerr << "\t ### UserProcBeamMonitoring::BuildEvent was called ### " <<  endl;

	Bool_t v_isValid = kFALSE;

//	DetEventFull* v_input = (DetEventFull*)GetInputEvent("stepRepackedToBM2Provider");
	v_input = (DetEventFull*)GetInputEvent("stepRepackedProvider3");
//	v_input = (DetEventFull*)GetInputEvent("stepRepackedToBM2Provider");
	if (v_input == NULL)
	{
		cerr << "[WARN  ] " << "UserProcBeamMonitoring2::BuildEvent(): no input event!" << endl;
		return v_isValid;
	}
	v_isValid = kTRUE;

	#ifdef DEBUGBeamMON
	cerr << "[DEBUG ] " << "UserProcBeamMonitoring2: Event " << fEventCounter
	     << " ======================================================================================================"
	     << endl;
	#endif

	// --------------------------

//	Short_t v_NsubElems = v_input->getNElements();
	//cerr << v_NsubElems << " subelements in the input full event." << endl;
	Int_t trigger;
	// Loop over sub-elements. There is one sub-element which is the 'DetEventCommon'
	// and all other are 'DetEventDetector's

	TGo4EventElement* v_comElement = v_input->getEventElement("DetEventCommon",1);
	if(!v_comElement) {
		cout << "Detector DetEventCommon was not found " << endl;
		return kFALSE;
	}
	DetEventCommon* v_commSubEl = (DetEventCommon*)(v_comElement);
	trigger = v_commSubEl->trigger;
	if(trigger>5) {
		cout << " Event wont be processed " << endl;
		return kFALSE;
	}
//	fHistoMan->fTrigger->Fill(trigger);


//////////////////////////////////////
//	filling my own histograms
//////////////////////////////////////

	FillMWPC(trigger);

//////////////////////////////////////
//	filling my own histograms
//////////////////////////////////////

	fEventCounter++;

	v_input = NULL;

	return v_isValid;
}

void UserProcBeamMonitoring2::UserPreLoop()
{
	// Get the all-accessible parameter-set object
	UserParameter* v_params = (UserParameter*)GetParameter("UserParameter");
	fSetupConfig = v_params->GetSetupConfig();

	#ifdef DEBUGBeamMON
	cerr << "[DEBUG ] " << "UserProcBeamMonitoring::UserPreLoop ====================================" << endl;
	#endif

	// fHistoMan->GenerateAutoHistos();

	#ifdef DEBUGBeamMON
	cerr << "[DEBUG ] " << "=======================================================================" << endl;
	#endif
}

void UserProcBeamMonitoring2::UserPostLoop()
{
}

void UserProcBeamMonitoring2::ProcessMessage(DetMessage* p_message, TString stName)
{
	//TODO implement your processing of independent messages here
	// cout << stName << " :UserProcBeamMonitoring2::ProcessMessage" << endl;
}

ClassImp(UserProcBeamMonitoring2)

void UserProcBeamMonitoring2::FillMWPC(Int_t curTrigger) {

//	DetEventStation* st_MWPCX1 = (DetEventStation*)(v_input->getEventElement(fParBD->stationMWPCX1name.Data(),1));
	DetEventStation* st_MWPCX1 = (DetEventStation*)(v_input->getEventElement(fParBD->GetStationMWPCx1name().Data(),1));
	if(!st_MWPCX1) {
		cout << " station " << fParBD->GetStationMWPCx1name() << " was not found in event " << fEventCounter << endl;
	}

	DetEventStation* st_MWPCY1 = (DetEventStation*)(v_input->getEventElement(fParBD->GetStationMWPCy1name().Data(),1));
	if(!st_MWPCY1) {
		cout << " station " << fParBD->GetStationMWPCy1name() << " was not found in event " << fEventCounter << endl;
	}

	DetEventStation* st_MWPCX2 = (DetEventStation*)(v_input->getEventElement(fParBD->GetStationMWPCx2name().Data(),1));
	if(!st_MWPCX2) {
		cout << " station " << fParBD->GetStationMWPCx2name() << " was not found in event " << fEventCounter << endl;
	}

	DetEventStation* st_MWPCY2 = (DetEventStation*)(v_input->getEventElement(fParBD->GetStationMWPCy2name().Data(),1));
	if(!st_MWPCY2) {
		cout << " station " << fParBD->GetStationMWPCy2name() << " was not found in event " << fEventCounter << endl;
	}

//	vector <Int_t> nx1;
//	Int_t mx1 = 0;

//	if (st_MWPCX1) {
//		MWPCplane(st_MWPCX1, 0, curTrigger);
//	}
//
//	if (st_MWPCY1) {
//		MWPCplane(st_MWPCY1, 1, curTrigger);
//	}
//	if (st_MWPCX2) {
//		MWPCplane(st_MWPCX2, 2, curTrigger);
//	}
//	if (st_MWPCY2) {
//		MWPCplane(st_MWPCY2, 3, curTrigger);
//	}
//
//	if  (st_MWPCX1 && st_MWPCY1) {
//		MWPCplane2D(st_MWPCX1, st_MWPCY1, 0, curTrigger);
//	}
//
//	if  (st_MWPCX2 && st_MWPCY2) {
//		MWPCplane2D(st_MWPCX2, st_MWPCY2, 1, curTrigger);
//	}

//	if (st_MWPCX1 && st_MWPCY1 && st_MWPCX2 && st_MWPCY2) {
	MWPCprojection(st_MWPCX1, st_MWPCY1, st_MWPCX2, st_MWPCY2, curTrigger);
//	}

	return;

}

void UserProcBeamMonitoring2::MWPCplane(DetEventStation* mwpcPlane, Int_t plane, Int_t curTrigger) {

	Int_t wireMult = 0;
	vector <Int_t> wire;

	TClonesArray* v_MWPC1 = mwpcPlane->GetDetMessages();
	wireMult = v_MWPC1->GetEntriesFast();

	if (curTrigger==fParBD->fTriggerCondition) {
		fHistoMan->fMultW[plane]->Fill(wireMult);
	}

	for(Int_t i = 0; i < wireMult; i++){
		DetMessage *mes_MWPC1 = (DetMessage*)v_MWPC1->At(i);
		wire.push_back(mes_MWPC1->GetStChannel());
	}

	if (wireMult==1 && curTrigger==fParBD->fTriggerCondition) {
//		fHistoMan->fMWPC[plane]->Fill(wire.at(0));
//		((DetMessage*)v_MWPC1->At(i))->GetStChannel();
		((DetMessage*)v_MWPC1->At(0))->GetStChannel();
		fHistoMan->fMWPCwire[plane]->Fill( ((DetMessage*)v_MWPC1->At(0))->GetStChannel() );
//		if (plane == 0) {
//			fHistoMan->fMWPCmm[plane]->Fill( (wire.at(0) + 0.5 - 16)*fParBD->fMWPCwireStepX1 + fParBD->fMWPC1_X_offset);
//			Float_t coordinate
//			= (wire.at(0) + gRandom->Uniform(-0.5, 0.5) + 0.5 - 16)*fParBD->GetWireStep(plane)
//			+ fParBD->GetMWPCoffset(plane);
//			fHistoMan->fMWPCmm[plane]->Fill(coordinate);
//		}




	}
}

void UserProcBeamMonitoring2::MWPCplane2D(DetEventStation* mwpcPlaneX,
		DetEventStation* mwpcPlaneY, Int_t plane, Int_t curTrigger)
{

	Int_t wireMultX = 0;
	Int_t wireMultY = 0;
	vector <Int_t> wireX;
	vector <Int_t> wireY;

	TClonesArray* v_MWPCX = mwpcPlaneX->GetDetMessages();
	wireMultX = v_MWPCX->GetEntriesFast();

	TClonesArray* v_MWPCY = mwpcPlaneY->GetDetMessages();
	wireMultY = v_MWPCY->GetEntriesFast();

//	if (curTrigger==fParBD->fTriggerCondition) {
//		fHistoMan->fMultW[planeX]->Fill(wireMultX);
//	}

	for(Int_t i = 0; i < wireMultX; i++){
		DetMessage *mes_MWPCX = (DetMessage*)v_MWPCX->At(i);
		wireX.push_back(mes_MWPCX->GetStChannel());
	}

	for(Int_t i = 0; i < wireMultY; i++){
		DetMessage *mes_MWPCY = (DetMessage*)v_MWPCY->At(i);
		wireY.push_back(mes_MWPCY->GetStChannel());
	}

	if (wireMultX==1 && wireMultY==1 && curTrigger==fParBD->fTriggerCondition) {
//		fHistoMan->fMWPC[plane]->Fill(wire.at(0));
		fHistoMan->fMWPCwireProfile[plane]->Fill(wireX.at(0), wireY.at(0));

	}

}

void UserProcBeamMonitoring2::MWPCprojection(DetEventStation* mwpcPlaneX1,
		DetEventStation* mwpcPlaneY1, DetEventStation* mwpcPlaneX2,
		DetEventStation* mwpcPlaneY2, Int_t curTrigger) {


	Float_t x1p, y1p, x2p, y2p, xt, yt;

//	Int_t wireMultX1 = 0;
//	Int_t wireMultY1 = 0;
//	Int_t wireMultX2 = 0;
//	Int_t wireMultY2 = 0;

	Int_t wireMult[4] = { 0 }; //x1, y1, x2, y2
	Int_t wire[4]; //x1, y1, x2, y2

	Int_t clusterMult[4] = { 0 }; //x1, y1, x2, y2
//	Int_t cluster[4]; //x1, y1, x2, y2

//	vector <Int_t> wireX1;
//	vector <Int_t> wireY1;
//	vector <Int_t> wireX2;
//	vector <Int_t> wireY2;

	TClonesArray* v_MWPC[4] = { NULL };	//x1, y1, x2, y2
//	for (Int_t i = 0; i < 4; i++) {
//		v_MWPC[i] = NULL;
//	}

//	return;

	if (mwpcPlaneX1) {
		v_MWPC[0] = mwpcPlaneX1->GetDetMessages();
//		wireMult[0] = v_MWPC[0]->GetEntriesFast();
		wireMult[0] = GetWireMult(v_MWPC[0]);
		clusterMult[0] = GetClusterMult(v_MWPC[0]);
	}

	if (mwpcPlaneY1) {
		v_MWPC[1] = mwpcPlaneY1->GetDetMessages();
//		wireMult[1] = v_MWPC[1]->GetEntriesFast();
		wireMult[1] = GetWireMult(v_MWPC[1]);
		clusterMult[1] = GetClusterMult(v_MWPC[1]);
	}

	if (mwpcPlaneX2) {
		v_MWPC[2] = mwpcPlaneX2->GetDetMessages();
//		wireMult[2] = v_MWPC[2]->GetEntriesFast();
		wireMult[2] = GetWireMult(v_MWPC[2]);
		clusterMult[2] = GetClusterMult(v_MWPC[2]);
	}

	if (mwpcPlaneY2) {
		v_MWPC[3] = mwpcPlaneY2->GetDetMessages();
//		wireMult[3] = v_MWPC[3]->GetEntriesFast();
		wireMult[3] = GetWireMult(v_MWPC[3]);
		clusterMult[3] = GetClusterMult(v_MWPC[3]);
	}

	for (Int_t i = 0; i < 4; i++) {
		if (curTrigger==fParBD->fTriggerCondition) {
			fHistoMan->fMultW[i]->Fill(wireMult[i]);
			fHistoMan->fMultC[i]->Fill(clusterMult[i]);
		}

		//filling if wire multiplicity equal to 1
		if (v_MWPC[i] && wireMult[i]==1 && curTrigger==fParBD->fTriggerCondition) {
			//add comment here
			wire[i] = ((DetMessage*)v_MWPC[i]->At(0))->GetStChannel();
			fHistoMan->fMWPCwire[i]->Fill(wire[i]);


		//filling if cluster multiplicity equal to 1
		// ....
		// ....
		// ....

		}//if one plane is present

	}

//	return;

	for (Int_t i = 0; i < 2; i++) {
		if (v_MWPC[2*i] && v_MWPC[2*i+1] &&
				wireMult[2*i]==1 && wireMult[2*i+1]==1 &&
				curTrigger==fParBD->fTriggerCondition) {

			fHistoMan->fMWPCwireProfile[i]->Fill(wire[2*i], wire[2*i+1]);

		}
	}

	if (v_MWPC[0] && v_MWPC[1] && v_MWPC[2] && v_MWPC[3] && curTrigger==fParBD->fTriggerCondition) {

		x1p = (wire[0] + gRandom->Uniform(-0.5, 0.5) + 0.5 - 16)*fParBD->fMWPCwireStepX1 + fParBD->fMWPC1_X_offset;
		y1p = (wire[1] + gRandom->Uniform(-0.5, 0.5) + 0.5 - 16)*fParBD->fMWPCwireStepY1 + fParBD->fMWPC1_Y_offset;

		x2p = (wire[2] + gRandom->Uniform(-0.5, 0.5) + 0.5 - 16)*fParBD->fMWPCwireStepX2 + fParBD->fMWPC2_X_offset;
		y2p = (wire[3] + gRandom->Uniform(-0.5, 0.5) + 0.5 - 16)*fParBD->fMWPCwireStepY2 + fParBD->fMWPC2_Y_offset;

		xt = x1p - (x2p -x1p)*fParBD->fMWPCz1/(fParBD->fMWPCz2-fParBD->fMWPCz1);
		yt = y1p - (y2p -y1p)*fParBD->fMWPCz1/(fParBD->fMWPCz2-fParBD->fMWPCz1);


		fHistoMan->fMWPCmm[0]->Fill(x1p);
		fHistoMan->fMWPCmm[1]->Fill(y1p);
		fHistoMan->fMWPCmm[2]->Fill(x2p);
		fHistoMan->fMWPCmm[3]->Fill(y2p);

		fHistoMan->fMWPCProfile[0]->Fill(x1p, y1p);
		fHistoMan->fMWPCProfile[1]->Fill(x2p, y2p);
		fHistoMan->fMWPCProfile[2]->Fill(xt, yt);

	}

//	for(Int_t i = 0; i < wireMultX1; i++){
////		DetMessage *mes_MWPCX1 = (DetMessage*)v_MWPCX1->At(i);
////		wireX1.push_back(mes_MWPCX1->GetStChannel());
//		((DetMessage*)v_MWPCX1->At(i))->GetStChannel();
//	}



}

Int_t UserProcBeamMonitoring2::GetWireMult(TClonesArray *data) {

	if (!data) return 0;

	return data->GetEntriesFast();

}

Int_t UserProcBeamMonitoring2::GetClusterMult(TClonesArray *data)
{

	if (!data) return 0;

	Int_t entries = data->GetEntriesFast();

	if (entries<2) return entries;

	Int_t wire1, wire2;
	Int_t noclusters = 1;


//	cout << "///\t" << fEventCounter << ":\t/////////////" << endl;

	for (Int_t i = 1; i < entries; i++) {
		//check if entries are in specific order
		wire1 = ((DetMessage*)data->At(i))->GetStChannel();
		wire2 = ((DetMessage*)data->At(i-1))->GetStChannel();

//		cout << wire2 << "\t" << wire1 << endl;
		//todo number 32 is related to number of wires
		// and should be taken from Parameters
		if ( abs(wire1 - wire2) > 1 && abs(wire1 - wire2) < 32) noclusters++;
	}

//	cout << endl
//			<< "clusters:\t" << noclusters << endl << endl;

	return noclusters;
} //--------------------------------------------------------------------
