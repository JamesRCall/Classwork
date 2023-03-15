// Programmer: James Callender
// Section: 102
// Date: 3/14/2023
// Assignment: HW6-PrintQuestion
// Purpose: prints each question using the structures defined in the header

#include "Game_Header.h"

void printQuestion(int questionNumber){
  // calls the strings of each variable and prints them out.
  cout << q[questionNumber].prompt << endl;
  cout << q[questionNumber].opt1 << endl;
  cout << q[questionNumber].opt2 << endl;
  cout << q[questionNumber].opt3 << endl;
  cout << q[questionNumber].opt4 << endl << endl;

}