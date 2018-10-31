// DllParser.h: interface for the DllParser class.
//
// DllParser Debug 1.0
// Copyright (C) 2016-2026 Beijing Mysher Technology CO., LTD All rights reserved
// Use in commercial applications requires written permission
// This software is provided "as is", with no warranty.
#pragma once

#include <windows.h>
#include <string>
#include <map>
#include <functional>
using namespace std;

typedef std::map<string, void*> Function;
class DllParser
{
public:
    DllParser()
    {
		m_hMod = nullptr;
    }

    ~DllParser()
    {
        UnLoad();
    }

    bool Load(const string& dllPath)
    {
		UnLoad();
        m_hMod = LoadLibraryA(dllPath.data());
        if (nullptr == m_hMod)
        {
            printf("LoadLibrary failed\n");
            return false;
        }

        return true;
    }

    bool UnLoad()
    {
		m_mapFunction.clear();
        if (m_hMod == nullptr)
            return true;

        auto b = FreeLibrary(m_hMod);
        if (!b)
            return false;

        m_hMod = nullptr;
        return true;
    }

    template <typename T>
    T* GetFunction(const string& funcName)
    {
		if(m_hMod == nullptr)
		{
			//如果Load没有成功直接返回
			return 0;
		}
		Function::iterator iter = m_mapFunction.find(funcName); 
		if(iter != m_mapFunction.end())
		{
			//如果已经创建函数则直接返回
			return (T*)(iter->second);
		}
		//如果没有创建函数则先创建函数并存储
        auto addr = GetProcAddress(m_hMod, funcName.c_str());
		if(addr == 0)
		{
			return 0;
		}
		m_mapFunction.insert(Function :: value_type(funcName, addr));
        return (T*) (addr);
    }

    /*template <typename T, typename... Args>
    typename std::result_of<std::function<T>(Args...)>::type ExcecuteFunc(const string& funcName, Args&&... args)
    {
        auto f = GetFunction<T>(funcName);
        if (f == nullptr)
        {
            string s = "can not find this function " + funcName;
            throw std::exception(s.c_str());
        }            

        return f(std::forward<Args>(args)...);
    }*/


private:
    HMODULE m_hMod;
	//std::map<string, FARPROC> m_map;
    std::map<string, void*> m_mapFunction;
};