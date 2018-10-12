#include "UserProcBeamDetMonitoring.h"

// STD
#include <iostream>
using std::cerr;
using std::endl;

// ROOT
#include <TClonesArray.h>
#include <TH1D.h>
#include <TH2D.h>

// Project
#include "base/Support.h"
#include "data/DetEventFull.h" // input event
#include "data/DetEventCommon.h"
#include "data/DetEventStation.h"
#include "data/DetMessage.h"

#include "UserHistosBeamDetMonitoring.h"
#include "UserParameter.h"
#include "setupconfigcppwrapper/SetupConfiguration.h"

/**
  Uncomment this if you want to see all the debug information.
  This allows you to analyze the raw bytes and bits by your eyes.
  This option produces A LOT OF DATA - run your analysis with a
  small number of events (~10-100)
*/
//#define DEBUGBEAMDETMON

UserProcBeamDetMonitoring::UserProcBeamDetMonitoring(const char* name) :
	TGo4EventProcessor(name),
	fEventCounter(0)
{
	fHistoMan = new UserHistosBeamDetMonitoring();
}

UserProcBeamDetMonitoring::~UserProcBeamDetMonitoring()
{
	if (fHistoMan) delete fHistoMan;
}

Bool_t UserProcBeamDetMonitoring::BuildEvent(TGo4EventElement* p_dest)
{
	Bool_t v_isValid = kFALSE;

	DetEventFull* v_input = (DetEventFull*)GetInputEvent("stepRepackedProvider1");
	if (v_input == NULL)
	{
		cerr << "[WARN  ] " << "UserProcBeamDetMonitoring::BuildEvent(): no input event!" << endl;
		return v_isValid;
	}
	v_isValid = kTRUE;

	#ifdef DEBUGBEAMDETMON
	cerr << "[DEBUG ] " << "UserProcBeamDetMonitoring: Event " << fEventCounter
	     << " ======================================================================================================"
	     << endl;
	#endif

	// --------------------------

	Short_t v_NsubElems = v_input->getNElements();
	//cerr << v_NsubElems << " subelements in the input full event." << endl;

	// Loop over sub-elements. There is one sub-element which is the 'DetEventCommon'
	// and all other are 'DetEventDetector's
	for (Short_t i=0; i<v_NsubElems; i++) {
		TGo4EventElement* v_subElement = v_input->getEventElement(i);

		TString curName = v_subElement->GetName();
		Short_t curId = v_subElement->getId();
		//cerr << curId << ") " << curName;

		if (curName == "DetEventCommon") {
			//DetEventCommon* v_commSubEl = (DetEventCommon*)(v_subElement);
			//cerr << endl;

			// Here you can process information from the 'common' sub-element

		} else {
			TGo4CompositeEvent* v_detSubEl = (TGo4CompositeEvent*)(v_subElement);

			Short_t v_NsubSubElems = v_detSubEl->getNElements();
			//cerr << " - " << v_NsubSubElems << " subsubelements." << endl;

			// Loop over the stations of the current detector
			for (Short_t j=0; j<v_NsubSubElems; j++) {

				Short_t stId = curId*100 + j; //FIXME this is quite dangerous

				DetEventStation* v_stSubsubEl = (DetEventStation*)(v_detSubEl->getEventElement(stId));
				//cerr << "\t" << stId << ") " << v_stSubsubEl->GetName() << endl;

				TClonesArray* v_data = v_stSubsubEl->GetDetMessages();

				TIter v_detMiter(v_data);
				DetMessage* v_curDetM;

				// Loop over the messages of the current station 
				while ((v_curDetM = (DetMessage*)v_detMiter.Next())) {
					//v_curDetM->Print();

					//TODO implement here your actions which require processing
					// of several messages simultaneously

					//TODO Look inside
					this->ProcessMessage(v_curDetM);


				} // end of loop over messages
			} // end of loop over the stations
		} // end of if
	} // end of loop over the sub-elements (detectors)

	// --------------------------

	fEventCounter++;

	return v_isValid;
}

void UserProcBeamDetMonitoring::UserPreLoop()
{
	// Get the all-accessible parameter-set object
	////UserParameter* v_params = (UserParameter*)GetParameter("UserParameter");
	////fSetupConfig = v_params->GetSetupConfig();

	#ifdef DEBUGBEAMDETMON
	cerr << "[DEBUG ] " << "UserProcBeamDetMonitoring::UserPreLoop ====================================" << endl;
	#endif

	#ifdef DEBUGBEAMDETMON
	cerr << "[DEBUG ] " << "=======================================================================" << endl;
	#endif
}

void UserProcBeamDetMonitoring::UserPostLoop()
{
}

void UserProcBeamDetMonitoring::ProcessMessage(DetMessage* p_message)
{
	//TODO implement your processing of independent messages here
}

ClassImp(UserProcBeamDetMonitoring)
