// BackgroundNotes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

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
	std::cout<<"-help         Get a list of possible commands to use"<<std::endl;
	std::cout<<"-add          Add a new note"<<std::endl;
	std::cout<<"-delete       Delete a note"<<std::endl;
	std::cout<<"-modify       Modify a note"<<std::endl;
	std::cout<<"-save         Save"<<std::endl;
	std::cout<<"-exit         Safely exit"<<std::endl;

	std::cout<<std::endl;
}

void Add()
{
	//go to add prompt and stuff
}

void Delete(int i)
{
	//delete stuff
}

void Modify(int i)
{
	//modify stuff
}

void Clear()
{
}

void Save()
{
}

void Exit()
{
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

void ParseInput()
{
	begin:
	//get input
	std::string str;
	std::cout<<">";
	std::cin>>str;

	if(str == "-help")
		Help();
	else if(str == "-add")
		Add();
	else if(str == "-delete")
		Add();
	else if(str == "-modify")
		Add();
	else if(str == "-clear")
		Add();
	else if(str == "-save")
		Add();
	else if(str == "-exit")
		Exit();
	else
	{
		std::cout<<"Nope. Try again, type -help for help.\n"<<std::endl;
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
	/*std::vector<std::string> strings = LoadData(); //Load current strings

	sf::RenderWindow window; window.create(sf::VideoMode(200, 400), "BackgroundNotes");
	bool controlBool(false);
	while(window.isOpen())
	{
		sf::Event Event;
		while(window.pollEvent(Event))
		{
			switch(Event.type)
			{
			case sf::Event::KeyPressed:
				//control bool
				if(Event.key.code == sf::Keyboard::Key::LControl)
					controlBool = true;
				if(Event.key.code == sf::Keyboard::Key::RControl)
					controlBool = true;

				//saving
				if(Event.key.code == sf::Keyboard::Key::S && controlBool == true)
				{
					SaveData(strings);
					CreateImage(strings);
					SetBackground("data/background.jpg");
				}

				//copying
				if(Event.key.code == sf::Keyboard::Key::C && controlBool == true)
				{
					//copying stuff
				}
				break;

			case sf::Event::KeyReleased:
				//control bool
				if(Event.key.code == sf::Keyboard::Key::LControl)
					controlBool = false;
				if(Event.key.code == sf::Keyboard::Key::RControl)
					controlBool = false;
				break;

			case sf::Event::MouseButtonPressed:
				break;

			case sf::Event::MouseButtonReleased:
				break;

			case sf::Event::Resized:
				break;

			case sf::Event::Closed:
				window.close();
				break;
			}
		}
	}
	//create a window and in for loop. Under keys, if pressed ctr + s: CreateImage() and SetBackground() and SaveData().
	//in normal window thing make it a simple .txt document lookalike with specific -commands

	//Create image based on strings

	//Exiting!
	SaveData(strings);
	SetBackground();*/

	//Display intro
	std::cout<<"Background Notes [Version 0.0.0.1]"<<std::endl;
	std::cout<<"(c) 2015 Swift Studios. All rights reserved.\n"<<std::endl;

	//Load current strings
	std::vector<std::string> strings = LoadData();

	//while loop
	while(1)
	{
		GeneralDisplay(strings);
		ParseInput();
	}

	SaveData(strings);

	return 0;
}

