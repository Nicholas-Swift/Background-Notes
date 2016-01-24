// Background Notes.cpp
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

#include <time.h>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

std::vector<std::string> GetStrings(std::string str)
{
	std::vector<std::string> strings;
	std::ifstream text(str);
	if(text.is_open())
	{
		std::string strLine = "";
		while(std::getline(text, strLine))
		{
			strings.push_back(strLine);
		}
	}
	text.close();
	return strings;
}

void ParseStrings()
{
	std::vector<std::string> properties = GetStrings("data/properties.txt");
	std::vector<std::string> notes = GetStrings("data/notes.txt");
	
	int type(std::stoi(properties[0])); //type: solid color, image, or slideshow

	sf::Vector2i dimensions(1366, 768);
	std::string fileName = "default";
	if(type == 0)
		dimensions = sf::Vector2i(std::stoi(properties[1]), std::stoi(properties[2])); //height and dimensions
	else if(type == 1)
		fileName = properties[1]; //filename

	sf::Color backgroundColor(sf::Color(std::stoi(properties[3]), std::stoi(properties[4]), std::stoi(properties[5]), 255)); //load background color

	sf::Font font; font.loadFromFile(properties[6]); //load font
	int fontSize = std::stoi(properties[7]); //font size
	sf::Color fontColor(sf::Color(std::stoi(properties[8]), std::stoi(properties[9]), std::stoi(properties[10]), 255)); //load font color
	std::string textPos = properties[11]; //font position (left, right, centered)
	int textOffset = std::stoi(properties[12]); //text offset
	int textSize = std::stoi(properties[13]); //text size (scale)
	//CreateImage(dimensions, backgroundColor, notes, font, fontColor, textPos, textOffset, textSize);

	switch(type)
	{
	case 0:
		//CreateImage(dimensions, backgroundColor, notes, font, fontColor, textPos, textOffset, textSize);
		break;
	case 1:
		//CreateImage(fileName, notes, font, fontColor, textPos, textOffset, textSize);
		break;
	default:
		//CreateImage(dimensions, backgroundColor, notes, font, fontColor, textPos, textOffset, textSize);
		break;
	}
}

void CreateImage(sf::Vector2i dimensions, sf::Color backgroundColor, std::vector<std::string> notes,
				 sf::Font font, sf::Color textColor, std::string textPos, int textOffset,
				 int textSize) //general background image blank color
{
	//create the background
	sf::RenderTexture texture;
	texture.create(dimensions.x, dimensions.y);
	texture.clear(backgroundColor);

	//add the notes
	for(int i = 0; i < notes.size(); i++)
	{
		sf::Text text;
		text.setString(notes[i]);
		text.setFont(font);
		text.setColor(textColor);
		text.setScale(textSize, textSize);
		if(textPos == "left")
			text.setPosition(textOffset, text.getCharacterSize()*i + 5);
		else if(textPos == "center")
			text.setPosition(dimensions.x/2 - text.getGlobalBounds().width/2, text.getCharacterSize()*i + 5);
		else if(textPos == "right")
			text.setPosition(dimensions.x - text.getGlobalBounds().width - textOffset, text.getCharacterSize()*i + 5);
		else
			text.setPosition(0, text.getCharacterSize()*i + 5);

		texture.draw(text);
	}

	//save the image
	sf::Image img = texture.getTexture().copyToImage();
	img.flipVertically();
	img.saveToFile("image.png");
}

void CreateImage(std::string fileName, std::vector<std::string> notes,
				 sf::Font font, sf::Color textColor, std::string textPos, int textOffset,
				 int textSize) //background image with actual picture
{
	sf::Image img;
	img.loadFromFile(fileName);

	//create the background
	sf::RenderTexture texture;
	texture.create(img.getSize().x, img.getSize().y);
	texture.clear(sf::Color(0, 0, 0, 0));

	//add the notes
	for(int i = 0; i < notes.size(); i++)
	{
		sf::Text text;
		text.setString(notes[i]);
		text.setFont(font);
		text.setColor(textColor);
		text.setScale(textSize, textSize);
		if(textPos == "left")
			text.setPosition(textOffset, text.getCharacterSize()*i + 5);
		else if(textPos == "center")
			text.setPosition(img.getSize().x/2 - text.getGlobalBounds().width/2, text.getCharacterSize()*i + 5);
		else if(textPos == "right")
			text.setPosition(img.getSize().x - text.getGlobalBounds().width - textOffset, text.getCharacterSize()*i + 5);
		else
			text.setPosition(0, text.getCharacterSize()*i + 5);

		texture.draw(text);
	}

	//save the image
	sf::Image textImage = texture.getTexture().copyToImage();
	textImage.flipVertically();

	for(int i = 0; i < img.getSize().x; i++)
	{
		for(int j = 0; j < img.getSize().y; j++)
		{
			if(textImage.getPixel(i, j) != sf::Color(0, 0, 0, 0))
				img.setPixel(i, j, textImage.getPixel(i, j));
		}
	}


	img.saveToFile("output.jpg");
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
	const std::string strLocalDirectory = ss;

	//Convert the index choice into a usable filename string.
	std::stringstream ssFilePath;
	//ssFilePath << strLocalDirectory << bgChoice << ".jpg";
	ssFilePath << strLocalDirectory << "data/output.jpg";
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
	//ParseStrings();
	//ALL STUFF ABOVE IS FOR PROPERTIES AND STUFF AND FUTURE USE --- BELOW IS BETTAAA STUFFFFF

	//get notes
	std::vector<std::string> notes = GetStrings("data/notes.txt");

	sf::Image img;
	img.loadFromFile("data/background.jpg");

	//create the background
	sf::RenderTexture texture;
	texture.create(img.getSize().x, img.getSize().y);
	texture.clear(sf::Color(0, 0, 0, 0));

	sf::Font font; font.loadFromFile("data/font.ttf");
	sf::Color textColor = sf::Color::White;
	float textSize = 1.f;
	float textOffset = 32.f;
	//add the notes
	for(int i = 0; i < notes.size(); i++)
	{
		sf::Text text;
		text.setString(notes[i]);
		text.setFont(font);
		text.setColor(textColor);
		text.setScale(textSize, textSize);
		text.setPosition(textOffset, text.getCharacterSize()*i + 5);

		texture.draw(text);
	}

	//save the image
	sf::Image textImage = texture.getTexture().copyToImage();
	textImage.flipVertically();

	for(int i = 0; i < img.getSize().x; i++)
	{
		for(int j = 0; j < img.getSize().y; j++)
		{
			if(textImage.getPixel(i, j) != sf::Color(0, 0, 0, 0))
				img.setPixel(i, j, textImage.getPixel(i, j));
		}
	}
	img.saveToFile("data/output.jpg");
	SetBackground();

	return 0;
}

