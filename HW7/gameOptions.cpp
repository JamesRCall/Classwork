// Programmer: James Callender
// Section: 102
// Date: 4/4/2023
// Assignment: Mr.Whiskey Game
// file: gameOptions.cpp
// Purpose: menu function which calls other functions based on player input

#include "WGames.h"

void gameOption(VideoGame games[], int Game_Size, int& playerChoice){
  cout << "Please Choose an option: " << endl;
  cout << "  1. Add a game to the collection " << endl;
  cout << "  2. Display all games in the collection " << endl; 
  cout << "  3. Search for a game" << endl;
  cout << "  4. Sort the collection " << endl;
  cout << "  5. Exit " << endl << endl;
  cout << "Enter your choice: ";
  cin >> playerChoice; // assigns player choice
  cout << endl;
  if(playerChoice < 1 || playerChoice > 5){ // ensures player chooses a valid option
    cout << "Error 102: Invalid option. Try again: " << endl << endl;
    playerChoice = 0;
    gameOption(games, Game_Size, playerChoice); // if invalid recall function
  }
  else{ // else call option
    switch(playerChoice){ // switch for each option
    // calls functions based on choice
      case 1:
        addGame(games, Game_Size);
        break;
      case 2:
        displayGames(games, Game_Size);
        break;
      case 3: 
        searchGames(games, Game_Size);
        break;
      case 4:
        sortGames(games, Game_Size);
        break;
      case 5:
      // break as exit is called
        break;
      default:
      // for error handling
        cout << "Error 105: invalid player choice, returning to main menu..." << endl << endl;
    }
  }
  return;
}