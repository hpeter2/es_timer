#include "stdafx.h"
#include "Resource.h"
#include "ESTimerRadar.h"



CESTimerRadar::CESTimerRadar()
{	
	timer1.tm_min = timer1.tm_sec = 0;
	timer2.tm_min = timer2.tm_sec = 0;
	highlight_1_two = highlight_1_three = highlight_2_two = highlight_2_three = false;
}


CESTimerRadar::~CESTimerRadar()
{
	try {
		this->OnAsrContentToBeSaved();
		//this->EuroScopePlugInExitCustom();
	}
	catch (exception& e) {
		stringstream s;
		s << e.what() << endl;
		AfxMessageBox(string("Error occurred " + s.str()).c_str());
	}
}


//---OnAsrContentLoaded--------------------------------------------

void CESTimerRadar::OnAsrContentLoaded(bool Loaded)
{
	const char* p_value;
	if ((p_value = GetDataFromAsr(string("TimerTopLeftX").c_str())) != NULL) {
		m_Area.left = atoi(p_value);
		m_Area.right = m_Area.left + m_Offset.x;
	}
	if ((p_value = GetDataFromAsr(string("TimerTopLeftY").c_str())) != NULL) {
		m_Area.top = atoi(p_value);
		m_Area.bottom = m_Area.top + m_Offset.y;
	}
}


//---OnAsrContentToBeSaved------------------------------------------

void CESTimerRadar::OnAsrContentToBeSaved()
{
	SaveDataToAsr(string("TimerTopLeftX").c_str(), "Timer position", to_string(m_Area.left).c_str());
	SaveDataToAsr(string("TimerTopLeftY").c_str(), "Timer position", to_string(m_Area.top).c_str());
}


//---OnRefresh------------------------------------------------------

void CESTimerRadar::OnRefresh(HDC hDC, int Phase)
{
	if (Phase != REFRESH_PHASE_AFTER_LISTS)
		return;

	// Basics
	CDC dc;
	dc.Attach(hDC);

	dc.SetTextColor(qTextColor);
	CBrush textBorderBrush(qTextColor);
	CBrush borderBrush(qBorderColor);
	CBrush backgroundBrush(qBackgroundColor);
	
	// Fonts
	CFont fontButton, fontTimer;
	fontButton.CreateFont(15, 0, 0, 0, 0, false, false,
		0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		FIXED_PITCH | FF_MODERN, _T("Arial"));
	fontTimer.CreateFont(18, 0, 0, 0, 0, false, false,
		0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		FIXED_PITCH | FF_MODERN, _T("Arial"));

	CFont* oldFont = dc.SelectObject(&fontTimer);
	

	// Base Rect
	CRect windowAreaCRect(m_Area);
	windowAreaCRect.NormalizeRect();
	
	dc.FillSolidRect(windowAreaCRect, qBackgroundColor);
	dc.FrameRect(windowAreaCRect, &borderBrush);
	AddScreenObject(DRAWING_APPWINDOW, "window", windowAreaCRect, true, "");


	// Rects
	CRect tempAreaCRect(windowAreaCRect.left + 6, windowAreaCRect.top + 6, windowAreaCRect.left + 57, windowAreaCRect.bottom - 6);
	CRect buttonAreaCRect(b_Area);
	buttonAreaCRect.NormalizeRect();
	CRgn buttonAreaCRgn;
	buttonAreaCRgn.CreateRectRgn(buttonAreaCRect.left, buttonAreaCRect.top, buttonAreaCRect.right, buttonAreaCRect.bottom);
	char tempS[6];
	
	if (timer1.tm_min > 0 || timer1.tm_sec > 0) {	
		strftime(tempS, 6, "%M:%S", &timer1);
		dc.DrawText(tempS, strlen(tempS), tempAreaCRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
		AddScreenObject(DRAWING_1, "", tempAreaCRect, true, "");

		buttonAreaCRect.OffsetRect(windowAreaCRect.left + 24, windowAreaCRect.top);
		buttonAreaCRgn.OffsetRgn(windowAreaCRect.left + 24, windowAreaCRect.top);
	}
	else
	{
		dc.SelectObject(&fontButton);
		buttonAreaCRect.OffsetRect(windowAreaCRect.TopLeft());
		buttonAreaCRgn.OffsetRgn(windowAreaCRect.TopLeft());
		if (highlight_1_two) {
			dc.FillSolidRect(buttonAreaCRect, qHighlightColor);
			dc.FrameRgn(&buttonAreaCRgn, &textBorderBrush, 2, 2);
		}
		else
			dc.FrameRgn(&buttonAreaCRgn, &textBorderBrush, 1, 1);

		dc.DrawText("2", 1, buttonAreaCRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
		AddScreenObject(DRAWING_1_TWO, "", buttonAreaCRect, false, "");

		buttonAreaCRect.OffsetRect(24, 0);
		buttonAreaCRgn.OffsetRgn(24, 0);
		if (highlight_1_three) {
			dc.FillSolidRect(buttonAreaCRect, qHighlightColor);
			dc.FrameRgn(&buttonAreaCRgn, &textBorderBrush, 2, 2);
		}
		else
			dc.FrameRgn(&buttonAreaCRgn, &textBorderBrush, 1, 1);
		
		dc.DrawText("3", 1, buttonAreaCRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
		AddScreenObject(DRAWING_1_THREE, "", buttonAreaCRect, false, "");
	}

	
	if (timer2.tm_min > 0 || timer2.tm_sec > 0) {
		dc.SelectObject(&fontTimer);
		tempAreaCRect.OffsetRect(55, 0);
		strftime(tempS, 6, "%M:%S", &timer2);
		dc.DrawText(tempS, strlen(tempS), tempAreaCRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
		AddScreenObject(DRAWING_2, "", tempAreaCRect, true, "");
	}
	else
	{
		dc.SelectObject(&fontButton);
		buttonAreaCRect.OffsetRect(31, 0);
		buttonAreaCRgn.OffsetRgn(31, 0);
		if (highlight_2_two) {
			dc.FillSolidRect(buttonAreaCRect, qHighlightColor);
			dc.FrameRgn(&buttonAreaCRgn, &textBorderBrush, 2, 2);
		}
		else
			dc.FrameRgn(&buttonAreaCRgn, &textBorderBrush, 1, 1);
		
		dc.DrawText("2", 1, buttonAreaCRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
		AddScreenObject(DRAWING_2_TWO, "", buttonAreaCRect, false, "");

		buttonAreaCRect.OffsetRect(24, 0);
		buttonAreaCRgn.OffsetRgn(24, 0);
		if (highlight_2_three) {
			dc.FillSolidRect(buttonAreaCRect, qHighlightColor);
			dc.FrameRgn(&buttonAreaCRgn, &textBorderBrush, 2, 2);
		}
		else
			dc.FrameRgn(&buttonAreaCRgn, &textBorderBrush, 1, 1);
		
		dc.DrawText("3", 1, buttonAreaCRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
		AddScreenObject(DRAWING_2_THREE, "", buttonAreaCRect, false, "");		
	}

	
	// Releasing after the drawing
	dc.SelectObject(oldFont);
	dc.Detach();
}


//---OnClickScreenObject-----------------------------------------

void CESTimerRadar::OnClickScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, int Button)
{
	if (Button != BUTTON_LEFT)
		return;
	
	if (ObjectType == DRAWING_1) {
		timer1.tm_min = timer1.tm_sec = 0;		
	}
	else if (ObjectType == DRAWING_2) {
		timer2.tm_min = timer2.tm_sec = 0;
	}
	else if (ObjectType == DRAWING_1_TWO) {
		timer1.tm_min = 2;
		timer1.tm_sec = 0;
	}
	else if (ObjectType == DRAWING_1_THREE) {
		timer1.tm_min = 3;
		timer1.tm_sec = 0;
	}
	else if (ObjectType == DRAWING_2_TWO) {
		timer2.tm_min = 2;
		timer2.tm_sec = 0;
	}
	else if (ObjectType == DRAWING_2_THREE) {
		timer2.tm_min = 3;
		timer2.tm_sec = 0;
	}
}


//---OnMoveScreenObject---------------------------------------------

void CESTimerRadar::OnMoveScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, bool Released)
{
	if (strcmp(sObjectId, "window") == 0) {

		CRect appWindowRect(m_Area);
		appWindowRect.NormalizeRect();

		POINT TopLeft = { Area.left, Area.top };
		POINT BottomRight = { TopLeft.x + appWindowRect.Width(), TopLeft.y + appWindowRect.Height() };
		CRect newPos(TopLeft, BottomRight);
		newPos.NormalizeRect();

		m_Area = newPos;
	}
}


//---OnButtonDownScreenObject---------------------------------------------

void CESTimerRadar::OnButtonDownScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, int Button)
{
	if (Button != BUTTON_LEFT)
		return;

	if (ObjectType == DRAWING_1_TWO) {
		highlight_1_two = true;
	}
	else if (ObjectType == DRAWING_1_THREE) {
		highlight_1_three = true;
	}
	else if (ObjectType == DRAWING_2_TWO) {
		highlight_2_two = true;
	}
	else if (ObjectType == DRAWING_2_THREE) {
		highlight_2_three = true;
	}
}


//---OnButtonDownScreenObject---------------------------------------------

void CESTimerRadar::OnButtonUpScreenObject(int ObjectType, const char* sObjectId, POINT Pt, RECT Area, int Button)
{
	if (Button != BUTTON_LEFT)
		return;
	
	if (ObjectType == DRAWING_1_TWO) {
		highlight_1_two = false;
	}
	else if (ObjectType == DRAWING_1_THREE) {
		highlight_1_three = false;
	}
	else if (ObjectType == DRAWING_2_TWO) {
		highlight_2_two = false;
	}
	else if (ObjectType == DRAWING_2_THREE) {
		highlight_2_three = false;
	}	
}

