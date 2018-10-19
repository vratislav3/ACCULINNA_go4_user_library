/**

	@class UserHistosBeamMonitoring

*/

#ifndef USERHISTOSBEAMMONITORING2_H
#define USERHISTOSBEAMMONITORING2_H

#include <TObject.h> // mother class

// STD
#include <map>
#include <fstream>
	
class TH1;
class TH2;

class UserHistosBeamMonitoring2 : public TObject
{
public:
	UserHistosBeamMonitoring2();
	~UserHistosBeamMonitoring2();

//	void GenerateAutoHistos(void);

//	TH1* fTrigger;		//!
//	TH1* fMWPCX1;		//!
//	TH1* fMWPCY1;		//!
//
//	TH1* fX1MultW;		//!
//	TH1* fY1MultW;		//!

	TH1* fMWPCwire[4];		//!
	TH1* fMWPCmm[4];		//!
	TH1* fMultW[4];		//!

	TH1* fMultC[4];		//!

	TH2* fMWPCwireProfile[2];	//!
	TH2* fMWPCProfile[3];	//!

	/**
	 * Automatically generated histograms
	 */
//	std::map<unsigned int, TH1*> fAutoHistos_Beam; //!

	ClassDef(UserHistosBeamMonitoring2, 1);
};

#endif // USERHISTOSBEAMMONITORING2_H
