// Programmer: James Callender
// Section: 102
// Date: 2/21/2023
// Assignment: HW4
// Purpose: this file contains the main functions for program
//          which will play a 2-player wordle

#include <iostream>
#include <string>
#include <cctype>
#include <ios> // used for ignore function
#include <limits> // used for ignoring left over from cin input before entering new Player 2

using namespace std;
/*---------------------------------Greet Function------------------------------------------*/
// Description: greets user
// Output: outputs a greeting
void greet() {
    cout << "Hello, Welcome to Wordle For Friends!" << endl << endl;
}
/*-----------------------------Validate Word Function-------------------------------------*/
// Description: checks whether or no string is 5 letters and all alphabetical characters, if not will repeat
// Output: the 5 letter word if correct
string validateWord(string word) {
    bool valid = true;
    if (word.length() != 5) { // checks if word length is 5 characters
        cout << "The word must be exactly 5 letters long." << endl << endl;
        valid = false;
    }
    for (char c : word) {
        if (!isalpha(c)) { // checks if word is alphabetical
            cout << "The word must contain only alphabetical characters." << endl << endl;
            valid = false;
            break;
        }
    }
    if (!valid) {
        cout << "Please enter a valid word: ";
        string new_word;
        cin >> new_word;
        cout << endl << endl;
        return validateWord(new_word); // repeats function till correct
    }
    return word;
}
/*---------------------------Display Feedback Function---------------------------*/
// Description: runs through each character in "guess" word then compares to each character in "key" word
// Output: says "@.@" if letter isnt in word, "^-^" if letter is in word but not right spot, "^o^" if letter is in right spot
void displayFeedback(string& key, string& guess) {
    cout << "Matching characters: " << endl;
    for(int j = 0; j < 5; j++){ // loops through each character in guess
        bool has_match = false; // true if character is in other word
        bool has_letter = false; // true if character is in right spot in other word
        for (int i = 0; i < 5; i++) { // loops through entire key word for each character in guess
            if (guess[j] == key[i]) {
                has_match = true;
                if (guess[j] == key[j]) {
                    has_letter = true;
                }
            }
        }
        if (has_match == true) {
            if (has_letter == true) {
                cout << guess[j] << ": ^o^" << endl; // checks if in right spot and if so outputs coresponding message
            }
            else{
                cout << guess[j] << ": ^-^" << endl; // checks if letter is in word and if so outputs corresponding message
            }
        }
        else{
            cout << guess[j] << ": @.@" << endl; // if letter isn't in word then outputs corresponding message
        }
    }
    cout << endl;
}
/*----------------------Friendship Level Function----------------------------------*/
// Description: ensures friendship level is in valid parameters
// Output: outputs frienship level if correct
int friendshipLevel(int level){
    if (level < 0 || level > 100){ // checks if character is lower than 0 or higher than 100
        cout << "The friendship level you input is invalid!" << endl << endl;
        cout << "Please enter the friendship level again (an integer value in [0,100]): ";
        int newOld_level;
        cin >> newOld_level;
        cout << endl << endl;
        friendshipLevel(newOld_level); // if not then repeats
    }
    else{
        cout << "Hooray, that's an admirable friendship between you two!" << endl << endl;
        return level; // if does then outputs level
    }
    return 0;
}
/*---------------------Print Game Summary Function------------------------------*/
// Description: outputs the results of the game
// Output: players names and friend ship level before and after game
void printGameSummary(string& player1, string& player2, int& old_level, int& new_level){
    cout << "End-of-Round Game Summary" << endl;
    cout << "\t Player 1: " << player1 << endl;
    cout << "\t Player 2: " << player2 << endl;
    cout << "\t Initial friendship level: " << old_level << endl;
    cout << "\t Current friendship level: " << new_level << endl;
}
/*-------------------------------Main Function--------------------------------*/
int main() {
/*------------------------Declarations------------------------*/
    int old_level, new_level, attempt, round; /*
     old_level: level before game 
     new_level: level after game 
     attempt: number of guesses player made
     round: number of rounds done 
     */
    string guess, key, player1, player2; /*
     guess: the guess player makes
     key: the correct word
     player1: 1st players name
     player2: 2nd players name
     */
    bool win; /*
     win: whether or not player won
     */
    char replay, restart; /*
     replay: value for whether or not to replay game
     restart: value for whether or not to restart with new player
     */
/*-------------------------Greeting----------------------------*/
    greet(); // calling greet function
/*-------------------------Player 1----------------------------*/
    cout << "Player 1, please enter your name: ";
    getline(cin, player1); // assigns first player
    cout << endl << "Welcome, " << player1 << "!" << endl << endl;
/*-------------------------Player 2----------------------------*/
    do{ // we start loop here as player 2 can change if restarted
        new_level = 0; // resets new_level in case of a slip up
        round = 0; // resets round number as new game
        cout << "Now, Player 2, please enter your name: ";
        getline(cin, player2); // assigns second player
        cout << endl << "Welcome, " << player2 << "!" << endl << endl;
/*-------------------------Friendship levels------------------------*/
        cout << player1 << ", please rate the friendship level you have with " << player2 << endl;
        cout << "(enter an integer value in [0, 100]): ";
        cin >> old_level;
        cout << endl << endl;
        old_level = friendshipLevel(old_level); // calls frienship function to ensure valid value
/*-------------------------Key-Word---------------------------------*/
        do{ // loop for replaying game
            round ++; // counts rounds
            cout << "Let the game begin now!" << endl << endl;
            cout << "Wait… Frank, I need the key word from you ";
            cout << "(yes, you may whisper into my ears… and remember, it has to be a valid five-letter word all UPPERCASE): ";
            getline(cin, key); // assigns keyword
            cout << endl << endl;
            key = validateWord(key); // calls validate function to ensure valid value
            cout << "Got it! The key word is now securely processed and saved." << endl << endl;
    /*-------------------------Guessing Game-------------------------------*/ 
            attempt = 0; // resets attempts
            win = false; // resets win value
            do{ // loop for guessing attempts
                attempt++; // counts attempts
                cout << "Get ready, " << player2 << "! It's now time to Wordle with " << player1 << endl;
                cout << "You will have a total of 6 attempts to guess the word correctly." << endl << endl;
                cout << "This is your attempt #" << attempt << ", " << player2 << ", please enter a valid five-letter word (all UPPERCASE):";
                getline(cin, guess);
                guess = validateWord(guess); // calls validate function to ensure valid value
                if (guess == key){
                    win = true; // if the player guessed correct set win to true
                }
                else{
                    cout << "You entered \"" << guess << "\". Nice try, keep going!" << endl << endl;
                    displayFeedback(key, guess); // calls feedback function to print results of guess
                }
            }while(attempt < 6 && win == false); // repeat loop for 6 attempts or until they win (whichever comes first)
/*-----------------------------Results------------------------------------------*/
            if (win == true){ // if win congratulate and add points
                cout << "You entered \"" << guess << "\". Congratulations, \"" << key << "\" it is!" << endl << endl;
                new_level = old_level + attempt;
                if (new_level > 100){
                    new_level = 100; // makes sure level doesn't go above 100
                }
            }
            else { // if lose print lose message
                cout << "Unfortunately you did not guess the correct answer in time." << endl << endl;
            }
            printGameSummary(player1, player2, old_level, new_level); // call game summary function to print game results
            old_level = new_level;
/*----------------------------Replay----------------------------------------------*/
            cout << player1 << ", do you want to play another round with " << player2 << " (Y/N)? ";
            cin >> replay;
            cout << endl;
        }while(replay != 'N'); // checks if user wants to play another round with other player
/*----------------------------New Game---------------------------------------------*/        
        cout << "OK, " << player1 << " Your final friendship level with " << player2 << " is " << old_level << " after " << round << " round(s) of Wordle." << endl; // outputs amount of rounts and level
        cout << "Remember, a real friend is one who always Wordles with you when the rest of the world won’t! " << endl << endl;
        cout << "Okay " << player1 << ", do you want to start a new game with a different player then (Y/N)? " << endl << endl;
        cin >> restart;
        cin.clear(); // clears cin values for new player2 name
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores all previous cin values too just incase
    }while(restart != 'N'); // checks if user wants to restart with new player2
/*----------------------------Fair well---------------------------------------------*/
    cout << "OK, good bye, " << player1 << "! See you soon, Wordle Wordle!" << endl; // says farewell
    return 0;
}
