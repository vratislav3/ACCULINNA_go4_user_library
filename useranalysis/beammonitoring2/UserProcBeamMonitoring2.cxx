
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

	FillMWPC();

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

void UserProcBeamMonitoring2::FillMWPC() {

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

	vector <Int_t> nx1;
	Int_t mx1 = 0;

	if(st_MWPCX1) {

		MWPCplane(st_MWPCX1,0);
	}

	if (st_MWPCY1) {
		MWPCplane(st_MWPCY1,1);
	}
	if (st_MWPCX2) {
		MWPCplane(st_MWPCX2,2);
	}
	if (st_MWPCY2) {
		MWPCplane(st_MWPCY2,3);
	}


	return;

}

void UserProcBeamMonitoring2::MWPCplane(DetEventStation* mwpcPlane, Int_t plane) {

	Int_t wireMult = 0;
	vector <Int_t> wire;

	TClonesArray* v_MWPC1 = mwpcPlane->GetDetMessages();
	wireMult = v_MWPC1->GetEntriesFast();

	fHistoMan->fMultW[plane]->Fill(wireMult);

	for(Int_t i = 0; i < wireMult; i++){
		DetMessage *mes_MWPC1 = (DetMessage*)v_MWPC1->At(i);
		wire.push_back(mes_MWPC1->GetStChannel());
	}

	if (wireMult==1) {
		fHistoMan->fMWPC[plane]->Fill(wire.at(0));

	}
}
