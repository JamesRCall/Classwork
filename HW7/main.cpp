// Programmer: James Callender
// Section: 102
// Date: 4/4/2023
// Assignment: Mr.Whiskey Game
// file: main.cpp
// Purpose: main file for video game collection app

#include "WGames.h"

int main(){
  // assign the constant variable array size
  const int Game_Size = 100;
  // creates array of 100 "VideoGame" structures
  VideoGame games[100];
  // sets default player option value
  int playerOption = 0;
  cout << "Welcome to Mr. Whiskers' Video Game Collection Management System!" << endl << endl;
  // loop through menu options until exit is called
  do{
    gameOption(games, Game_Size, playerOption);
  }while(playerOption != 5);
  // farewell message
  cout << "Thank you for using Mr. Whiskers' Video Game Collection Management System! Goodbye!" << endl;
  return 0; 
}