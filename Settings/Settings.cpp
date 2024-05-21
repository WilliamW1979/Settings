#include "Settings.h"


bool SETTINGS::LoadSettings()
{
	Settings.clear();
	ifstream in;
	in.open(filename, std::ifstream::in);
	if (!in.good())
		return false;
	string Category = "";
	__int8 Categorycount = 0;
	while (in)
	{
		string data;
		char buffer[1000];
		in.getline(buffer, 1000);
		data = buffer;
		if (data.size() >= 2)
			if (data[0] == '/' && data[0] == '/') {}// We have a comment!
			else if (data[0] == '[') // We have a Category
			{
				data.erase(std::remove(data.begin(), data.end(), '['), data.end());
				data.erase(std::remove(data.begin(), data.end(), ']'), data.end());
				Category = data;
				Categorycount++;
			}
			else if (data.find("Program Version: ") == 0)
			{
				version = data;
				version.erase(data.find("Program Version: "), sizeof("Program Version: ")-1);
			}
			else
			{
				std::size_t found = data.find(Breaker);
				if (found != std::string::npos)
				{
					string first = data.substr(0, found);
					string second = data.substr(found + 1, data.length());
					while (second[0] == ' ')
						second.erase(0, 1);
					SETTING s;
					s.Category = Category;
					s.Setting = first;
					s.Data = second;
					Settings.push_back(s);
				}
			}
	}
	return true;
}

bool SETTINGS::SaveSettings()
{
	ofstream out;
	out.open(filename, std::ofstream::out);
	if (!out.good())
		return false;

	out << "// Settings File\n//\n// This file was created based on William Glenn Ward's Setting Library to easily write and read to a settings file.\n//\n// Using this library is allowed by anyone for FREE as long as credit is given.\n\nProgram Version: " << version << "\n\n\n";

	deque<string> Cat;

	for (SETTING data : Settings)
	{
		if (data.Category == "")
			out << data.Setting << ": " << data.Data << endl;
		else
			if (find(Cat.begin(), Cat.end(), data.Category) == Cat.end())
				Cat.push_back(data.Category);
	}

	for (string Category : Cat)
	{
		out << endl << "[" << Category << "]" << endl << endl;
		for (SETTING data : Settings)
			if (data.Category == Category)
				out << data.Setting << ": " << data.Data << endl;
	}

	return true;
}

int SETTINGS::GetCount(string category)
{
	int count = 0;
	for (SETTING d : Settings)
		if (d.Category == category)
			count++;
	return count;
}

bool SETTINGS::Get(string setting, string &data, string category)
{
	for (SETTING temp : Settings)
		if (setting == temp.Setting && category == temp.Category)
		{
			data = temp.Data;
			return true;
		}
	data = "";
	return false;
}

bool SETTINGS::Get(string setting, bool &data, string category)
{
	for(SETTING temp : Settings)
		if (setting == temp.Setting && category == temp.Category)
		{
			if (temp.Data == "true")
			{
				data = true;
				return true;
			}
			else if (temp.Data == "false")
			{
				data = false;
				return true;
			}
		}
	return false;
}

bool SETTINGS::Get(string setting, __int8 &data, string category)
{
	for (SETTING temp : Settings)
		if (setting == temp.Setting && category == temp.Category)
		{
			std::stringstream ss;
			ss << temp.Data;
			ss >> data;
			return true;
		}
	return false;
}

bool SETTINGS::Get(string setting, __int16 &data, string category)
{
	for (SETTING temp : Settings)
		if (setting == temp.Setting && category == temp.Category)
		{
			std::stringstream ss;
			ss << temp.Data;
			ss >> data;
			return true;
		}
	return false;
}

bool SETTINGS::Get(string setting, int &data, string category)
{
	for (SETTING temp : Settings)
		if (setting == temp.Setting && category == temp.Category)
		{
			std::stringstream ss;
			ss << temp.Data;
			ss >> data;
			return true;
		}
	return false;
}

bool SETTINGS::Get(string setting, long long& data, string category)
{
	for (SETTING temp : Settings)
		if (setting == temp.Setting && category == temp.Category)
		{
			std::stringstream ss;
			ss << temp.Data;
			ss >> data;
			return true;
		}
	return false;
}

bool SETTINGS::Get(string setting, unsigned __int8 &data, string category)
{
	for (SETTING temp : Settings)
		if (setting == temp.Setting && category == temp.Category)
		{
			std::stringstream ss;
			ss << temp.Data;
			ss >> data;
			return true;
		}
	return false;
}

bool SETTINGS::Get(string setting, unsigned __int16 &data, string category)
{
	for (SETTING temp : Settings)
		if (setting == temp.Setting && category == temp.Category)
		{
			std::stringstream ss;
			ss << temp.Data;
			ss >> data;
			return true;
		}
	return false;
}

bool SETTINGS::Get(string setting, unsigned int &data, string category)
{
	for (SETTING temp : Settings)
		if (setting == temp.Setting && category == temp.Category)
		{
			std::stringstream ss;
			ss << temp.Data;
			ss >> data;
			return true;
		}
	return false;
}

bool SETTINGS::Get(string setting, unsigned long long &data, string category)
{
	for (SETTING temp : Settings)
		if (setting == temp.Setting && category == temp.Category)
		{
			std::stringstream ss;
			ss << temp.Data;
			ss >> data;
			return true;
		}
	return false;
}

void SETTINGS::AddString(string setting, string data, string category)
{
	for (SETTING s : Settings)
		if (s.Setting == setting && s.Category == category)
		{
			deque<SETTING>::iterator x = find(Settings.begin(), Settings.end(), s);
			if (x != Settings.end())
				x->Data = data;
			return;
		}
	SETTING temp;
	temp.Category = category;
	temp.Setting = setting;
	temp.Data = data;
	Settings.push_back(temp);
}

void SETTINGS::AddBool(string setting, bool data, string category)
{
	for (SETTING s : Settings)
		if (s.Setting == setting && s.Category == category)
		{
			deque<SETTING>::iterator x = find(Settings.begin(), Settings.end(), s);
			if (x != Settings.end())
			{
				if (data) x->Data = "true";
				else x->Data = "false";
			}
			return;
		}
	SETTING temp;
	temp.Category = category;
	temp.Setting = setting;
	if (data) temp.Data = "true";
	else temp.Data = "false";
	Settings.push_back(temp);
}

void SETTINGS::Add(string setting, __int8 data, string category)
{
	std::stringstream ss;
	ss << data;
	for (SETTING s : Settings)
		if (s.Setting == setting && s.Category == category)
		{
			deque<SETTING>::iterator x = find(Settings.begin(), Settings.end(), s);
			if (x != Settings.end())
			{
				ss >> x->Data;
			}
			return;
		}
	SETTING temp;
	temp.Category = category;
	temp.Setting = setting;
	ss >> temp.Data;
	Settings.push_back(temp);
}

void SETTINGS::Add(string setting, __int16 data, string category)
{
	std::stringstream ss;
	ss << data;
	for (SETTING s : Settings)
		if (s.Setting == setting && s.Category == category)
		{
			deque<SETTING>::iterator x = find(Settings.begin(), Settings.end(), s);
			if (x != Settings.end())
			{
				ss >> x->Data;
			}
			return;
		}
	SETTING temp;
	temp.Category = category;
	temp.Setting = setting;
	ss >> temp.Data;
	Settings.push_back(temp);
}

void SETTINGS::Add(string setting, int data, string category)
{
	std::stringstream ss;
	ss << data;
	for (SETTING s : Settings)
		if (s.Setting == setting && s.Category == category)
		{
			deque<SETTING>::iterator x = find(Settings.begin(), Settings.end(), s);
			if (x != Settings.end())
				ss >> x->Data;
			return;
		}
	SETTING temp;
	temp.Category = category;
	temp.Setting = setting;
	ss >> temp.Data;
	Settings.push_back(temp);
}

void SETTINGS::Add(string setting, long long data, string category)
{
	std::stringstream ss;
	ss << data;
	for (SETTING s : Settings)
		if (s.Setting == setting && s.Category == category)
		{
			deque<SETTING>::iterator x = find(Settings.begin(), Settings.end(), s);
			if (x != Settings.end())
			{
				ss >> x->Data;
			}
			return;
		}
	SETTING temp;
	temp.Category = category;
	temp.Setting = setting;
	ss >> temp.Data;
	Settings.push_back(temp);
}

void SETTINGS::Add(string setting, unsigned __int8 data, string category)
{
	std::stringstream ss;
	ss << data;
	for (SETTING s : Settings)
		if (s.Setting == setting && s.Category == category)
		{
			deque<SETTING>::iterator x = find(Settings.begin(), Settings.end(), s);
			if (x != Settings.end())
			{
				ss >> x->Data;
			}
			return;
		}
	SETTING temp;
	temp.Category = category;
	temp.Setting = setting;
	ss >> temp.Data;
	Settings.push_back(temp);
}

void SETTINGS::Add(string setting, unsigned __int16 data, string category)
{
	std::stringstream ss;
	ss << data;
	for (SETTING s : Settings)
		if (s.Setting == setting && s.Category == category)
		{
			deque<SETTING>::iterator x = find(Settings.begin(), Settings.end(), s);
			if (x != Settings.end())
			{
				ss >> x->Data;
			}
			return;
		}
	SETTING temp;
	temp.Category = category;
	temp.Setting = setting;
	ss >> temp.Data;
	Settings.push_back(temp);
}

void SETTINGS::Add(string setting, unsigned int data, string category)
{
	std::stringstream ss;
	ss << data;
	for (SETTING s : Settings)
		if (s.Setting == setting && s.Category == category)
		{
			deque<SETTING>::iterator x = find(Settings.begin(), Settings.end(), s);
			if (x != Settings.end())
				ss >> x->Data;
			return;
		}
	SETTING temp;
	temp.Category = category;
	temp.Setting = setting;
	ss >> temp.Data;
	Settings.push_back(temp);
}

void SETTINGS::Add(string setting, unsigned long long data, string category)
{
	std::stringstream ss;
	ss << data;
	for (SETTING s : Settings)
		if (s.Setting == setting && s.Category == category)
		{
			deque<SETTING>::iterator x = find(Settings.begin(), Settings.end(), s);
			if (x != Settings.end())
			{
				ss >> x->Data;
			}
			return;
		}
	SETTING temp;
	temp.Category = category;
	temp.Setting = setting;
	ss >> temp.Data;
	Settings.push_back(temp);
}

void SETTINGS::Get(deque<string>& settings, deque<__int8>& data, string category)
{
	for (SETTING temp : Settings)
		if (category == temp.Category)
		{
			settings.push_back(temp.Setting);
			settings.push_back(temp.Data);
		}
}

void SETTINGS::Get(deque<string>& settings, deque<__int16>& data, string category)
{
	for (SETTING temp : Settings)
		if (category == temp.Category)
		{
			settings.push_back(temp.Setting);
			settings.push_back(temp.Data);
		}
}

void SETTINGS::Get(deque<string>& settings, deque<int>& data, string category)
{
	for (SETTING temp : Settings)
		if (category == temp.Category)
		{
			settings.push_back(temp.Setting);
			settings.push_back(temp.Data);
		}
}

void SETTINGS::Get(deque<string>& settings, deque<long long>& data, string category)
{
	for (SETTING temp : Settings)
		if (category == temp.Category)
		{
			settings.push_back(temp.Setting);
			settings.push_back(temp.Data);
		}
}

void SETTINGS::Get(deque<string>& settings, deque<unsigned __int8>& data, string category)
{
	for (SETTING temp : Settings)
		if (category == temp.Category)
		{
			settings.push_back(temp.Setting);
			settings.push_back(temp.Data);
		}
}

void SETTINGS::Get(deque<string>& settings, deque<unsigned __int16> &data, string category)
{
	for (SETTING temp : Settings)
		if (category == temp.Category)
		{
			settings.push_back(temp.Setting);
			settings.push_back(temp.Data);
		}
}

void SETTINGS::Get(deque<string>& settings, deque<unsigned int> &data, string category)
{
	for (SETTING temp : Settings)
		if (category == temp.Category)
		{
			settings.push_back(temp.Setting);
			settings.push_back(temp.Data);
		}
}

void SETTINGS::Get(deque<string>& settings, deque<unsigned long long> &data, string category)
{
	for (SETTING temp : Settings)
		if (category == temp.Category)
		{
			settings.push_back(temp.Setting);
			settings.push_back(temp.Data);
		}
}

void SETTINGS::Get(deque<string>& settings, deque<string> &data, string category)
{
	for (SETTING temp : Settings)
		if (category == temp.Category)
		{
			settings.push_back(temp.Setting);
			settings.push_back(temp.Data);
		}
}

bool SETTINGS::Remove(string setting, string category)
{
	for(SETTING s : Settings)
		if (s.Setting == setting && s.Category == category)
		{
			deque<SETTING>::iterator x = find(Settings.begin(), Settings.end(), s);
			if (x != Settings.end())
				Settings.erase(x);
			return true;
		}
	return false;
}