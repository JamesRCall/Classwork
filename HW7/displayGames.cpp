// Programmer: James Callender
// Section: 102
// Date: 4/4/2023
// Assignment: Mr.Whiskey Game
// file: displayGames.cpp
// Purpose: displays all valid games in array in order

#include "WGames.h"

void displayGames(VideoGame games[], int Game_Size){
  static int gameNumber = 1; // counts game number
  static bool hasGame = false; // checks if there are any games
  cout << "Displaying Games: " << endl << endl;
  // loops through array to check for and print out all games
  for(int i = 0; i < Game_Size; i++){
    if(games[i].gameID > 0){
      cout << gameNumber << ". " << endl;
      cout << " Game ID: " << games[i].gameID << endl;
      cout << " Title: " << games[i].gameTitle << endl;
      cout << " Genre: " << games[i].genre << endl;
      cout << " Platform: " << games[i].platform << endl;
      cout << " Release Year: " << games[i].releaseYear << endl;
      cout << " Developer: " << games[i].dev.devName << " (" << games[i].dev.devCountry << ")" << endl << endl;
      gameNumber++; // counts amount of games
      hasGame = true; // sets has game to true
    }
  }
  gameNumber = 1;
  if(hasGame == false){ // if no games say so
    cout << "Error 106: No games found, returning to main menu..." << endl << endl;
  }
  return;
}
