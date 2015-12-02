// BackgroundNotes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

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

	SaveData(s);
}

void Delete(std::vector<std::string> &s, std::string str)
{
	//delete stuff
	str.erase(0, 7);
	if(std::stoi(str) > s.size() - 1)
	{
		std::cout<<"Did not delete."<<std::endl;
		std::cout<<"Reason: number too high."<<std::endl;
		std::cout<<std::endl;
	}
	else
	{
		s.erase(s.begin() + std::stoi(str));
		std::cout<<std::endl;
	}

	SaveData(s);
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

	if(num > s.size()-1)
	{
		std::cout<<"Did not modify."<<std::endl;
		std::cout<<"Reason: number too high."<<std::endl;
		std::cout<<std::endl;
	}
	else
	{
		s[num] = sentence;
		std::cout<<std::endl;
	}

	SaveData(s);
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

	SaveData(s);
}

void Save(std::vector<std::string> s)
{
	SaveData(s);
	std::cout<<"Data successfully saved.\n"<<std::endl;
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
		std::cout<<"Did not work."<<std::endl;
		std::cout<<"Reason: command not recognized."<<std::endl;
		std::cout<<"Type 'help' for help."<<std::endl;
		std::cout<<std::endl;
		goto begin;
	}
}

bool SetBackground()
{
	std::string filePath;
	const std::string strLocalDirectory = "C:\\Users\\Nick\\Documents\\1. Nick Stuff\\Programming\\(X) Projects 3\\BackgroundNotes\\Release\\"; // TWEAKED PATH

	int dirSize = 5;  //Will be automated later. 
	int bgChoice = 0; //Index of chosen wallpaper. 
  
	srand ( (unsigned int)time(NULL) );
	bgChoice = rand() % dirSize + 1;
	//Convert the index choice into a usable filename string.
	std::stringstream ssFilePath;
	//ssFilePath << strLocalDirectory << bgChoice << ".jpg";
	ssFilePath << strLocalDirectory << "output.jpg";
	//Returns true on success, false otherwise. 
	if( SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)ssFilePath.str().c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE) != 0)
	{
		filePath = ssFilePath.str();
		std::cout<<filePath<<std::endl;
		return true;
	}

	return false;
}

void CreateImage(std::vector<std::string> strings)
{
	//create the background
	cv::Mat image(480, 640, CV_8UC3);

	//add the text
	for(int i = 0; i < strings.size(); i++)
	{
		cv::putText(image, strings[i], cvPoint(10, 20*i + 20), CV_FONT_HERSHEY_SIMPLEX, 0.5, cvScalar(255, 255, 255));
	}

	//save the image
    cv::imwrite("output.jpg", image);
}

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
	CreateImage(strings);

	if(SetBackground())
	{ 
		std::cout <<"Applied Background";
	}
	else
	{  
		DWORD DWLastError = GetLastError();
		std::cout << "\nError: " << std::hex << DWLastError;
	}

	//std::cin.get();

	return 0;
}

