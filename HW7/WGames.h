// Programmer: James Callender
// Section: 102
// Date: 4/4/2023
// Assignment: Mr.Whiskey Game
// file: WGames.h
// Purpose: header file to connect all source files of whiskey sort code

#ifndef WGAMES
#define WGAMES

#include <iostream>
#include <string>

using namespace std;

// developer structure
struct Developer{
    string devName = "Unknown"; // default to unknown
    string devCountry = "Unknown"; // default to unknown
};

struct VideoGame{
  int gameID = -1; // set to -1 for displayGames check
  // all defaults set to unknown or negative 1
  string gameTitle = "Unknown";
  string genre = "Unknown";
  string platform = "Unknown";
  int releaseYear = -1;
  Developer dev;
};
// allows games to be used outside of header file
extern VideoGame games[100];

// Desc: function is used for navigating through the 5 main menu options
// Pre: an array equal to Game_Size
// Post: takes in input for menu navigation, ensures valid input then calls functions based on option
void gameOption(VideoGame games[], int Game_Size, int& playerChoice);

// Desc: function is used to add games to array of videogames
// Pre: an array equal to Game_Size
// Post: checks to make sure there is space in array, then modifies variable of array in order,
//       counts array location after adding all variables and also checks to make sure title hasn't
//       been used yet.
void addGame(VideoGame games[], int Game_Size);

// Desc: function is used to display all games in array games[]
// Pre: an array equal to Game_Size
// Post: outputs all structures with gameIDs greater than 0, (structure that have been modified via addGame function)
void displayGames(VideoGame games[], int Game_Size);

// Desc: function is used to search through array for variables inside each structure
// Pre: an array equal to Game_size
// Post: outputs all structures in array with matching variable parameters
//       currently can check for 6 different types of parameters 
void searchGames(VideoGame games[], int Game_Size);

// Desc: function is used to display the structures found using searchGames function
// Pre: array pertaining an index location equal to i
// Post: outputs all variables of the structure with the matching variable
void displaySearchGame(VideoGame games[], int i);

// Desc: function uses a simple bubble sort to reorganize array based on structure parameter
// Pre: array equal to Game_size
// Post: sorts array either by "gameID" or "gameTitle" based on user input,
//       loops through array comparing consecutive structures then swapping locations based on values.
void sortGames(VideoGame games[], int Game_Size);

#endif