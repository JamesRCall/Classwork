// Programmer: James Callender
// Section: 102
// Date: 4/4/2023
// Assignment: Mr.Whiskey Game
// file: addGame.cpp
// Purpose: function to add games to array of video games

#include "WGames.h"

void addGame(VideoGame games[], int Game_Size){
  // default values for static variables
  static int indexLocation = 0; // checks location
  static int uniqueTracker = 0; // checks if title already used
  // check if all array locations have been used 
  if(indexLocation > 99){
    cout << "Error 100: Collection is full, no more games can be added, returning to main menu..." << endl << endl;
    // if full return
    return;
  }
  // clear cin for inputs
  cin.ignore();
  cout << "Enter the game title: ";
  getline(cin, games[indexLocation].gameTitle); // assigns title
  // loops through array to ensure title hasnt been used
  for(int i = 0; i < Game_Size; i++){
    if(games[i].gameTitle.compare(games[indexLocation].gameTitle) == 0){
      // adds when title is found
      uniqueTracker++;
    }
    // checks if more than one game in array has title
    if(uniqueTracker > 1){
      // if more than one game has title quit and return
      cout << "Error 101: Game already exist, returning to main menu..." << endl << endl;
      // resets tracker
      uniqueTracker = 0;
      return;
    }
  }
  // also resets tracker
  uniqueTracker = 0;
  // gets rest of inputs
  cout << "Enter the genre: ";
  getline(cin, games[indexLocation].genre);
  cout << "Enter the platform: ";
  getline(cin, games[indexLocation].platform);
  cout << "Enter the release year: ";
  cin >> games[indexLocation].releaseYear;
  cin.ignore();
  cout << "Enter the developer name: ";
  getline(cin, games[indexLocation].dev.devName);
  cout << "Enter the developer's country: ";
  getline(cin, games[indexLocation].dev.devCountry);
  // changes index location to next spot
  indexLocation++;
  // assigns game id
  games[(indexLocation-1)].gameID = indexLocation;
  // outputs success message
  cout << "Game added successfully! Game ID: " << indexLocation << endl << endl;
  return;
}
