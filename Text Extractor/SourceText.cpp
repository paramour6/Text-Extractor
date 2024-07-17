#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include "SourceText.h"

SourceText::SourceText(std::string FILENAME)
{
	this->FILENAME = FILENAME;
	in_file.open(FILENAME);
	nWordDumps = nNumDumps = nCharDumps = 0;

	populateCharacterMap();
	populateWordMap();
	populateNumberMap();
}

SourceText::SourceText()
{
	nWordDumps = nNumDumps = nCharDumps = 0;
	FILENAME = "";
}

SourceText::~SourceText()
{
	if (in_file.is_open())
		in_file.close();
}

void SourceText::populateWordMap()
{
	if (in_file.is_open())
	{
		std::string w;

		while (in_file >> w)
		{
			if (!isNumber(w))
			{
				mWordFrequencies[w]++;
			}
		}
	}
	else
		std::cout << "Error opening source file...\n";

	in_file.clear();
	in_file.seekg(0);
}

void SourceText::populateNumberMap()
{
	if (in_file.is_open())
	{
		std::string w;

		while (in_file >> w)
		{
			if (isNumber(w))
			{
				mNumberFrequencies[std::stoi(w)]++;
			}
		}
	}
	else
		std::cout << "Error opening source file...\n";

	in_file.clear();
	in_file.seekg(0);
}

void SourceText::populateCharacterMap()
{
	if (in_file.is_open())
	{
		char c;

		while (in_file >> c)
		{
			mCharacterFrequencies[c]++;
		}
	}
	else
		std::cout << "Error opening source file...\n";

	in_file.clear();
	in_file.seekg(0);
}

bool SourceText::setFilename(std::string filename)
{
	this->FILENAME = filename;
	in_file.open(FILENAME);
	if (in_file.is_open())
	{
		populateWordMap();
		populateNumberMap();
		populateCharacterMap();
		return true;
	}
	else return false;
}

inline std::unordered_map<std::string, int> SourceText::getWordMap() const
{
	return mWordFrequencies;
}

inline std::unordered_map<int, int> SourceText::getNumMap() const
{
	return mNumberFrequencies;
}

inline std::unordered_map<char, int> SourceText::getCharMap() const
{
	return mCharacterFrequencies;
}

bool SourceText::findWord(const char* word)
{
	return mWordFrequencies.find(word) != mWordFrequencies.end();
}

int SourceText::countWord(const char* word)
{
	return (mWordFrequencies.find(word) != mWordFrequencies.end() ? mWordFrequencies.at(word) : 0);
}

bool SourceText::findNumber(int number)
{
	return mNumberFrequencies.find(number) != mNumberFrequencies.end();
}

int SourceText::countNumber(int number)
{
	return (mNumberFrequencies.find(number) != mNumberFrequencies.end() ? mNumberFrequencies.at(number) : 0);
}

bool SourceText::findCharacter(char character)
{
	return mCharacterFrequencies.find(character) != mCharacterFrequencies.end();
}

int SourceText::countCharacter(char character)
{
	return (mCharacterFrequencies.find(character) != mCharacterFrequencies.end() ? mCharacterFrequencies.at(character) : 0);
}

bool SourceText::isNumber(std::string word)
{
	int i = 0;
	while (i != word.size() && isdigit(word[i])) i++;

	return i == word.size();
}

void SourceText::wordcrc(const char* filename)
{
	SourceText file(filename);
	std::unordered_map<std::string, int> fWordMap = file.getWordMap();

	std::ofstream out_file(this->FILENAME + (std::string)"_wordcrc_" + filename + ".txt");

	out_file << "Word Cross Comparison: " << this->FILENAME << ", " << filename << "\n";
	for (auto i = mWordFrequencies.begin(); i != mWordFrequencies.end(); i++)
	{
		if (fWordMap.find(i->first) != fWordMap.end())
		{
			out_file << i->first << ": " << i->second << ", " << fWordMap.at(i->first) << " instances\n";
		}
		else out_file << i->first << ": " << i->second << ", 0 instances\n";
	}
	for (auto i = fWordMap.begin(); i != fWordMap.end(); i++)
	{
		if (mWordFrequencies.find(i->first) == mWordFrequencies.end())
		{
			out_file << i->first << ": 0, " << i->second << " instances\n";
		}
	}
	out_file.close();
}

void SourceText::numcrc(const char* filename)
{
	SourceText file(filename);
	std::unordered_map<int, int> fNumMap = file.getNumMap();
	std::ofstream out_file(this->FILENAME + (std::string)"_numcrc_" + filename + ".txt");

	out_file << "Number Cross Comparison: " << this->FILENAME << ", " << filename << "\n";
	for (auto i = mNumberFrequencies.begin(); i != mNumberFrequencies.end(); i++)
	{
		if (fNumMap.find(i->first) != fNumMap.end())
		{
			out_file << i->first << ": " << i->second << ", " << fNumMap.at(i->first) << " instances\n";
		}
		else out_file << i->first << ": " << i->second << ", 0 instances\n";
	}
	for (auto i = fNumMap.begin(); i != fNumMap.end(); i++)
	{
		if (mNumberFrequencies.find(i->first) == mNumberFrequencies.end())
		{
			out_file << i->first << ": 0, " << i->second << " instances\n";
		}
	}
	out_file.close();
}

void SourceText::charcrc(const char* filename)
{
	SourceText file(filename);
	std::unordered_map<char, int> fCharMap = file.getCharMap();
	std::ofstream out_file(this->FILENAME + (std::string)"_charcrc_" + filename + ".txt");

	out_file << "Character Cross Comparison: " << this->FILENAME << ", " << filename << "\n";
	for (auto i = mCharacterFrequencies.begin(); i != mCharacterFrequencies.end(); i++)
	{
		if (fCharMap.find(i->first) != fCharMap.end())
		{
			out_file << i->first << ": " << i->second << ", " << fCharMap.at(i->first) << " instances\n";
		}
		else out_file << i->first << ": " << i->second << ", 0 instances\n";
	}
	for (auto i = fCharMap.begin(); i != fCharMap.end(); i++)
	{
		if (mCharacterFrequencies.find(i->first) == mCharacterFrequencies.end())
		{
			out_file << i->first << ": 0, " << i->second << " instances\n";
		}
	}
	out_file.close();
}

void SourceText::dumpWordFrequencies()
{
	std::ofstream out_file(FILENAME + (std::string)"_worddump_" + std::to_string(nWordDumps) + ".txt");
	if (out_file.is_open())
	{
		for (auto i = mWordFrequencies.begin(); i != mWordFrequencies.end(); i++)
		{
			out_file << i->first << ": " << i->second << " instances\n";
		}
	}
	else
		std::cout << "Unable to write to dump file!\n";

	out_file.close();
}

void SourceText::dumpNumberFrequencies()
{
	std::ofstream out_file(FILENAME + (std::string)"_numberdump_" + std::to_string(nNumDumps) + ".txt");
	if (out_file.is_open())
	{
		for (auto i = mNumberFrequencies.begin(); i != mNumberFrequencies.end(); i++)
		{
			out_file << i->first << ": " << i->second << " instances\n";
		}
	}
	else
		std::cout << "Unable to write to dump file!\n";

	out_file.close();
}

void SourceText::dumpCharacterFrequencies()
{
	std::ofstream out_file(FILENAME + (std::string)"_chardump_" + std::to_string(nCharDumps) + ".txt");
	if (out_file.is_open())
	{
		for (auto i = mCharacterFrequencies.begin(); i != mCharacterFrequencies.end(); i++)
		{
			out_file << i->first << ": " << i->second << " instances\n";
		}
	}
	else
		std::cout << "Unable to write to dump file!\n";

	out_file.close();
}