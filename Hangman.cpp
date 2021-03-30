// Hangman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
 **   Assignment:  Hangman Project Specification
 **
 **     Filename:  Hangman.cpp
 **
 **       Author:  Gerardo Cerpa
 **
 **  Lab Section:  CompE260
 **     Due Date:  10/04/2020 @ 11:59PM
 **
 **  Description: Hangman
 **
 **        Input: Integer to determine the user's selection from the menu. In addition it also accepts
                  strings as inputs(with letters only) when the user is in the playing mode or word bank 
                  mode.
 **
 **       Output: A menu displaying the different options for the player. Varying on their decision, the 
                  player then sees the respective screen for the mode they have chosen. The program also
                  displays the results of the game to the player

 **      Caveats: There is no visual representation of a hangman like in a traditional game as well as no
                  display of the letters the player has already chosen, meaning they can guess incorrectly
                  multiple times with the same letter.

 **      Version:  1.0
 **
          This program utilizes classes and instances in order to run a game of Hangman. An object called game is created
          and is then run via the classes being defined in a header file and instantiated in a seperate .cpp file
 */
#include "HangManClass.h"

int main()
{
     game Hangman;
     Hangman.Hangman();
}
