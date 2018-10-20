#include "UserHistosBeamMonitoring2.h"

// ROOT
#include <TH1D.h>
#include <TH2D.h>

// Go4
#include <TGo4Analysis.h>

// Project
#include "setupconfigcppwrapper/SetupConfiguration.h"

UserHistosBeamMonitoring2::UserHistosBeamMonitoring2()
{
	TGo4Analysis* a = TGo4Analysis::Instance();

	fMWPCwire[0] = a->MakeTH1('I', "BM2/wires/X1w", "My new histogram", 32, 0, 32);
	fMWPCwire[1] = a->MakeTH1('I', "BM2/wires/Y1w", "My new histogram", 32, 0, 32);
	fMWPCwire[2] = a->MakeTH1('I', "BM2/wires/X2w", "My new histogram", 32, 0, 32);
	fMWPCwire[3] = a->MakeTH1('I', "BM2/wires/Y2w", "My new histogram", 32, 0, 32);

	fMWPCmmW[0] = a->MakeTH1('I', "BM2/X1mmW", "X1 position in mm", 46, -23., 23.);
	fMWPCmmW[1] = a->MakeTH1('I', "BM2/Y1mmW", "Y1 position in mm", 46, -23., 23.);
	fMWPCmmW[2] = a->MakeTH1('I', "BM2/X2mmW", "X2 position in mm", 46, -23., 23.);
	fMWPCmmW[3] = a->MakeTH1('I', "BM2/Y2mmW", "Y2 position in mm", 46, -23., 23.);

	fMWPCmmC[0] = a->MakeTH1('I', "BM2/X1mmC", "X1 position in mm", 46, -23., 23.);
	fMWPCmmC[1] = a->MakeTH1('I', "BM2/Y1mmC", "Y1 position in mm", 46, -23., 23.);
	fMWPCmmC[2] = a->MakeTH1('I', "BM2/X2mmC", "X2 position in mm", 46, -23., 23.);
	fMWPCmmC[3] = a->MakeTH1('I', "BM2/Y2mmC", "Y2 position in mm", 46, -23., 23.);

	fMultW[0] = a->MakeTH1('I', "BM2/Mult/multX1w", "multiplicity x1", 32, 0, 32);
	fMultW[1] = a->MakeTH1('I', "BM2/Mult/multY1w", "multiplicity y1", 32, 0, 32);
	fMultW[2] = a->MakeTH1('I', "BM2/Mult/multX2w", "multiplicity x2", 32, 0, 32);
	fMultW[3] = a->MakeTH1('I', "BM2/Mult/multY2w", "multiplicity y2", 32, 0, 32);

	fMWPCcluster[0] = a->MakeTH1('I', "BM2/wires/X1c", "My new histogram", 32, 0, 32);
	fMWPCcluster[1] = a->MakeTH1('I', "BM2/wires/Y1c", "My new histogram", 32, 0, 32);
	fMWPCcluster[2] = a->MakeTH1('I', "BM2/wires/X2c", "My new histogram", 32, 0, 32);
	fMWPCcluster[3] = a->MakeTH1('I', "BM2/wires/Y2c", "My new histogram", 32, 0, 32);

	fMultC[0] = a->MakeTH1('I', "BM2/Mult/multX1c", "multiplicity x1", 32, 0, 32);
	fMultC[1] = a->MakeTH1('I', "BM2/Mult/multY1c", "multiplicity y1", 32, 0, 32);
	fMultC[2] = a->MakeTH1('I', "BM2/Mult/multX2c", "multiplicity x2", 32, 0, 32);
	fMultC[3] = a->MakeTH1('I', "BM2/Mult/multY2c", "multiplicity y2", 32, 0, 32);

	fMWPCwireProfile[0] = a->MakeTH2('I', "BM2/wires/XY1wire", "Y1 vs X1: 1 fired wire", 32, 0, 32, 32, 0, 32,"X1","Y1");
	fMWPCwireProfile[1] = a->MakeTH2('I', "BM2/wires/XY2wire", "Y2 vs X2: 1 fired wire", 32, 0, 32, 32, 0, 32,"X2","Y2");

	fMWPCclusterProfile[0] = a->MakeTH2('I', "BM2/wires/XY1cluster", "Y1 vs X1: 1 fired wire", 32, 0, 32, 32, 0, 32,"X1","Y1");
	fMWPCclusterProfile[1] = a->MakeTH2('I', "BM2/wires/XY2cluster", "Y2 vs X2: 1 fired wire", 32, 0, 32, 32, 0, 32,"X2","Y2");

	fMWPCProfileW[0] = a->MakeTH2('I', "BM2/XY1w", "Y1 vs X1: mm", 46, -23., 23., 46, -23., 23.,"X1","Y1");
	fMWPCProfileW[1] = a->MakeTH2('I', "BM2/XY2w", "Y2 vs X2: mm", 46, -23., 23., 46, -23., 23.,"X2","Y2");
	fMWPCProfileW[2] = a->MakeTH2('I', "BM2/XYtw", "Yt vs Xt: mm", 46, -23., 23., 46, -23., 23.,"Xt","Yt");

	fMWPCProfileC[0] = a->MakeTH2('I', "BM2/XY1c", "Y1 vs X1: mm", 46, -23., 23., 46, -23., 23.,"X1","Y1");
	fMWPCProfileC[1] = a->MakeTH2('I', "BM2/XY2c", "Y2 vs X2: mm", 46, -23., 23., 46, -23., 23.,"X2","Y2");
	fMWPCProfileC[2] = a->MakeTH2('I', "BM2/XYtc", "Yt vs Xt: mm", 46, -23., 23., 46, -23., 23.,"Xt","Yt");

	fMWPCwireEff = a->MakeTH1('D', "BM2/wireEff", "Multiplicity 1 in wires", 5, 0, 5);
	fMWPCclusterEff = a->MakeTH1('D', "BM2/clusterEff", "Multiplicity 1 in clusters", 5, 0, 5);

}

UserHistosBeamMonitoring2::~UserHistosBeamMonitoring2()
{
	/**
	 * Not 100% sure, but it looks as if you do not need to delete your histograms yourself.
	 * TGo4AnalysisObjectManager, as part of the singleton TGo4Analysis, will take care.
	 */
}

ClassImp(UserHistosBeamMonitoring2)
