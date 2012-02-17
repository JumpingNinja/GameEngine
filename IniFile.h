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
	
	///@brief costructeur à partir d'un nom de fichier
	///@param File nom du fichier
	IniFile(const std::string &File);
	///@brief destructeur
	~IniFile();
	
	/**
	 @brief Lis toutes les paire d'une section et les stocke dans une map (très utile pour les key par exemple
	 @param Section section où lire
	 @param map map où enregistrer la lecture
	 **/
	void ReadPairs(const std::string &Section, std::map<std::string, std::string> &map);
	
	/**
	 @brief lis une valeur en particulier
	 @param Section section où lire
	 @param Key clé à lire
	 @param Default retournée quand la clé n'a pas été trouvée
	 @return la valeur trouvée pour la clé en format de texte
	 **/
	std::string GetValue(const std::string &Section, const std::string &Key, const std::string Default="");
};

#endif
