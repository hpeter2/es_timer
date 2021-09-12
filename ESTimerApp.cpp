// ESTimerApp.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "ESTimerApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CvSMRApp

BEGIN_MESSAGE_MAP(CESTimerApp, CWinApp)
END_MESSAGE_MAP()


// CvSMRApp construction

CESTimerApp::CESTimerApp()
{

}


// The one and only CvSMRApp object

CESTimerApp theApp;


// CvSMRApp initialization

BOOL CESTimerApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

//---EuroScopePlugInInit-----------------------------------------------

void __declspec (dllexport) EuroScopePlugInInit(EuroScopePlugIn::CPlugIn** ppPlugInInstance)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// create the instance
		* ppPlugInInstance = theApp.gpMyPlugin = new CESTimerPlugin();
}

