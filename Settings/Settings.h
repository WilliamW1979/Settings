#pragma once
#ifndef SETTINGS_WGW
#define SETTINGS_WGW

// This program was developed to make accessing Settings Files easy and painless.
// It is simple to use, you declare the class, set up the file you wish it to use, and it will automatically
// and write the data for you. You can organize by categories which will be listed in the file as [CATEGORY NAME]
// allowing you to organize it. The program will read the file, store it in the class, and then allow you to pull
// the information based on what you saved.
//
// Written by:
// 
// William Glenn Ward
// WilliamW1979@netscape.net
// Computer Programmer / Graphic Designer

#if _M_IX86 && _DEBUG
#define ADD_WGW "_32_DEBUG"
#elif _M_IX86
#define ADD_WGW "_32"
#elif _DEBUG
#define ADD_WGW "_DEBUG"
#endif
#ifdef ADD_WGW
#pragma comment(lib, SETTINGS_WGW ADD_WGW ".lib")
#else
#pragma comment(lib, SETTINGS_WGW ".lib")
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <deque>

using std::string;
using std::ofstream;
using std::ifstream;
using std::deque;
using std::endl;
using std::find;

struct SETTING
{
	string Category;
	string Setting;
	string Data;

	bool operator==(const SETTING& s) { return std::tie(s.Category, s.Setting, s.Data) == std::tie(Category, Setting, Data); };
};

class SETTINGS
{
private:
	deque<SETTING> Settings;
	string filename = "Settings.ini";
	string version;
	char Breaker = ':';
	char Breaker2 = '|';

public:
	SETTINGS() {};
	SETTINGS(string Filename) { filename = Filename; };
	~SETTINGS() {};

	void SetFile(string file) { filename = file; };
	void SetVersion(string Version) { version = Version; };
	string GetVersion() { return version; };
	int GetCount(string Category);
	void SetBreakers(char first = ':', char second = '|') {	Breaker = first; Breaker2 = second; };
	void ClearSettings() { Settings.clear(); };
	bool LoadSettings();
	bool SaveSettings();

	void AddString(string setting, string data, string category = "");
	void AddBool(string setting, bool data, string category = "");
	void Add(string setting, __int8 data, string category = "");
	void Add(string setting, __int16 data, string category = "");
	void Add(string setting, int data, string category = "");
	void Add(string setting, long long data, string category = "");
	void Add(string setting, unsigned __int8 data, string category = "");
	void Add(string setting, unsigned __int16 data, string category = "");
	void Add(string setting, unsigned int data, string category = "");
	void Add(string setting, unsigned long long data, string category = "");
	bool Get(string setting, string &data, string category = "");
	bool Get(string setting, bool &data, string category = "");
	bool Get(string setting, __int8 &data, string category = "");
	bool Get(string setting, __int16 &data, string category = "");
	bool Get(string setting, int &data, string category = "");
	bool Get(string setting, long long &data, string category = "");
	bool Get(string setting, unsigned __int8 &data, string category = "");
	bool Get(string setting, unsigned __int16 &data, string category = "");
	bool Get(string setting, unsigned int& data, string category = "");
	bool Get(string setting, unsigned long long &data, string category = "");
	void Get(deque<string> &settings, deque<__int8> &data, string category = "");
	void Get(deque<string> &settings, deque<__int16> &data, string category = "");
	void Get(deque<string> &settings, deque<int> &data, string category = "");
	void Get(deque<string> &settings, deque<long long> &data, string category = "");
	void Get(deque<string> &settings, deque<unsigned __int8> &data, string category = "");
	void Get(deque<string> &settings, deque<unsigned __int16> &data, string category = "");
	void Get(deque<string> &settings, deque<unsigned int> &data, string category = "");
	void Get(deque<string> &settings, deque<unsigned long long> &data, string category = "");
	void Get(deque<string> &settings, deque<string> &data, string category = "");
	bool Remove(string setting, string category = "");
	unsigned long long Count() { return Settings.size(); };
};

#endif