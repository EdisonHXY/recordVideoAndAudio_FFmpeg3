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
	//����ͷת����ͷ
	static std::wstring ConvertWA_A2W(string strSrc);

	//����ͷת����ͷ
	static std::string ConvertWA_W2A(std::wstring wstrSrc);

};