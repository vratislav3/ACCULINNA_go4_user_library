// $Id: TXXXParameter.cxx 1318 2015-01-08 13:28:41Z linev $
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

#include "UserParameterBeamDetector.h"

UserParameterBeamDetector::UserParameterBeamDetector(const char* name) :
	TGo4Parameter(name)
//   fArr()
{
	fBeamDetName = "Beam_detector";		//beam detector name
	fMWPCx1Name = "MWPC1";				//x1 plane name
	fMWPCy1Name = "MWPC2";				//y1 plane name
	fMWPCx2Name = "MWPC3";				//x2 plane name
	fMWPCy2Name = "MWPC4";				//y2 plane name

	fTriggerCondition = 1;

	fMWPCwireStepX1 = -1.25;
	fMWPCwireStepY1 = 1.25;		//step between two wires
	fMWPCwireStepX2 = -1.25;		//step between two wires
	fMWPCwireStepY2 = 1.25;		//step between two wires

	fMWPC1_X_offset = -1.19;
	fMWPC1_Y_offset = -2.12;
	fMWPC2_X_offset = 0.2;
	fMWPC2_Y_offset = -1.02;

	fMWPCz1 = -815.;	//z coordinate of the center of MWPC1
	fMWPCz2 = -270.;	//z coordinate of the center of MWPC2

//	stationMWPCX1name.Form("%s_%s", fBeamDetName.Data(), fMWPCx1Name.Data());
//	stationMWPCY1name.Form("%s_%s", fBeamDetName.Data(), fMWPCy1Name.Data());
//	stationMWPCX2name.Form("%s_%s", fBeamDetName.Data(), fMWPCx2Name.Data());
//	stationMWPCY2name.Form("%s_%s", fBeamDetName.Data(), fMWPCy2Name.Data());

}

const Float_t UserParameterBeamDetector::GetWireStep(Int_t plane) {
	if (plane==0) return fMWPCwireStepX1;
	else if (plane==1) return fMWPCwireStepY1;
	else if (plane==2) return fMWPCwireStepX2;
	else if (plane==3) return fMWPCwireStepY2;
	else return 0;
}

const Float_t UserParameterBeamDetector::GetMWPCoffset(Int_t plane) {
	if (plane==0) return fMWPC1_X_offset;
	else if (plane==1) return fMWPC1_Y_offset;
	else if (plane==2) return fMWPC2_X_offset;
	else if (plane==3) return fMWPC2_Y_offset;
	else return 0;
}
