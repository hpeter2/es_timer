// ESTimerApp.h : main header file for the es_timer DLL
//

#pragma once
#include "EuroScopePlugIn.h"
#include "ESTimerPlugin.h"

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols



class CESTimerApp :  public CWinApp
{
public:
	CESTimerApp();

	// Overrides
public:
	virtual BOOL InitInstance();
	CESTimerPlugin* gpMyPlugin = NULL;
	DECLARE_MESSAGE_MAP()
};

