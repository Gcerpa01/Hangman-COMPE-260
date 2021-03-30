#include "HangManClass.h"
  


/*This boolean function takes a string and then verifies
all the elements of the string are alphabetic values*/

bool game::letters(string words) {
     for (int i = 0; i < words.length(); i++) {
          if (words[i] >= 'a' && words[i] <= 'z' || words[i] >= 'A' && words[i] <= 'Z') {
               return true;
          }
          else return false;
     }
}

/*This function asks the user for new words to add to the existing word bank. In addition once the user
has put in a word, it will ask them if they would like to continue adding additional words*/
void game::enterNewWords() {
     wordBorder();
     int opt = 1;
     while (opt == 1) {

          opt = 0;
          std::string input; //create a string variable for saving user input

          std::cout << "Please enter a new word for the word-bank:" << std::endl;
          std::ofstream file("words.txt", std::ios::app); //creates file and appends to already existing file
          std::cin >> input; //get user input


          while (letters(input) == false) {
               cout << "Please only input letters:\n";
               std::cin >> input;
          }

          file << "\n" << input; //store user's word into the file
          file.close();



          std::cout << "Would you like to add more words?" << std::endl;
          std::cout << "1. Yes     2. No" << std::endl;
          std::cin >> opt;


          while (!std::cin.good()) {           //while loop keeps asking for user input if user puts in character
               std::cin.clear();
               std::cin.ignore(INT_MAX, '\n');
               std::cout << "Would you like to add more words?" << std::endl;
               std::cout << "1. Yes     2. No" << std::endl;
               std::cin >> opt;
          }
          while (opt != 1 && opt != 2) {
               std::cin.clear();
               std::cin.ignore(INT_MAX, '\n');
               std::cout << "Please select between 1.Yes and 2.No" << std::endl;
               std::cin >> opt;
          }
     }

     std::cout << "\nWould you like to return to main menu or exit the program?" << std::endl;
     std::cout << "1.Main Menu    2.Exit" << std::endl;
     std::cin >> select;

     while (!std::cin.good()) {           //while loop keeps asking for user input if user puts in character
          std::cin.clear();
          std::cin.ignore(INT_MAX, '\n');
          std::cout << "\nWould you like to return to main menu or exit the program?" << std::endl;
          std::cout << "1.Main Menu    2.Exit" << std::endl;
          std::cin >> select;
     }

     while (select < 1 || select > 2) {    // while loop keeps asking for user input to make sure it follows program rules
          std::cin.clear();
          std::cin.ignore(INT_MAX, '\n');
          std::cout << "\nWould you like to return to main menu or exit the program?" << std::endl;
          std::cout << "1.Main Menu    2.Exit" << std::endl;
          std::cin >> select;
     }
     if (select == 1) {
          select = 0;
          Hangman();
     }
     else if (select == 2) {
          return;
     }

}

/*These border functions serve to display what mode the user is currently in*/
void game::topBorder() {
     std::cout << "+----------------------------------------------+\n";
     std::cout << "|                Hangman Menu                  |\n";
     std::cout << "+----------------------------------------------+\n";
}

void game::wordBorder() {
     std::cout << "+----------------------------------------------+\n";
     std::cout << "|                  Word Bank                   |\n";
     std::cout << "+----------------------------------------------+\n";
}

void game::gameBorder(string word) {
     std::cout << "+----------------------------------------------+\n";
     std::cout << "+             Guess the word below:            +\n";
     std::cout << "\n";
     std::cout << "                   "<<word<<"                   \n";
     std::cout << "+                                              +\n";
     std::cout << "+----------------------------------------------+\n";
}

void game::endBorder(int attempt) {
     if (attempt >= 9) {
          std::cout << "+----------------------------------------------+\n";
          std::cout << "|                   YOU LOSE                   |\n";
          std::cout << "+----------------------------------------------+\n";
     }
     else if (attempt < 9) {
          std::cout << "+----------------------------------------------+\n";
          std::cout << "|                   YOU WIN                    |\n";
          std::cout << "+----------------------------------------------+\n";
     }
}
/*Read from file opens the file "words.txt" if it does not already exist or in instead opens it.
It then stores all of the words in the file into a vector that is then shuffled randomly.The first
string in the  vector is then utilized as the word the user will be guessing*/
void game::readFromFile() {
     std::ifstream file("words.txt");
     std::string input;

     while (file >> input) { //read through file until nothing is left
          wordList.push_back(input);
     }

     file.close();
     std::srand(unsigned(time(0))); //random seed generator
     std::random_shuffle(wordList.begin(), wordList.end()); //shuffle items in vectors producing unique order each time

     setSecretWord(wordList[0]);
     setWordLength(wordList[0].size());

}

void game::setSecretWord(string correct) {
     secretWord = correct;
     convertToUpper();
}

string game::getSecretWord() {
     return secretWord;
}

void game::setWordLength(int length) {
     wordLength = length;
}

int game::getWordLength() {
     return wordLength;
}

/*This function displays the neccessary amount of dashes for the word the user will
be attempting to unlock. In addition, it will reiterate and check each element of the
string and compare it to only the first element of the user input. If there is a match than
the corresponding dash will change to the correct letter*/

void game::playGame() {
     /*This section of the code places the amount of dashes
      necessary for the amount of letters in the word the user will be guessing
      for*/

     string user;
     int attempts = 0;
     unsigned int guess = 0;

     /* This sectio  of the code copies the element in SecretWord to blanks and then
     replaces each element of the string with a dash*/
     blanks = getSecretWord();
     for (int i = 0; i < getWordLength(); i++) {
          blanks[i] = '-';
     }
     std::cout << "\n";
     gameBorder(blanks);


     /*The game will continue to ask the user for input until they have figured out
     what the secret word is. In addition, if the user guesses a letter correctly,
     the corresponding location in the string array will be replaced with that letter and
     nothing will be added to the count*/

     isWin(blanks, secretWord);
     while (isWin(blanks, secretWord) == false) {
          std::cout << "This word is " << wordLength << " letters long\n";
          std::cout << "Please guess a letter: ";
          std::cin >> user;

          while (letters(user) == false) {
               cout << "Please only input letters\n";
               std::cout << "Guess a letter: ";
               std::cin >> user;
          }

          user[0] = toupper(user[0]);

          attempts += 1;

          for (int i = 0; i < getWordLength(); i++) {
               if (user[0] == secretWord[i]) {
                    blanks[i] = user[0];
                    guess += 1;
               }
          }

          if (guess > 0) {
               attempts -= 1; //subtract from attempt if the user guessed  correcctly
               
          }
          guess = 0;
          std::cout << "\n";
          gameBorder(blanks);
          std::cout << "Incorrect attempts: "<<attempts << "\n";
          isWin(blanks, secretWord); //check for win condition
     }
     std::cout << "Congrats, you figured out the word!" << std::endl;
     std::cout << "You had: " << attempts << " incorrect attempt(s)" << std::endl;
     
     endBorder(attempts);

     std::cout << "\nWould you like to return to main menu or exit the program?" << std::endl;
     std::cout << "1.Main Menu    2.Exit" << std::endl;
     std::cin >> select;

     while (!std::cin.good()) {           //while loop keeps asking for user input if user puts in character
          std::cin.clear();
          std::cin.ignore(INT_MAX, '\n');
          std::cout << "\nWould you like to return to main menu or exit the program?" << std::endl;
          std::cout << "1.Main Menu    2.Exit" << std::endl;
          std::cin >> select;
     }

     while (select < 1 || select > 2) {    // while loop keeps asking for user input to make sure it follows program rules
          std::cin.clear();
          std::cin.ignore(INT_MAX, '\n');
          std::cout << "\nWould you like to return to main menu or exit the program?" << std::endl;
          std::cout << "1.Main Menu    2.Exit" << std::endl;
          std::cin >> select;
     }
     if (select == 1) {
          select = 0;
          Hangman();
     }
     else if (select == 2) {
          return;
     }
}

/*This boolean will continue to return false until the two string parameters
are exactly the same in value, including capitlization*/
bool game::isWin(string guess, string correct) {
     if (guess.compare(correct) == 0) {
          return true;
     }
     else return false;

}

/*Converts all the elements of the secretWord string into uppercase letters*/
void game::convertToUpper() {
     std::transform(secretWord.begin(), secretWord.end(), secretWord.begin(), ::toupper);
}

/*This function displays the menu to the user for them to choose from the available options*/
void game::displayMenu() {
     topBorder();
     std::cout << "\nWelcome to the classic game of hangman!" << std::endl;
     std::cout << "Get less than 9 incorrect guesses and you win!" << std::endl;
     std::cout << "Please choose from the following options:" << std::endl;
     std::cout << "1.PLAY" << std::endl;
     std::cout << "2.ENTER NEW WORDS" << std::endl;
     std::cout << "3.QUIT" << std::endl;
}


/*This class function runs the entirety of the game. It begins by calling the display menu function
and then taking user input. From the user's input the function then calls the function necessary
to do what the user has asked to play or do*/

void game::Hangman() {
     displayMenu();
     std::cin >> select;

     while (!std::cin.good()) {           //while loop keeps asking for user input if user puts in character
          std::cin.clear();
          std::cin.ignore(INT_MAX, '\n');
          std::cout << "\nPlease choose from the following options:" << std::endl;
          std::cout << "1.PLAY" << std::endl;
          std::cout << "2.ENTER NEW WORDS" << std::endl;
          std::cout << "3.QUIT" << std::endl;
          std::cin >> select;
     }

     while (select < 1 || select > 3) {
          std::cin.clear();
          std::cin.ignore(INT_MAX, '\n');
          std::cout << "\nPlease choose from the following options:" << std::endl;
          std::cout << "1.PLAY" << std::endl;
          std::cout << "2.ENTER NEW WORDS" << std::endl;
          std::cout << "3.QUIT" << std::endl;
          std::cin >> select;
     }

     /*This switch statment is essentialy the menu that the user picks from, calling the necessary
     functions to run the game or add new words*/
     switch (select) {
     case 1:
          readFromFile();
          playGame();
          break;
     case 2:
          std::cout << "\n";
          enterNewWords();
          break;
     case 3:
          return;
     default:
          return;

     }

}