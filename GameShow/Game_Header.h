// Programmer: James Callender
// Section: 102
// Date: 3/14/2023
// Assignment: HW6-header
// Purpose: file header for gameshow program, used to define all functions and structures to be called in multiple files

//ensuring header file does not get defined more than once
#ifndef GAME_HEADER
#define GAME_HEADER

#include <string>
#include <iostream>
#include <cmath>
using namespace std;

// defines structure for Player
struct Player {
  int winnings; // amount of money player won
  int lifelineRemaining;  // lifelines left
  int incorrectAnswers; // amount of wrong answers
}; 
// creates player structure as "extern" which allows it's values to be modified by each file
extern Player player;
// source file for player in seperate file...

/*-----------------------------------------Function Prototype Documentation---------------------------------------*/
/*-----------------------PrintQuestion.cpp-------------------------*/
// Desc: used to output question and it's options.
// Pre: integer between 0 and 9 (inclusive).
// Post: outputs question and it's option based on question number
//       from an array of questions stored in header file.
void printQuestion(int questionNumber);

/*-----------------------GreetAndExit.cpp------------------------*/
// Desc: greets user.
// Pre: None.
// Pose: outputs greeting.
void greeting();

// Desc: outputs exit message.
// Pre: None.
// Post: outputs exit message based on players results (whether they won or lost).
void exitMessage(bool shouldLeave);

/*----------------------PlayerInputFunctions.cpp-----------------------*/
// Desc: checks what type of input was given then returns functions based on input
// Pre: None.
// Post: if 1-4 will return isCorrect function; 
//       if any of the keywords returns their related function;
//       else returns itself with new input.
bool checkInput(int questionNumber, string playerChoice, bool& shouldLeave);

// Desc: checks if the players answer is correct.
// Pre: integer between 0-9 (inclusive).
// Post: checks the structure of the question number for it's answer
//       then compares to player answer returning true if correct, false if wrong.
bool isCorrect(int questionNumber, int playerAnswer);

// Desc: gives a random integer based on chance, changes based on chance values.
// Pre: integer between 0-9 (inclusive).
// Post: rolls random integers and uses their values between 0-99 (inclusive) to output different
//       values based on players lifelines remaining, if all lifelines remaining might give invalid answer,
//       if some lifelines remaining might give answer within 2 inclusive, if none remaining might give
//       the correct answer. corresponding chances of each are 21%, 29%, 62%.
bool answerRandomly(int questionNumber);

// Desc: modifies leave flag to leave game.
// Pre: None.
// Post: changes leave value to true.
bool leave(bool& shouldLeave);

// Desc: Uses lifeline to get an answer.
// Pre: None.
// Post: If no lifelines left says so then returns, otherwise removes a lifeline and
//       gives a 80% chance of the correct answer and 20% of random answer using chance
//       between 0-99 (inclusive), now that I think about it I could've used 1-5 inclusive,
//       and saved runtime maybe.....
bool lifeLine(int questionNumber);

/*-------------------------Template Functions-------------------------------*/
// Desc: finds the absolute difference between two values of same type.
// Pre: two values of same type.
// Post: returns absolute difference of the two values.
template <typename T> // defines T as value type
T absoluteDifference(T val1, T val2){
  return abs(val1 - val2); // returns absolute value of them subtracted by eachother.
}

// Desc: updates current money based on whether or not player had correct answer.
// Pre: Two variable types.
// Post: if X variable is true, if money is 0 make it 100, else make it multiplied by 2;
//       if X variable is false, if money is 0 keep it so, else subtract 100 from money;
template <typename U, typename X> // defines two different value types
U updateMoney(U currentMoney, X isCorrect){
  // I didn't want the templated function to take up space in the header 
  // so I nested a ternary operator to achieve correct value
  return (currentMoney==0) ?((isCorrect==true) ? 100 : 0) : ((isCorrect==true) ? (currentMoney*2) : (currentMoney-100));
}


// structure used for each question
struct Question {
  string 
  prompt, // the question prompt
  opt1, // the first question option
  opt2, // the second question option
  opt3, // the third question option
  opt4; // the third question option
  int correctAnswer; // which # is the correct answer
};
static const int MAX_QUESTIONS = 10; // defines the amount of questions

/*Defines each question as such:
{question prompt,
1st option,
2nd option,
3rd option,
4th option,
answer}
*/

static Question q[MAX_QUESTIONS] = {
  
  {"Question 1: Which of these is not a numeric data type?", 
  "1 - integer", 
  "2 - double", 
  "3 - boolean", 
  "4 - float", 
  3},

  {"Question 2: Which of the following is a reserved c++ keyword?", 
  "1 - buddy", 
  "2 - friend", 
  "3 - pal", 
  "4 - homeslice", 
  2},

  {"Question 3: What does the & symbol mean in C++?", 
  "1 - address of", 
  "2 - and", 
  "3 - not", 
  "4 - value of", 
  1},

  {"Question 4: You do not need to document your functions in CS1570", 
  "1 - true", 
  "2 - false", 
  "3 - sometimes", 
  "4 - I don't know", 
  2},

  {"Question 5: What is \"OOP\"?", 
  "1 - Only Once Programming", 
  "2 - Object Oriented Programming", 
  "3 - What I say when I stub my toe", 
  "4 - Ope, oh peanuts.", 
  2},

  {"Question 6: How many significant digits can a float have?", 
  "1 - 9", 
  "2 - 8", 
  "3 - 7", 
  "4 - 6", 
  4},

  {"Question 7: If C is 3, then C++ is:", 
  "1 - An object oriented programming language", 
  "2 - 4", 
  "3 - Amazing", 
  "4 - All of the above", 
  4},

  {"Question 8: What is the maximum value of a signed integer in C++?", 
  "1 - 81", 
  "2 - 2147483647", 
  "3 - 11", 
  "4 - -12", 
  2},

  {"Question 9: What does == do in C++?", 
  "1 - Sets the left variable equal to the right value", 
  "2 - Checks the validity of a data type in C++", 
  "3 - Checks if 2 values are equal to each other", 
  "4 - All of the above", 
  3},

  {"Question 10: Can you lose money in this game show?", 
  "1 - Yes", 
  "2 - No", 
  "3 - Don't pick this one", 
  "4 - Don't pick this one either", 
  1}
};


#endif
// end the definitions