// Programmer: James Callender
// Section: 102
// Date: 3/6/2023
// Assignment: HW5
// Purpose: this file contains all functions used for the program Galatic.cpp
//          which will input guess cordinates from the player and have them play against
//          an alien until one dies

#include <iostream>
#include <cstdlib>
// used for random cordinates
#include <ctime>
// used to generate random cordinates (set seed to 612 on line 250)
#include <string>
// used for the type of powerup string variable

using namespace std;

/*-----------------------------FUNCTIONS DOCUMENTATION------------------------------*/
// Desc: This function generates to int values for player between 0 to 2 inclusive
// Pre: None
// Post: Two variables used are changed to int values between 0 to 2
void generatePlayerPositions(int &current_x, int &current_y);

// Desc: This function generates to int values for alien between 0 to 2 inclusive
// Pre: None
// Post: Two variables used are changed to int values between 0 to 2
void generateAlienPositions(int &current_x, int &current_y);

// Desc: This function generates to int values for Power up between 0 to 2 inclusive
// Pre: None
// Post: Two variables used are changed to int values between 0 to 2
void generatePowerUpPositions(int &current_x, int &current_y);

// Desc: This function checks if player is at power up location and applies correct power up based on location
// Pre: The four int x/y values must be between 0 and 2 inclusive
// Post: If player is at power up location will increase life/bullets based on location
void acquirePowerUp(int powerup_x, int powerup_y, int& player_x, int& player_y, int& player_lives, int& player_bullets);

// Desc: This function decreases alien_lives based on 2 guess integers by checking them to aliens location
// Pre: The four in x/y values must be between 0 and 2 inclusive
// Post: Will decrease alien_lives based on guess location
void shootAlien(int guess_x, int guess_y, int alien_x, int alien_y, int& alien_lives);

// Desc: This function decreases player_lives based on aliens cordinates by checking them to players location
// Pre: The four in x/y values must be between 0 and 2 inclusive
// Post: Will decrease player_lives based on alien location
void shootPlayer(int player_last_x, int player_last_y, int alien_x, int alien_y, int& player_lives);

// Desc: This function ensures the players guess inputs are between 0 and 2 inclusive
// Pre: None
// Post: If correct will return, otherwise recalls function with new inputs
void validateGuess(int& guess_x, int& guess_y);

// Desc: This function uses the acquirePowerUp function but includes variables to check if powerup was given and if so what type
// Pre: None
// Post: Updates variables related to type of powerup and value and whether or not powerup was acquired
void powerup_Status(int powerup_x, int powerup_y, int& player_x, int& player_y, int& player_lives, int& player_bullets, int& powerup_value, bool& powerup_acquired, string& powerup_type);

// Desc: This functions displays the game's status at the end of every round
// Pre: None
// Post: Outputs lives of each entity and players bullets and type of power up acquired
void displayGameStatus(int player_lives, int alien_lives, int bullets_left, bool powerup_acquired, int powerup_value, string powerup_type);

/*----------------------------------------FUNCTIONS-----------------------------------------------*/
void generatePlayerPositions(int &current_x, int &current_y)
{
  static int prevPlayer_x; // update previous x value to current x value
  static int prevPlayer_y; // update previous y value to current y value

  do {
    current_x = rand() % 3; // generate a random x value between 0 and 2 (inclusive)
    current_y = rand() % 3; // generate a random y value between 0 and 2 (inclusive)
  } while (current_x == prevPlayer_x && current_y == prevPlayer_y); // check if the new position is the same as the previous
  prevPlayer_x = current_x; // assigns previous postion to satatic var
  prevPlayer_y = current_y; // assigns previous postion to satatic var
  return;
}

void generateAlienPositions(int &current_x, int &current_y)
{
  static int prevAlien_x; // update previous x value to current x value
  static int prevAlien_y; // update previous y value to current y value

  do {
    current_x = rand() % 3; // generate a random x value between 0 and 2 (inclusive)
    current_y = rand() % 3; // generate a random y value between 0 and 2 (inclusive)
  } while (current_x == prevAlien_x && current_y == prevAlien_y); // check if the new position is the same as the previous
  prevAlien_x = current_x; // assigns previous postion to satatic var
  prevAlien_y = current_y; // assigns previous postion to satatic var
  return;
}

void generatePowerUpPositions(int &current_x, int &current_y)
{
  static int prevPower_x; // update previous x value to current x value
  static int prevPower_y; // update previous y value to current y value

  do {
    current_x = rand() % 3; // generate a random x value between 0 and 2 (inclusive)
    current_y = rand() % 3; // generate a random y value between 0 and 2 (inclusive)
  } while (current_x == prevPower_x && current_y == prevPower_y); // check if the new position is the same as the previous
  prevPower_x = current_x; // assigns previous postion to satatic var
  prevPower_y = current_y; // assigns previous postion to satatic var
  return;
}

void acquirePowerUp(int powerup_x, int powerup_y, int& player_x, int& player_y, int& player_lives, int& player_bullets)
{
  if (powerup_x == player_x && powerup_y == player_y) // checks if player is at power-up location
  {
    int powerup_sum = powerup_x + powerup_y;

    if (powerup_sum % 2 == 0) // if power-up sum is even, give extra lives
    {
      int extra_lives = powerup_sum;
      player_lives += extra_lives;
      cout << "Player gained " << extra_lives << " extra lives!" << endl;
    }
    else // if power-up sum is odd, give extra bullets
    {
      int extra_bullets = powerup_sum;
      player_bullets += extra_bullets;
      cout << "Player gained " << extra_bullets << " extra bullets!" << endl;
    }
  }
  return;
}

void shootAlien(int guess_x, int guess_y, int alien_x, int alien_y, int& alien_lives)
{
  if (guess_x == alien_x && guess_y == alien_y) // if guess is an exact hit
  {
    alien_lives -= 2;
    cout << "Direct hit! Alien loses 2 lives!" << endl;
  }
  else if (guess_x == alien_x || guess_y == alien_y) // if guess is adjacent to alien
  {
    alien_lives -= 1;
    cout << "Close hit! Alien loses 1 life!" << endl;
  }
  else{
    cout << "Missed! The alien is raging!" << endl;
  }
  return;
}

void shootPlayer(int player_last_x, int player_last_y, int alien_x, int alien_y, int& player_lives)
{
  if (player_last_x == alien_x && player_last_y == alien_y) // alien's position matches player's last position
  {
    player_lives -= 2;
    cout << "The alien is attacking you! " << endl;
    cout << "Player loses 2 lives. " << player_lives << " lives remaining. " << endl;
  }
  else if (player_last_x == alien_x || player_last_y == alien_y) // alien's position is adjacent to player's last position
  {
    player_lives -= 1;
    cout << "The alien is attacking you! " << endl;
    cout << "Player loses 1 life. " << player_lives << " lives remaining. " << endl;
  }
  return;
}

void validateGuess(int& guess_x, int& guess_y) 
{
  if (guess_x < 0 || guess_x > 2 || guess_y < 0 || guess_y > 2) { // if not in range
    cout << "Invalid input. Please enter two integers between 0 and 2 (inclusive): ";
    cin >> guess_x >> guess_y;
    cout << endl;
    validateGuess(guess_x, guess_y);
  }
  return;
}
void powerup_Status(int powerup_x, int powerup_y, int& player_x, int& player_y, int& player_lives, int& player_bullets, int& powerup_value, bool& powerup_acquired, string& powerup_type)
{
  static int prev_player_lives = -1; // used to keep track of previous lives
  static int prev_player_bullets = -1; // used to keep track of previous bullets
  prev_player_bullets = player_bullets;
  prev_player_lives = player_lives;
  acquirePowerUp(powerup_x, powerup_y, player_x, player_y, player_lives, player_bullets);
  if(prev_player_lives < player_lives){ // checks after function called if lives changed
    powerup_acquired = 1;
    powerup_value += (player_lives - prev_player_lives); // if changed check value
    powerup_type = " life(s)"; // assign type to life
  }
  else if(prev_player_bullets < player_bullets){ // checks after function if bullets changed
    powerup_acquired = 1; 
    powerup_value += (player_bullets - prev_player_bullets); // if changed check value
    powerup_type = " bullet(s)"; // assign type to bullets
  }
  else{
    powerup_acquired = 0;
  }
  return;
}
void displayGameStatus(int player_lives, int alien_lives, int bullets_left, bool powerup_acquired, int powerup_value, string powerup_type)
{
  cout << "Current game status" << endl;
  cout << "Player's life: " << player_lives << endl;;
  cout << "Alien's life: " << alien_lives << endl;
  cout << "Bullets left: " << bullets_left << endl;
  if(powerup_acquired == 1){ // if power up acquired
  cout << "Powerup acquired: " << powerup_value << powerup_type << endl;
  }
  else{
    cout << "Powerup acquired: none " << endl; // if no power up acquired
  }
  return;
}
/*------------------------------------------MAIN FUNCTION----------------------------------------*/
int main()
{
  int 
    player_x, player_y, // players cordinates
    prev_player_x, prev_player_y, // players previous cordinates
    player_lives, // amount of lives the player has
    player_bullets, // amount of bullets the player has
    alien_x, alien_y, // alien cordinates
    alien_lives, // amount of lives alien has
    prev_alien_lives, // previous lives alien had (used for consecutive shots)
    powerup_x, powerup_y, // power up cordinates
    guess_x, guess_y, // guess cordinates
    powerup_value, // the amount the power up added
    round, // what round it is
    consecutive_shots; // how many shots player got in a row
  string
    powerup_type; // the type of power up
  bool 
    powerup_acquired, // whether or not power up was acquired
    reward; // whether or not player has shot 2 shots in a row

  cout << "Welcome to GalDef - The Galactic Defender!" << endl;
  cout << "The game starts now!" << endl;

  player_lives = 5; // sets players lives to 5
  player_bullets = 15; // sets players bullets to 15
  alien_lives = 10; // sets aliens lives 10
  cout << "You have " << player_lives << " lives and " << player_bullets << " bullets to begin with, the alien has " 
       << alien_lives << " lives. Goodluck, Let the game begin…!!!" << endl << endl;

  generatePlayerPositions(player_x, player_y); // generates player location
  generateAlienPositions(alien_x, alien_y); // generates alien location
  generatePowerUpPositions(powerup_x, powerup_y); // generates powerup location
  powerup_acquired = 0; // resets whether power up is acquired
  powerup_value = 0; // resets powerup value
  round = 0; // sets round to 0
  consecutive_shots = 0; // sets consecutive shots to 0
  reward = 0; // sets 2 consecutive shots to false
  srand(612); // sets seed to 612
  do{ // repeats rounds till while condition met
    round += 1; // counts round
    cout << "Round " << round << ": " << endl;
    for(int i = 0; i < 2; i ++){ // loops for 2 player shots
      if (player_bullets > 0){
        cout << "Enter the coordinates to shoot (x, y): ";
        cin >> guess_x >> guess_y;
        validateGuess(guess_x, guess_y); // calls validate function
        prev_alien_lives = alien_lives;
        shootAlien(guess_x, guess_y, alien_x, alien_y, alien_lives); // calls shoot function
        player_bullets -= 1; // takes bullet for shot
        if(alien_lives < prev_alien_lives){ // if alien is shot
          consecutive_shots += 1; // add a consecutive shot
          cout << "The alien’s position has been refreshed to a new location." << endl;
          generateAlienPositions(alien_x, alien_y); // alien moves because hit
          if(consecutive_shots == 2){ // if 2 consecutive shots then trigger reward
            consecutive_shots = 0; // reset consecutive shots
            reward = 1;
          }
        }
        else{ // if miss set consecutive shots back to 0
          consecutive_shots = 0;
        }
      }
      else{ // if no bullets left cant shoot
      cout << "No bullets left!" << endl;
      }
    }
    if(reward == 1){ // if reward triggered give player
      player_lives += 1;
      player_bullets += 3;
      cout << "Congratulations! You hit the alien twice in a row and received an extra life and 3 additional bullets! ";
      cout << "You now have " << player_lives << " lives and " << player_bullets << " bullets!" << endl;
      reward = 0; // reset reward
    }
    powerup_Status(powerup_x, powerup_y, player_x, player_y, player_lives, player_bullets, powerup_value, powerup_acquired, powerup_type);
    // checks if player recieved power up
    if(round > 1){ // after first round alien starts attacking
      shootPlayer(prev_player_x, prev_player_y, alien_x, alien_y, player_lives);
    }
    displayGameStatus(player_lives, alien_lives, player_bullets, powerup_acquired, powerup_value, powerup_type);
    // show round results
    prev_player_x = player_x;
    prev_player_y = player_y; // set old cordinates
    generatePlayerPositions(player_x, player_y); // generate new ones
    generatePowerUpPositions(powerup_x, powerup_y);
    cout << endl;
  }while(player_lives > 0 && alien_lives > 0); // continue until a entity dies
  if(alien_lives <= 0){ // if alien died
    cout << "The alien has been defeated! Congratulations, player! You saved the galaxy! " << endl;
  }
  else{ // if alien didnt die then player died
    cout << "Player threw, alien destroyed the galaxy..." << endl;
  }

  cout << "Thanks for playing GalDef!" << endl;
}