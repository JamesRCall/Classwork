// Programmer: James Callender
// Section: 102
// Date: 4/4/2023
// Assignment: Mr.Whiskey Game
// file: searchGame.cpp
// Purpose: searches through array of structures for matching variables then outputs them

#include "WGames.h"

void displaySearchGame(VideoGame games[], int i){
  // outputs games
  cout << " Game ID: " << games[i].gameID << endl;
  cout << " Title: " << games[i].gameTitle << endl;
  cout << " Genre: " << games[i].genre << endl;
  cout << " Platform: " << games[i].platform << endl;
  cout << " Release Year: " << games[i].releaseYear << endl;
  cout << " Developer: " << games[i].dev.devName << " (" << games[i].dev.devCountry << ")" << endl << endl;
  return;
}
void searchGames(VideoGame games[], int Game_Size){
  // setting default values for searches for error handlind
  int searchChoice = 0;
  string searchValue = "";
  int searchNumber = 0;
  bool foundGame = false;
  cout << "Search by: " << endl;
  cout << "  1. Game ID " << endl;
  cout << "  2. Game Title" << endl;
  cout << "  3. Genre " << endl;
  cout << "  4. Platform" << endl;
  cout << "  5. Release Year" << endl;
  cout << "  6. Developer Name" << endl << endl;
  cout << "Enter your choice: ";
  cin >> searchChoice; // assigns choice
  cout << endl << endl;
  // ensures choice is valid, if not recall function
  if(searchChoice < 1 || searchChoice > 6){
    cout << "Error 103: Invalid choice. Try again: " << endl << endl;
    searchGames(games, Game_Size);
  }
  // once valid preforms switch case based on option
  else{
    switch(searchChoice){
      // assigns value for either searchValue or searchNumber based on option
      case 1:
        cout << "Enter the game ID: ";
        cin >> searchNumber;
        cout << "searching for games with the ID \"" << searchNumber << "\"..." << endl << endl;
        break;
      case 2:
        cout << "Enter the game title: ";
        // ignores for previous cin commands
        cin.ignore();
        getline(cin, searchValue);
        cout << "searching for games with the title \"" << searchValue << "\"..." << endl << endl;
        break;
      case 3:
        cout << "Enter the genre: ";
        cin.ignore();
        getline(cin, searchValue);
        cout << "searching for games with the genre \"" << searchValue << "\"..." << endl << endl;
        break;
      case 4:
        cout << "Enter the platform: ";
        cin.ignore();
        getline(cin, searchValue);
        cout << "searching for games with the platform \"" << searchValue << "\"..." << endl << endl;
        break;
      case 5:
        cout << "Enter the release year: ";
        cin >> searchNumber;
        cout << "searching for games with the release year \"" << searchValue << "\"..." << endl << endl;
        break;
      case 6:
        cout << "Enter the developer name: ";
        cin.ignore();
        getline(cin, searchValue);
        cout << "searching for games with the developer name \"" << searchValue << "\"..." << endl << endl;
        break;
      default:
        // error handlind
        cout << "Error 104: improper search choice, returning to main menu..." << endl << endl;
        return;
    }
    // loops through the array to find all valid games
    for(int i = 0; i < Game_Size; i++){
      // switch case for what to search for based on searchChoice value
      switch(searchChoice){
        // loops using either searchNumber or searchValue to respective variable in structure
        case 1:
          if(searchNumber == games[i].gameID){
            // if first game found output found game message
            if(foundGame == false){
              cout << "found a game(s): " << endl;
              foundGame = true;
            }
            // calls output function
            displaySearchGame(games, i);
          }
          break;
        case 2:
          if(searchValue == games[i].gameTitle){
            if(foundGame == false){
              cout << "found a game(s): " << endl;
              foundGame = true;
            }
            displaySearchGame(games, i);
          }
          break;
        case 3:
          if(searchValue == games[i].genre){
            if(foundGame == false){
              cout << "found a game(s): " << endl;
              foundGame = true;
            }
            displaySearchGame(games, i);
          }
          break;
        case 4:
          if(searchValue == games[i].platform){
            if(foundGame == false){
              cout << "found a game(s): " << endl;
              foundGame = true;
            }
            displaySearchGame(games, i);
          }
          break;
        case 5:
          if(searchNumber == games[i].releaseYear){
            if(foundGame == false){
              cout << "found a game(s): " << endl;
              foundGame = true;
            }
            displaySearchGame(games, i);
          }
          break;
        case 6:
          if(searchValue == games[i].dev.devName){
            if(foundGame == false){
              cout << "found a game(s): " << endl;
              foundGame = true;
            }
            displaySearchGame(games, i);
          }
          break;
      }
    }
  }
  // resets found game status
  foundGame = false;
  return;
}