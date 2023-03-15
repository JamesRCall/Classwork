// Programmer: James Callender
// Section: 102
// Date: 3/14/2023
// Assignment: HW6
// Purpose: main file for gameshow program

#include <cstdlib>
#include "Game_Header.h"
/*----------------------------IMPORTANT---------------------------------
FUNCTION DEFINITIONS ARE IN THE HEADER FILE
(I am unsure if this is allowed but it seemed the most normal spot)
*/
int main(){
  // sets the seed to 11
  srand(11);
  // starting question value, yes it should probably be 1 
  // but I used an array which starts at 0
  int questionNumber = 0;
  // correct is used to check if they got the right answer
  // leave is used to check if player wants to leave.
  bool correct = 0, leave = 0;
  string playerChoice; // used to store players input
  greeting(); // calls greeting
  
  do{
    printQuestion(questionNumber); // prints current question
    getline(cin, playerChoice); // gets players input
    // assigns whether or not answer was correct to "correct" value
    // also does a lot of other things inside the PlayerInputFunctions.cpp file.
    correct = checkInput(questionNumber, playerChoice, leave);
    // if leave value was changed to true during check input then break off
    if(leave == true) break;
    // calls updateMoney function and gives value to player.winnings
    player.winnings = updateMoney(player.winnings, correct);
    // if player got it right tell them so
    if(correct==true){
      cout << "Correct!" << endl;
    }
    // if player got it wrong say so
    else{
      player.incorrectAnswers++; // adds to incorrect answers
      cout << "Incorrect! your have " << (3-player.incorrectAnswers) << " lives remaining." << endl;
    }
    // if player doesn't have 3+ incorrect answers then output winnings
    // the if statement is so the player doesn't see something like
    // "Current winngs: $12300!" and get really excited only to find out that it was a lie
    if(player.incorrectAnswers < 3){
      cout << "Current winnings: $" << player.winnings << endl << endl;
    }
    questionNumber++; // counts question number
  // while question number hasn't reached max questions and player has less than 3 wrong answers, continue.
  }while(questionNumber < MAX_QUESTIONS && player.incorrectAnswers < 3);
  // outputs the exit message
  exitMessage(leave);
  return 0; // return 0...
}
