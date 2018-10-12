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
	fBeamDetName = "Beam_detector";
	fMWPCx1Name = "MWPC1";
	fMWPCy1Name = "MWPC2";
	fMWPCx2Name = "MWPC3";
	fMWPCy2Name = "MWPC4";

//	stationMWPCX1name.Form("%s_%s", fBeamDetName.Data(), fMWPCx1Name.Data());
//	stationMWPCY1name.Form("%s_%s", fBeamDetName.Data(), fMWPCy1Name.Data());
//	stationMWPCX2name.Form("%s_%s", fBeamDetName.Data(), fMWPCx2Name.Data());
//	stationMWPCY2name.Form("%s_%s", fBeamDetName.Data(), fMWPCy2Name.Data());

}
