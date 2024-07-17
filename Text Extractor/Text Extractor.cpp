#include "SourceText.h"
#include <iostream>

std::string validFilename()
{
	std::string filepath{};
	bool validPath = false;
	do
	{
		std::cout << "Enter filename: ";
		std::cin >> filepath;
		if (filepath.size() <= 4)
		{
			std::cout << "Invalid filename!\n";
		}
		else
		{
			std::string comp{};
			for (int i = (int)(filepath.size() - 4); i < filepath.size(); i++)
			{
				comp += filepath[i];
			}
			if (comp != ".txt")
			{
				std::cout << "Invalid extension!\n";
			}
			else
			{
				validPath = true;
				return filepath;
			}
		}

	} while (!validPath);

	return "";
}

int main()
{
	std::cout << "Welcome to Text Extractor\n";
	SourceText src;
	while (!src.setFilename(validFilename()))
	{
		std::cout << "Invalid filename!\n";
	}

	int option = 0;
	do
	{
		std::cout << "1: Search word instances\n";
		std::cout << "2: Search number instances\n";
		std::cout << "3: Search character instances\n";
		std::cout << "4: Cross compare word instances\n";
		std::cout << "5: Cross compare number instances\n";
		std::cout << "6: Cross compare character instances\n";
		std::cout << "7: Dump all instances\n";
		std::cout << "8: Exit\n";
		std::cout << "Enter choice: ";
		std::cin >> option;
		system("CLS");

		switch (option)
		{
		case 1:
		{
			std::string word{};
			std::cout << "Enter word to search for: ";
			std::cin >> word;
			if (src.findWord(word.c_str()))
			{
				std::cout << word << " was found with " << src.countWord(word.c_str()) << " instances\n";
			}
			else std::cout << word << " was not found!\n";
			break;
		}
		case 2:
		{
			int number = 0;
			std::cout << "Enter number to search for: ";
			std::cin >> number;
			if (src.findNumber(number))
			{
				std::cout << number << " was found with " << src.countNumber(number) << " instances\n";
			}
			else std::cout << number << " was not found!\n";
			break;
		}
		case 3:
		{
			char character{};
			std::cout << "Enter character to search for: ";
			std::cin >> character;
			if (src.findCharacter(character))
			{
				std::cout << character << " was found with " << src.countCharacter(character) << " instances\n";
			}
			else std::cout << character << " was not found!\n";
			break;
		}
		case 4:
		{
			src.wordcrc(validFilename().c_str());
			std::cout << "Word cross comparison dumped\n";
			break;
		}
		case 5:
		{
			src.numcrc(validFilename().c_str());
			std::cout << "Number cross comparison dumped\n";
			break;
		}
		case 6:
		{
			src.charcrc(validFilename().c_str());
			std::cout << "Character cross comparison dumped\n";
			break;
		}
		case 7:
		{
			std::cout << "Dumping all instances...\n";
			src.dumpWordFrequencies();
			src.dumpNumberFrequencies();
			src.dumpCharacterFrequencies();
			std::cout << "Word, number, and character frequencies dumped\n";
			break;
		}
		case 8: break;
		default:
		{
			std::cout << "Invalid option...\n";
			break;
		}
		}
	} while (option != 8);

	return 0;
}