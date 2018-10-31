// PathManager.h: interface for the PathManager class.
//
// PathManager Debug 1.0
// Copyright (C) 2016-2026 Beijing Mysher Technology CO., LTD All rights reserved
// Use in commercial applications requires written permission
// This software is provided "as is", with no warranty.
#pragma once

#include <string>
using namespace std;

class PathManager
{
public:
	//获取当前模块路径
	static string GetAppPath();
};

