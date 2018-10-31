// ConvertWA.h: interface for the ConvertWA class.
//
// ConvertWA Debug 1.0
// Copyright (C) 2016-2026 Beijing Mysher Technology CO., LTD All rights reserved
// Use in commercial applications requires written permission
// This software is provided "as is", with no warranty.

#pragma once
#include <string>
using namespace std;
class ConvertWA
{
public:
	//多字头转宽字头
	static std::wstring ConvertWA_A2W(string strSrc);

	//宽字头转多字头
	static std::string ConvertWA_W2A(std::wstring wstrSrc);

};