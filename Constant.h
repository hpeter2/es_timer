#pragma once
#include "stdafx.h"
#include "EuroScopePlugIn.h"
#define _USE_MATH_DEFINES
#include <vector>
#include <thread>
#include <mmsystem.h>
#include <string>
#include <iostream>

using namespace std;
using namespace EuroScopePlugIn;


const int DRAWING_APPWINDOW = 1211;
const int DRAWING_1 = 1212;
const int DRAWING_1_TWO = 1213;
const int DRAWING_1_THREE = 1214;
const int DRAWING_2 = 1215;
const int DRAWING_2_TWO = 1216;
const int DRAWING_2_THREE = 1217;

const COLORREF qBackgroundColor(RGB(26, 26, 26));
const COLORREF qHighlightColor(RGB(125, 125, 125));
const COLORREF qBorderColor(RGB(45, 45, 48));
const COLORREF qTextColor(RGB(102, 205, 170));
