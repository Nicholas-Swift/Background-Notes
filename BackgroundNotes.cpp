// BackgroundNotes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//#include <SFML/Graphics.hpp>

std::vector<std::string> LoadData()
{
	std::vector<std::string> strings;
	std::ifstream props("data/properties.txt");
	if(props.is_open())
	{
		std::string strLine = "";
		while(std::getline(props, strLine))
		{
			strings.push_back(strLine);
		}
	}
	props.close();
	return strings;
}

void SaveData(std::vector<std::string> s)
{
	std::ofstream props("data/properties.txt");
	props.clear();
	for(int i = 0; i < s.size(); i++)
		props<<s[i]<<"\n";
	props.close();
}

void Help()
{
	//display help stuff
	std::cout<<"For more help, contact Nicholas Swift at www.nicholas-swift.com/contact.html"<<std::endl;
	std::cout<<"help         Get a list of possible commands to use"<<std::endl;
	std::cout<<"add          Add a new note"<<std::endl;
	std::cout<<"delete       Delete a note"<<std::endl;
	std::cout<<"modify       Modify a note"<<std::endl;
	std::cout<<"save         Save"<<std::endl;
	std::cout<<"exit         Safely exit"<<std::endl;

	std::cout<<std::endl;
}

void Add(std::vector<std::string> &s, std::string str)
{
	//go to add prompt and stuff
	str.erase(0, 4);
	s.push_back(str);

	std::cout<<std::endl;
}

void Delete(std::vector<std::string> &s, std::string str)
{
	//delete stuff
	str.erase(0, 7);
	if(std::stoi(str) > s.size() - 1)
		{}
	else
		s.erase(s.begin() + std::stoi(str));

	std::cout<<std::endl;
}

void Modify(std::vector<std::string> &s, std::string str)
{
	//modify stuff
	str.erase(0, 7);
	std::string sentence = str;
	int num = -1;

	for(int i = 0; i < str.size(); i++)
	{
		if(str[i] == ' ')
		{
			str.erase(i, str.size()-i);
			sentence.erase(0, i+1);
		}
	}

	num = std::stoi(str);
	s[num] = sentence;

	std::cout<<std::endl;
}

void Clear(std::vector<std::string> &s)
{
	begin:
	char c;
	std::cout<<"Are you sure? (y/n): ";
	std::cin>>c;
	if(c == 'y')
	{
		s.clear();
		SaveData(s);
	}
	else if(c == 'n')
	{
		return;
	}
	else
	{
		std::cout<<"Try again."<<std::endl;
		goto begin;
	}
}

void Save(std::vector<std::string> s)
{
	SaveData(s);
	std::cout<<"data successfully saved.\n"<<std::endl;
}

void Exit(std::vector<std::string> s, bool &b)
{
	SaveData(s);
	b = true;
}

void GeneralDisplay(std::vector<std::string> s)
{
	//display strings
	std::cout<<"Your current notes are..."<<std::endl;
	for(int i = 0; i < s.size(); i++)
	{
		std::cout<<"     ("<<i<<")"<<s[i]<<std::endl;
	}

	std::cout<<std::endl;
}

void ParseInput(std::vector<std::string> &s, bool &b)
{
	begin:
	//get input
	std::string str;
	std::cout<<">";
	//std::cin>>str;
	//std::cin.getline(str, str.size());
	std::getline(std::cin, str);

	if(str == "help")
		Help();
	else if(str[0] == 'a' && str[1] == 'd' && str[2] == 'd') //add
		Add(s, str);
	else if(str[0] == 'd' && str[1] == 'e' && str[2] == 'l' && str[3] == 'e' && str[4] == 't' && str[5] == 'e') //delete
		Delete(s, str);
	else if(str[0] == 'm' && str[1] == 'o' && str[2] == 'd' && str[3] == 'i' && str[4] == 'f' && str[5] == 'y') //modify
		Modify(s, str);
	else if(str == "clear")
		Clear(s);
	else if(str == "save")
		Save(s);
	else if(str == "exit")
		Exit(s, b);
	else
	{
		std::cout<<"Nope. Try again, type help for help.\n"<<std::endl;
		goto begin;
	}
}

/*void SetBackground(std::string p)
{
	std::string sPath = p;
	char cPath[150];
	strcpy(cPath, sPath.c_str());
	char *pPath;
	pPath = cPath;

	std::cout<<pPath<<std::endl;

    int result;
    result = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, pPath, SPIF_UPDATEINIFILE);

    if(result)
        std::cout<<"Wallpaper set";
    else
        std::cout<<"Wallpaper not set";
}

void CreateImage(std::vector<std::string> strings)
{
	sf::Image background;
	background.create(1366, 768, sf::Color::White);

	background.saveToFile("data/background.jpg");
} */

int main()
{
	//Display intro
	std::cout<<"Background Notes [Version 0.0.0.1]"<<std::endl;
	std::cout<<"(c) 2015 Swift Studios. All rights reserved.\n"<<std::endl;

	//Load current strings
	std::vector<std::string> strings = LoadData();

	//while loop
	bool exit = false;
	while(1)
	{
		GeneralDisplay(strings);
		ParseInput(strings, exit);
		if(exit)
			break;
	}

	SaveData(strings);

	return 0;
}

