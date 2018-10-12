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

	TString fBeamDetName; // some comment; is it necessary?

	TString fMWPCx1Name;
	TString fMWPCy1Name;
	TString fMWPCx2Name;
	TString fMWPCy2Name;

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
		return fBeamDetName + "_" + fMWPCx1Name;
	}

	const TString GetStationMWPCy1name() const {
		return fBeamDetName + "_" + fMWPCy1Name;
	}

	const TString GetStationMWPCy2name() const {
		return fBeamDetName + "_" + fMWPCy2Name;
	}
};

#endif
