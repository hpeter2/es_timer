#pragma once
#include "EuroScopePlugIn.h"
#include "Constant.h"
#include <sstream>


using namespace std;
using namespace EuroScopePlugIn;


class CESTimerRadar :
    public EuroScopePlugIn::CRadarScreen
{
protected:

	RECT m_Area = { 50, 100, 168, 137 };
	RECT b_Area = { 9, 7, 30, 30 };
	POINT m_Offset = { 118, 37 };
	bool highlight_1_two, highlight_1_three, highlight_2_two, highlight_2_three;
public:
	tm timer1, timer2;

public:
	CESTimerRadar();
	virtual ~CESTimerRadar();
	
	
	//---OnAsrContentLoaded--------------------------------------------

	virtual void OnAsrContentLoaded(bool Loaded);

	//---OnAsrContentToBeSaved------------------------------------------

	virtual void OnAsrContentToBeSaved();

	//---OnRefresh------------------------------------------------------

	virtual void OnRefresh(HDC hDC, int Phase);

	//---OnClickScreenObject-----------------------------------------

	virtual void OnClickScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, int Button);
	

	//---OnMoveScreenObject---------------------------------------------

	virtual void OnMoveScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, bool Released);

	//---OnButtonDownScreenObject---------------------------------------------

	virtual void OnButtonDownScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, int Button);

	//---OnButtonDownScreenObject---------------------------------------------
	
	virtual void OnButtonUpScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, int Button);

	
	//  This gets called before OnAsrContentToBeSaved()
	inline virtual void OnAsrContentToBeClosed(void)
	{
		delete this;
	};
};

