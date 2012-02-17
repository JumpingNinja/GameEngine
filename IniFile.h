#ifndef _INIFILE_H_
#define _INIFILE_H_

#include <cstring>
#include <string>
#include <list>
#include <map>
#include <iostream>
#include <fstream>

class IniFile
{
	private:
		std::string myName;
		std::fstream myStream;

	public:
		static unsigned int nbChar;

		IniFile(std::string);
		~IniFile();

		void ReadPairs(std::string Section, std::map<std::string, std::string> &map);
		std::string GetValue(std::string Section, std::string Key);
};

#endif
