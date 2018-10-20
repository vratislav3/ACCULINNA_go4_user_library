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

	TH1* fMWPCwire[4];		//!
	TH1* fMultW[4];		//!
	TH2* fMWPCwireProfile[2];	//!

	TH1* fMWPCcluster[4];		//!
	TH1* fMultC[4];		//!
	TH2* fMWPCclusterProfile[2];	//!

	TH1* fMWPCmmW[4];		//!
	TH2* fMWPCProfileW[3];	//!

	TH1* fMWPCmmC[4];		//!
	TH2* fMWPCProfileC[3];	//!

	TH1* fMWPCwireEff;		//!
	TH1* fMWPCclusterEff;			//!

	/**
	 * Automatically generated histograms
	 */
//	std::map<unsigned int, TH1*> fAutoHistos_Beam; //!

	ClassDef(UserHistosBeamMonitoring2, 1);
};

#endif // USERHISTOSBEAMMONITORING2_H
