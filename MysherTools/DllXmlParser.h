// DllXmlParser.h: interface for the DllXmlParser class.
//
// DllXmlParser Debug 1.0
// Copyright (C) 2016-2026 Beijing Mysher Technology CO., LTD All rights reserved
// Use in commercial applications requires written permission
// This software is provided "as is", with no warranty.

#pragma once
#include <string>
using namespace std;
class DllXmlParser
{
//����
public:
	//��ȡDLL����
	static std::string GetDllName(std::string strKey);
	
	//��ȡDLL����(����ͷ)
	static std::wstring GetDllName(std::wstring wstrKey);

};

