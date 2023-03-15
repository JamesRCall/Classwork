// Programmer: James Callender
// Section: 102
// Date: 3/14/2023
// Assignment: HW6-main
// Purpose: holds the greeting and exit function of the gameshow program, calls all other functions

#include "Game_Header.h"

void greeting(){
    cout << "Welcome to Are you Smarter than a Comp Sci! Ready to play?" << endl << endl;
}
void exitMessage(bool shouldLeave){
  // if the player left use left output
  if(shouldLeave == true){
    cout << "Thanks for playing! " << endl;
    cout << "You walked out with $" << player.winnings << "." << endl;
    cout << "Lifelines remaining: " << player.lifelineRemaining << endl;
    cout << "Incorrect answers: " << player.incorrectAnswers << endl;
  }
  // if the player had too many incorrect answer us loser output
  else if(player.incorrectAnswers >= 3){
    cout << "Better luck next time! " << endl;
    cout << "You lost, and walked away with $0. " << endl;
    cout << "Lifelines remaining: " << player.lifelineRemaining << endl;
    cout << "Incorrect answers: " << player.incorrectAnswers << endl;
  }
  // else output winning output, (yes I could make this an else if statement enstead
  // and then I could create a last else statement for error handling but it's really late
  // please don't mark me off for that... ._.)
  else{
    cout << "Congratulations! "<< endl;
    cout << "You won $" << player.winnings << "! Thanks for playing!" << endl;
    cout << "Lifelines remaining: " << player.lifelineRemaining << endl;
    cout << "Incorrect answers: " << player.incorrectAnswers << endl;
  }
}