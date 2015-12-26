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
#include <opencv2/opencv.hpp>

//GLOBALS

std::vector<std::string> NotesLoadData()
{
	std::vector<std::string> strings;
	std::ifstream props("data/notes.txt");
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

void NotesSaveData(std::vector<std::string> s)
{
	std::ofstream props("data/notes.txt");
	props.clear();
	for(int i = 0; i < s.size(); i++)
		props<<s[i]<<"\n";
	props.close();

	system("background.exe");
}

void NotesHelp()
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

void NotesAdd(std::vector<std::string> &s, std::string str)
{
	//go to add prompt and stuff
	str.erase(0, 4);
	s.push_back(str);

	std::cout<<std::endl;

	NotesSaveData(s);
}

void NotesDelete(std::vector<std::string> &s, std::string str)
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

	NotesSaveData(s);
}

void NotesModify(std::vector<std::string> &s, std::string str)
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

	NotesSaveData(s);
}

void NotesClear(std::vector<std::string> &s)
{
	begin:
	char c;
	std::cout<<"Are you sure? (y/n): ";
	std::cin>>c;
	if(c == 'y')
	{
		s.clear();
		NotesSaveData(s);
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

	NotesSaveData(s);
}

void NotesSave(std::vector<std::string> s)
{
	NotesSaveData(s);
	std::cout<<"Data successfully saved.\n"<<std::endl;
}

void NotesExit(std::vector<std::string> s, bool &b)
{
	NotesSaveData(s);
	b = true;
}

void NotesGeneralDisplay(std::vector<std::string> s)
{
	//display strings
	std::cout<<"Your current notes are..."<<std::endl;
	for(int i = 0; i < s.size(); i++)
	{
		std::cout<<"     ("<<i<<")"<<s[i]<<std::endl;
	}

	std::cout<<std::endl;
}

void NotesParseInput(std::vector<std::string> &s, bool &b)
{
	begin:
	//get input
	std::string str;
	std::cout<<">";
	//std::cin>>str;
	//std::cin.getline(str, str.size());
	std::getline(std::cin, str);

	if(str == "help")
		NotesHelp();
	else if(str[0] == 'a' && str[1] == 'd' && str[2] == 'd') //add
		NotesAdd(s, str);
	else if(str[0] == 'd' && str[1] == 'e' && str[2] == 'l' && str[3] == 'e' && str[4] == 't' && str[5] == 'e') //delete
		NotesDelete(s, str);
	else if(str[0] == 'm' && str[1] == 'o' && str[2] == 'd' && str[3] == 'i' && str[4] == 'f' && str[5] == 'y') //modify
		NotesModify(s, str);
	else if(str == "clear")
		NotesClear(s);
	else if(str == "save")
		NotesSave(s);
	else if(str == "exit")
		NotesExit(s, b);
	else
	{
		std::cout<<"Did not work."<<std::endl;
		std::cout<<"Reason: command not recognized."<<std::endl;
		std::cout<<"Type 'help' for help."<<std::endl;
		std::cout<<std::endl;
		goto begin;
	}
}

/*==========================================================================
ABOVE IS FOR NOTES
============================================================================*/

std::vector<std::string> g_properties;

void OptionsGetProperties()
{
	std::vector<std::string> strings;
	std::ifstream props("data/properties.txt");
	if(props.is_open())
	{
		std::string strLine = "";
		while(std::getline(props, strLine))
		{
			g_properties.push_back(strLine);
		}
	}
	props.close();
}

void OptionsSaveProperties()
{
	std::ofstream props("data/properties.txt");
	props.clear();
	for(int i = 0; i < g_properties.size(); i++)
		props<<g_properties[i]<<"\n";
	props.close();
}

void OptionsDisplay()
{
	//display general stuff
	std::cout<<"Background Notes [Version 0.1.1]\n";
	std::cout<<"(c) 2015 Swift Studios. All rights reserved.\n\n";

	//display strings
	std::cout<<"Your current properties are..."<<std::endl;
	for(int i = 0; i < g_properties.size(); i++)
	{
		switch(i)
		{
		case 0:
			std::cout<<"Dimensions-x:............ ";
			break;
		case 1:
			std::cout<<"Dimensions-y:............ ";
			break;
		case 2:
			std::cout<<"Text position:........... ";
			break;
		case 3:
			std::cout<<"Background color (r,g,b): ";
			break;
		case 4:
			std::cout<<"Font color (r,g,b):...... ";
			break;
		default:
			std::cout<<"error??? ";
			break;
		}
		std::cout<<g_properties[i]<<std::endl;
	}

	std::cout<<std::endl;
}

void OptionsModify()
{
	std::cout<<"\nDimensions-x: ";
	std::string dimensionsx; std::cin>>dimensionsx;

	std::cout<<"\nDimensions-y: ";
	std::string dimensionsy; std::cin>>dimensionsy;

	std::cout<<"\nText position (left, center, right): ";
	std::string textPos; std::cin>>textPos;

	std::cout<<"\nBackground color (r,g,b): ";
	std::string backgroundColor; std::cin>>backgroundColor;

	std::cout<<"\nFont color (r,g,b): ";
	std::string fontColor; std::cin>>fontColor;

	g_properties[0] = dimensionsx;
	g_properties[1] = dimensionsy;
	g_properties[2] = textPos;
	g_properties[3] = backgroundColor;
	g_properties[4] = fontColor;
}

/*==========================================================================
ABOVE IS FOR OPTIONS
============================================================================*/

//GLOBALS
int g_dimensionsX, g_dimensionsY;
std::string g_position;
CvScalar g_backgroundColor = cvScalar(102, 87, 59);
CvScalar g_fontColor = cvScalar(255, 255, 255);
std::vector<std::string> g_strings;

void GetProperties() //get properties for dimensions, position of text, background color, etc.
{
	std::ifstream text("data/properties.txt");
	if(text.is_open())
	{
		std::string strLine = "";
		int pos = 0;
		while(std::getline(text, strLine))
		{
			if(pos == 0) //dimensions x
				g_dimensionsX = std::stoi(strLine);
			else if(pos == 1) //dimensions y
				g_dimensionsY = std::stoi(strLine);
			else if(pos == 2) //position (left, centered, right)
				g_position = strLine;
			else if(pos == 3) //background color
			{
				if(strLine == "default")
					g_backgroundColor = cvScalar(102, 87, 59);
				else
				{
					int r(59), g(87), b(102), rgbCounter(0);
					std::string str = strLine;
					for(int i = 0; i < strLine.size(); i++)
					{
						if(strLine[i] == ',' || i == strLine.size()-1)
						{
							int case2TempCounter(0);
							switch(rgbCounter)
							{
							case 0:
								str.erase(i, str.size());
	            
								r = std::stoi(str);
								str = strLine;
								rgbCounter++;
								break;
							case 1:
								str.erase(i, str.size());
								for(int j = str.size(); j > 0; j--)
									if(str[j] == ',')
										str.erase(0, j+1);
	            
								g = std::stoi(str);
								str = strLine;
								rgbCounter++;
								break;
							case 2:
								for(int j = 0; j < str.size(); j++)
								{
									if(str[j] == ',' && case2TempCounter == 1)
										str.erase(0, j+1);
									else if(str[j] == ',')
										case2TempCounter++;
								}

								b = std::stoi(str);
								str = strLine;
								rgbCounter++;
								break;
							default:
								break;
							}
						}
					}

					g_backgroundColor = cvScalar(b, g, r);
				}
			}
			else if(pos == 4) //font color
			{
				if(strLine == "default")
					g_fontColor = cvScalar(255, 255, 255);
				else
				{
					int r(255), g(255), b(255), rgbCounter(0);
					std::string str = strLine;
					for(int i = 0; i < strLine.size(); i++)
					{
						if(strLine[i] == ',' || i == strLine.size()-1)
						{
							int case2TempCounter(0);
							switch(rgbCounter)
							{
							case 0:
								str.erase(i, str.size());
	            
								r = std::stoi(str);
								str = strLine;
								rgbCounter++;
								break;
							case 1:
								str.erase(i, str.size());
								for(int j = str.size(); j > 0; j--)
									if(str[j] == ',')
										str.erase(0, j+1);
	            
								g = std::stoi(str);
								str = strLine;
								rgbCounter++;
								break;
							case 2:
								for(int j = 0; j < str.size(); j++)
								{
									if(str[j] == ',' && case2TempCounter == 1)
										str.erase(0, j+1);
									else if(str[j] == ',')
										case2TempCounter++;
								}

								b = std::stoi(str);
								str = strLine;
								rgbCounter++;
								break;
							default:
								break;
							}
						}
					}

					g_fontColor = cvScalar(b, g, r);
				}
			}

			pos++;
		}
	}
	text.close();
}

void GetStrings()
{
	std::ifstream text("data/notes.txt");
	if(text.is_open())
	{
		std::string strLine = "";
		while(std::getline(text, strLine))
		{
			g_strings.push_back(strLine);
		}
	}
	text.close();
}

void CreateImage()
{
	//create the background
	cv::Mat image(g_dimensionsY, g_dimensionsX, CV_8UC3, g_backgroundColor);

	//add the text
	for(int i = 0; i < g_strings.size(); i++)
	{
		//cv::putText(image, text, position(x, y), font, size(int), color(b, g, r);
		cv::putText(image, g_strings[i], cv::Point(0, 40+40*i), CV_FONT_HERSHEY_TRIPLEX, 1.f, g_fontColor);
	}

	//save the image
    cv::imwrite("output.jpg", image);
}

bool SetBackground()
{
	//Get .exe path
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(hModule, path, MAX_PATH);

    char ch[260];
    char DefChar = ' ';
    WideCharToMultiByte(CP_ACP,0,path,-1, ch,260,&DefChar, NULL);
    
    std::string ss(ch);
	for(int i = ss.size(); i > 0; i--)
	{
		if(ss[i] == '\\')
		{
			ss.erase(i+1, ss.size());
			break;
		}
	}

	std::string filePath;
	const std::string strLocalDirectory = ss; //"C:\\Users\\Nick\\Documents\\1. Nick Stuff\\Programming\\(X) Projects 3\\BackgroundNotes\\Release\\"; // TWEAKED PATH

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

int main()
{
	//BackgroundNotes.exe
	//Display intro
	/*std::cout<<"Background Notes [Version 0.1.1]"<<std::endl;
	std::cout<<"(c) 2015 Swift Studios. All rights reserved.\n"<<std::endl;

	//Load current strings
	std::vector<std::string> strings = NotesLoadData();

	//while loop
	bool exit = false;
	while(1)
	{
		NotesGeneralDisplay(strings);
		NotesParseInput(strings, exit);
		if(exit)
			break;
	}*/

	//background.exe
	GetProperties();
	GetStrings();
	CreateImage();
	SetBackground();

	//options.exe
	/*OptionsGetProperties();
	OptionsDisplay();
	OptionsModify();
	OptionsSaveProperties();
	system("background.exe");*/

	return 0;
}

