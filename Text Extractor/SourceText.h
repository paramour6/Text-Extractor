#include <fstream>
#include <unordered_map>

class SourceText
{
private:
	std::string FILENAME;
	std::ifstream in_file;
	std::unordered_map<std::string, int> mWordFrequencies;
	std::unordered_map<int, int> mNumberFrequencies;
	std::unordered_map<char, int> mCharacterFrequencies;
	int nWordDumps, nNumDumps, nCharDumps;

	void populateWordMap();
	void populateNumberMap();
	void populateCharacterMap();
	bool isNumber(std::string);

public:
	SourceText(std::string);
	SourceText();
	~SourceText();

	bool setFilename(std::string);
	std::unordered_map<std::string, int> getWordMap() const;
	std::unordered_map<int, int> getNumMap() const;
	std::unordered_map<char, int> getCharMap() const;

	bool findWord(const char*);
	bool findNumber(int);
	bool findCharacter(char);
	int countWord(const char*);
	int countNumber(int);
	int countCharacter(char);

	void wordcrc(const char*);
	void numcrc(const char*);
	void charcrc(const char*);
	void dumpWordFrequencies();
	void dumpNumberFrequencies();
	void dumpCharacterFrequencies();
};