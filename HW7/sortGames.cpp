// Programmer: James Callender
// Section: 102
// Date: 4/4/2023
// Assignment: Mr.Whiskey Game
// file: sortGames.cpp
// Purpose: uses simple bubble sort to reorganize array based on variables

#include "WGames.h"

void sortGames(VideoGame games[], int Game_Size){
  // outputs options
  cout << "Sort by: " << endl;
  cout << "1. Game ID " << endl;
  cout << "2. Game Title " << endl << endl;
  cout << "Enter your choice: ";
  // sets default value for error handlind
  int sortChoice = 0;
  // assigns option
  cin >> sortChoice;
  // checks for invalid option
  if(sortChoice < 1 || sortChoice > 2){
    cout << "Error 107: Invalid choice. Try again: " << endl << endl;
    // recalls function if invalid
    sortGames(games, Game_Size);
  }
  // checks if option 2 chosen
  if(sortChoice == 2){
    // simple bubble sort 
    for(int i = 0; i < Game_Size-1; i++) {
      for(int j = 0; j < Game_Size-i-1; j++) {
        // checks if previous game is greater than former
        if(games[j].gameTitle > games[j+1].gameTitle) {
          // creates a temp struture to store structure
          VideoGame temp = games[j];
          // replaces structure
          games[j] = games[j+1];
          // places temp structure into last structure
          games[j+1] = temp;
        }
      }
    }
  }
  // checks if option 1 was chosen
  else if(sortChoice == 1){
    // simple bubble sort same as above except with gameID enstead
    for(int i = 0; i < Game_Size-1; i++) {
      for(int j = 0; j < Game_Size-i-1; j++) {
        if(games[j].gameID > games[j+1].gameID) {
          VideoGame temp = games[j];
          games[j] = games[j+1];
          games[j+1] = temp;
        }
      }
    }
  }
  else{
    // error handling
    cout << "Error 108: Improper sort choice, returning to main menu..." << endl << endl;
  }
  return;
}