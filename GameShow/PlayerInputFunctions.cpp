// Programmer: James Callender
// Section: 102
// Date: 3/14/2023
// Assignment: HW6-PlayerinputFunctions
// Purpose: all functions relating to the actions done based on player's input

#include "Game_Header.h"

bool checkInput(int questionNumber, string playerChoice, bool& shouldLeave) {
  int playerAnswer = 0; // defined as 0 to prevent errors;
  cout << endl; // endline for readibilty
  // checks if player choice is 1 then assigns integer as such and
  // calls isCourrect function comparing to correct answer returning true or false
  if(playerChoice == "1"){
    playerAnswer = 1; 
    return isCorrect(questionNumber, playerAnswer); 
  }
  // checks if player choice is 2 then assigns integer as such and
  // calls isCourrect function comparing to correct answer returning true or false
  else if(playerChoice == "2"){ 
    playerAnswer = 2;
    return isCorrect(questionNumber, playerAnswer);
  }
  // checks if player choice is 3 then assigns integer as such and
  // calls isCourrect function comparing to correct answer returning true or false
  else if(playerChoice == "3"){
    playerAnswer = 3;
    return isCorrect(questionNumber, playerAnswer);
  }
  // checks if player choice is 4 then assigns integer as such and
  // calls isCourrect function comparing to correct answer returning true or false
  else if(playerChoice == "4"){
    playerAnswer = 4;
    return isCorrect(questionNumber, playerAnswer);
  }
  // if player didn't enter an answer, select among other options
  else{
    // if random is chosen return random function (which will return this function after done)
    if(playerChoice == "random"){
      return answerRandomly(questionNumber);
    }
    // if lifeline is chosen return lifeline function (which will also return to this function)
    else if(playerChoice == "lifeline"){
      return lifeLine(questionNumber);
    }
    // if leave call leave function which returns false and flags leave option
    else if(playerChoice == "leave"){
      return leave(shouldLeave);
    }
    else{ // if no ifs were triggered then invalid and call again
      cout << "invalid response, try again: " << endl;
      string newPlayerChoice;
      getline(cin, newPlayerChoice);
      return checkInput(questionNumber, newPlayerChoice, shouldLeave);
    }
  }
  return false; // safety measure incase if/else statements fail
}

// playerAnswer is assigned 3 as default
bool isCorrect(int questionNumber, int playerAnswer = 3){
  // compares players answer to correct answer
  if(playerAnswer == q[questionNumber].correctAnswer){
    return true;
  }
  return false;
}
bool answerRandomly(int questionNumber){
  bool leave = 0;
  // defines leave false for return function later
  static int percChance = -1, randomNumber = 0;
  // static ints defined only in function to save runtime and hassle
  static char typeofChange = 'A';
  //static char swaps between sheep mischief based on lifelines left
  if(player.lifelineRemaining < 3){
    typeofChange = 'B';
  }
  else if(player.lifelineRemaining < 1){
    typeofChange = 'C';
  }
  // assigns a percent chance using random function
  percChance = rand()%100;
  // assigns a default random number
  randomNumber = (rand()%4)+1;
  // checks percent chance against each case to see if any mischief should be done
  switch(typeofChange){
    case 'A':
      cout << "you are on " << typeofChange << endl;
      if(percChance < 21){
        cout << "case A initiated" << endl;
        randomNumber = (rand()%2)+5;
        // reassigns random number as 5 or 6 randomly
      }
      // breaks to ensure future cases don't trigger
      break;
    case 'B':
      cout << "you are on " << typeofChange << endl;
      if(percChance < 29){
        cout << "case B initiated" << endl;
        while(absoluteDifference(q[questionNumber].correctAnswer, randomNumber) > 2){
          randomNumber = (rand()%4)+1;
          // while the difference between the correct answer and the random number is greater than 2,
          // keep generating new random numbers
        }
      }
      // breaks to ensure future cases don't trigger
      break;
    case 'C':
      cout << "you are on " << typeofChange << endl;
      if(percChance < 62){
        cout << "Case C initiated" << endl;
        randomNumber = q[questionNumber].correctAnswer;
        // 62% chance to give correct answer
      }
      // breaks just because...
      break;
    // created default because of force of habbit, then just had it break..... 
    // I'm too scared to remove it, please don't mark me off for it ;-;
    default:
      break;
  }
  cout << "You thought of the number " << randomNumber << ". What is Your answer? "<< endl;
  // assigns a new player input
  string newPlayerChoice;
  getline(cin, newPlayerChoice);
  // calls the primary check input function again by returning it
  return checkInput(questionNumber, newPlayerChoice, leave);
}
bool leave(bool& shouldLeave){
  // literally just flags the leave statement
  shouldLeave = true;
  return false;
}
bool lifeLine(int questionNumber){
  bool leave = 0; // ensures leave isn't true
  static int lifeLines = player.lifelineRemaining; // sets lifelines = players
  //static ints for friends answer and the chance of it being wrong
  static int friendsAnswer = 0, incorrectChance;

  if(lifeLines > 0){ // while you have more than 0 lifelines
    lifeLines--; //removes one of the lifelines
    incorrectChance = rand()%100; // sets percent chance
    if(incorrectChance < 80){ // if chance is less than 80 give correct answer
      friendsAnswer = q[questionNumber].correctAnswer;
    }
    else{ // else give a random answer
      friendsAnswer = (rand()%4+1);
    }
    cout << "Your friend said the answer was " << friendsAnswer << ". ";
    player.lifelineRemaining--; // removes a player lifeline
  }
  else{
    cout << "You are out of lifelines! ";
  }
  cout << "What is your answer? " << endl << endl;
  
  string newPlayerChoice;
  getline(cin, newPlayerChoice);
  return checkInput(questionNumber, newPlayerChoice, leave);
}