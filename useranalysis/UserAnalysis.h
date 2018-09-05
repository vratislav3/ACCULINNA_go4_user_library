/**

	@class UserAnalysis

*/

#ifndef USERANALYSIS_H
#define USERANALYSIS_H

#include <TGo4Analysis.h> // mother class

// ROOT
#include <TString.h>

class UserParameter;

//TODO not used by now
class TGo4MbsEvent;
class UserEventUnpacking;
class UserEventRepacking;
class UserEventLearn;

class UserAnalysis : public TGo4Analysis
{
public:
	UserAnalysis(const char* name = "UserAnalysis");
	UserAnalysis(int argc, char** argv);
	virtual ~UserAnalysis();

	void Construct(TString p_outfilename, TString p_setupfilename);

	virtual Int_t UserPreLoop();
	virtual Int_t UserEventFunc();
	virtual Int_t UserPostLoop();

private:
	unsigned long int mEventCounter;

	/**
	 * Analysis parameters object, accessible by all steps
	 */
	UserParameter* mParams;

	//TODO not used by now
	TGo4MbsEvent* mMbsEvent;
	UserEventUnpacking* mUserEventUnpacking;
	UserEventRepacking* mUserEventRepacking;
	UserEventLearn* mUserEventLearn;

	ClassDef(UserAnalysis, 1);
};

#endif // USERANALYSIS_H
