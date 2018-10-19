// $Id: TXXXParameter.h 1318 2015-01-08 13:28:41Z linev $
//-----------------------------------------------------------------------
//       The GSI Online Offline Object Oriented (Go4) Project
//         Experiment Data Processing at EE department, GSI
//-----------------------------------------------------------------------
// Copyright (C) 2000- GSI Helmholtzzentrum f�r Schwerionenforschung GmbH
//                     Planckstr. 1, 64291 Darmstadt, Germany
// Contact:            http://go4.gsi.de
//-----------------------------------------------------------------------
// This software can be used under the license agreements as stated
// in Go4License.txt file which is part of the distribution.
//-----------------------------------------------------------------------

#ifndef UserParameterBeamDetector_H
#define UserParameterBeamDetector_H

#include "TGo4Parameter.h"

//#include "TArrayI.h"

class UserParameterBeamDetector : public TGo4Parameter {
public:
	UserParameterBeamDetector(const char* name = "BeamDetPar");
	virtual ~UserParameterBeamDetector() {}

	TString fBeamDetName; 			//name of BeamDetector

	TString fMWPCx1Name;			//name of the X1 plane
	TString fMWPCy1Name;			//name of the Y1 plane
	TString fMWPCx2Name;			//name of the X2 plane
	TString fMWPCy2Name;			//name of the Y2 plane

	Int_t fTriggerCondition;		//trigger condition

//	Float_t fMWPCwireStep[4];
	Float_t fMWPCwireStepX1;		//step between two wires
	Float_t fMWPCwireStepY1;		//step between two wires
	Float_t fMWPCwireStepX2;		//step between two wires
	Float_t fMWPCwireStepY2;		//step between two wires

	//offsets taken from S. Krupko
	Float_t fMWPC1_X_offset;
	Float_t fMWPC1_Y_offset;
	Float_t fMWPC2_X_offset;
	Float_t fMWPC2_Y_offset;

	//MWPC
	Float_t fMWPCz1;	//z coordinate of the center of MWPC1
	Float_t fMWPCz2;	//z coordinate of the center of MWPC2


//private:
//	TString stationMWPCX1name;

//public:
//	TString stationMWPCY1name;
//	TString stationMWPCX2name;
//	TString stationMWPCY2name;

	ClassDef(UserParameterBeamDetector,1)

	const TString GetStationMWPCx1name() const {
//		return stationMWPCX1name;
		return fBeamDetName + "_" + fMWPCx1Name;
	}

	const TString GetStationMWPCx2name() const {
		return fBeamDetName + "_" + fMWPCx2Name;
	}

	const TString GetStationMWPCy1name() const {
		return fBeamDetName + "_" + fMWPCy1Name;
	}

	const TString GetStationMWPCy2name() const {
		return fBeamDetName + "_" + fMWPCy2Name;
	}

	const Float_t GetWireStep(Int_t plane);
	const Float_t GetMWPCoffset(Int_t plane);
};

#endif
