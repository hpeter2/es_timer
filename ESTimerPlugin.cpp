#include "stdafx.h"
#include "Resource.h"
#include "ESTimerPlugin.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


vector<CESTimerRadar*> RadarScreensOpened;


CESTimerPlugin::CESTimerPlugin(void) :CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE, MY_PLUGIN_NAME, MY_PLUGIN_VERSION, MY_PLUGIN_DEVELOPER, MY_PLUGIN_COPYRIGHT)
{
}


CESTimerPlugin::~CESTimerPlugin()
{
}


void CESTimerPlugin::OnTimer(int Counter)
{
	for each (auto var in RadarScreensOpened)
	{
		if (var->timer1.tm_min > 0 || var->timer1.tm_sec > 0) {
			if (var->timer1.tm_sec < 1) {
				var->timer1.tm_min--;
				var->timer1.tm_sec = 59;
			}
			else
				var->timer1.tm_sec--;

			if (var->timer1.tm_min == 0 && var->timer1.tm_sec == 0) {
				AFX_MANAGE_STATE(AfxGetStaticModuleState());
				PlaySound(MAKEINTRESOURCE(IDR_WAVE1), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
			}
		}
		if (var->timer2.tm_min > 0 || var->timer2.tm_sec > 0) {
			if (var->timer2.tm_sec < 1) {
				var->timer2.tm_min--;
				var->timer2.tm_sec = 59;
			}
			else
				var->timer2.tm_sec--;

			if (var->timer2.tm_min == 0 && var->timer2.tm_sec == 0) {
				AFX_MANAGE_STATE(AfxGetStaticModuleState());
				PlaySound(MAKEINTRESOURCE(IDR_WAVE2), AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
			}
		}
	}
}


CRadarScreen* CESTimerPlugin::OnRadarScreenCreated(const char* sDisplayName, bool NeedRadarContent, bool GeoReferenced, bool CanBeSaved, bool CanBeCreated)
{
	CESTimerRadar* rd = new CESTimerRadar();
	RadarScreensOpened.push_back(rd);
	return rd;
}


//---EuroScopePlugInExit-----------------------------------------------

void __declspec (dllexport) EuroScopePlugInExit(void)
{
	for each (auto var in RadarScreensOpened)
	{
		//var->EuroScopePlugInExitCustom();
	}
}

