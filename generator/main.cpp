#include <iostream>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>
#include <string>
#include <vector>

std::string FILENAME = "words.txt";

int dim, gridsize, players;
int wordsTotal;

std::vector<std::string> wordList, wordPool;

std::string generate()
{
	int rn = (rand() % wordPool.size());
	std::string res = wordPool[rn];

	wordPool.erase(wordPool.begin() + rn);
	
	return res;
}

void reset()
{
	wordPool = wordList;
}


//arg 1 dimensions
//arg 2 how many

int main (int argc, char** args)
{
	//Reading in word list
	
	
	if(argc != 3)
	{
		std::cerr << "usage: brot-generator [dim] [numplayers]" << std::endl;
		return -1;
	}
	
	dim = std::stoi(args[1]);
	players = std::stoi(args[2]);
	gridsize = dim*dim;
	if(dim < 1)
	{
		std::cerr << "dimensions only > 0 " << std::endl;
		return -1;
	}
	

	std::ifstream file(FILENAME);
	
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			std::string lineS = line.c_str();
			if(lineS.compare("") != 0)
		   		wordList.push_back(line.c_str());
		}
		file.close();
	}
	else
	{
		std::cerr << "word file not found: " << FILENAME << std::endl;
	}
	wordsTotal = wordList.size();
	
	if(wordsTotal < gridsize)
	{
		std::cerr << "it needs " << dim*dim << " words to genrate the bingo card, only " << wordsTotal << " available" << std::endl;
		return -1;
	}
	

  /* initialize random seed: */
  srand (time(NULL));

  for(int i = 0; i < players; i++)
  {
  	std::cout << "Spieler " << (i+1) << std::endl;
  	reset();
  	for(int j = 0; j < gridsize; j++)
  	{
  		std::string entry = generate();
  		std::cout << (j < 9 ? " " : "") << (j+1) << ": " << entry << std::endl;
  	}
  	std::cout << std::endl;
  }
  std::cout << ":|" << std::endl;
  return 0;
}
