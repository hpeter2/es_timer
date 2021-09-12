#pragma once
#include "EuroScopePlugIn.h"
#include "ESTimerRadar.h"


#define MY_PLUGIN_NAME      "Timer Plugin"
#define MY_PLUGIN_VERSION   "1.0"
#define MY_PLUGIN_DEVELOPER "Hendrik Peter"
#define MY_PLUGIN_COPYRIGHT "GPL v3"
#define MY_PLUGIN_VIEW_AVISO  "SMR radar display"

using namespace std;
using namespace EuroScopePlugIn;


class CESTimerPlugin : public EuroScopePlugIn::CPlugIn
{
public:
	CESTimerPlugin();
	virtual ~CESTimerPlugin();

	
	//---OnTimer------------------------------------------

	virtual void OnTimer(int Counter);

	//---OnRadarScreenCreated------------------------------------------

	virtual CRadarScreen* OnRadarScreenCreated(const char* sDisplayName, bool NeedRadarContent, bool GeoReferenced, bool CanBeSaved, bool CanBeCreated);
};
