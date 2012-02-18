#include "IniFile.h"

unsigned int IniFile::nbChar = 256;

IniFile::IniFile(const std::string &File) : myName(File), myStream(File.c_str(), std::fstream::in | std::fstream::out)
{
	if(!myStream.good()) std::cerr << "Error opening ini File" << std::endl;
}

IniFile::~IniFile()
{
	myStream.close();
}

std::string IniFile::GetValue(std::string const &Section, std::string const &Key, const std::string Default)
{
	myStream.seekg(0);
	char temp[IniFile::nbChar];
	while(!myStream.eof())
	{
		myStream.getline(temp, IniFile::nbChar, '\n');
		if(temp[0] == '[')
		{
			unsigned int i = 1;
			char temp2[IniFile::nbChar];
			while((temp[i] != ']')&&(i < IniFile::nbChar))
				temp2[i-1] = temp[i], i++;
			temp2[i-1] = '\0';


			if(Section.compare(temp2) == 0)
			{
				char tmp_key[IniFile::nbChar];
				char tmp_value[IniFile::nbChar];
				while((strcmp(tmp_key, Key.c_str()) != 0)&&(tmp_key[0] != '[')&&(!myStream.eof()))
				{
					myStream.getline(tmp_key, IniFile::nbChar, '='); // Récupère la clé
					myStream.getline(tmp_value, IniFile::nbChar, '\n'); // Récupère la valeur associée
				}

				if(strcmp(tmp_key, Key.c_str()) == 0) return tmp_value;
				else return Default;
			}
		}
	}
	return Default;
}

void IniFile::ReadPairs(std::string const &Section, std::map<std::string, std::string> &map)
{
	myStream.seekg(0);
	map.clear();
	char temp[IniFile::nbChar];
	while(!myStream.eof())
	{
		myStream.getline(temp, IniFile::nbChar, '\n');
		if(temp[0] == '[')
		{
			unsigned int i = 1;
			char temp2[IniFile::nbChar];
			while((temp[i] != ']')&&(i < IniFile::nbChar))
				temp2[i-1] = temp[i], i++;
			temp2[i-1] = '\0';

			if(Section.compare(temp2) == 0)
			{
				char tmp_key[IniFile::nbChar], tmp_value[IniFile::nbChar];
				do
				{
					myStream.getline(tmp_key, IniFile::nbChar, '='); // Récupère la clé
					myStream.getline(tmp_value, IniFile::nbChar, '\n'); // Récupère la valeur associée
					if((tmp_key[0] == '[')||(tmp_key[0] == '\n')) break;
					map.insert(std::pair<std::string, std::string>(std::string(tmp_key), std::string(tmp_value)));
				} while((tmp_key[0] != '[')&&(!myStream.eof()));
				break;
			}
		}
	}
}
