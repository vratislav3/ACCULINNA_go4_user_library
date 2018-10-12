/**

	@class UserProcBeamDetMonitoring

*/

#ifndef USERPROCBEAMDETMONITORING_H
#define USERPROCBEAMDETMONITORING_H

#include <TGo4EventProcessor.h> // mother class

class TGo4EventElement;

class UserHistosBeamDetMonitoring;
////class SetupConfiguration;
class DetMessage;

class UserProcBeamDetMonitoring : public TGo4EventProcessor
{
public: // methods

	UserProcBeamDetMonitoring(const char* name = "UserProcBeamDetMonitoring");
	virtual ~UserProcBeamDetMonitoring();

	virtual Bool_t BuildEvent(TGo4EventElement* p_dest);

	/** Method called when analysis is created */
	virtual void UserPreLoop();

	/** Method called when analysis is stopping */
	virtual void UserPostLoop();

private: // methods
	void ProcessMessage(DetMessage* p_message);

private: // data members
	/**
	 * Counter or processed events
	 */
	unsigned long int fEventCounter;

	/**
	 * Put all your output histograms inside this object.
	 * See UserHistosBeamDetMonitoring class.
	 */
	UserHistosBeamDetMonitoring* fHistoMan;

	/**
	 * 'this' object of the UserProcRawMonitoring class does not own this pointer
	 */
	////const SetupConfiguration* fSetupConfig;


	ClassDef(UserProcBeamDetMonitoring, 1);
};

#endif // USERPROCBEAMDETMONITORING_H
