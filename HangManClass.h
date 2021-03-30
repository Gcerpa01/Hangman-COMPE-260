#ifndef _HANG_MAN_CLASS
#define _HANG_MAN_CLASS

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib> 

/*This header file defines the class Tic Tac Toe as well as all elements of the
object that are to be defined in a seperate cpp file*/
using namespace std;

class game
{
private:
     int attempts = 0;
     int wordLength = 0;
     int select;
     string secretWord;
     string blanks;
     std::vector < std::string> wordList;

public:
     void Hangman();
     void playGame();
     void enterNewWords(); //CHECK
     void readFromFile();     //CHECK
     void setSecretWord(string correct);//CHECK
     void setWordLength(int length); //CHECK
     void displayMenu();
     void convertToUpper();
     void topBorder();
     void wordBorder();
     void gameBorder(string word);
     void endBorder(int attempt);
     bool isWin(string guess, string correct);
     int getWordLength(); //CHECK
     bool letters(string words);

     string getSecretWord();

};
#endif