// Programmer 1: James Callender
// Programmer 1 Section: 102
// Date: 4/25/2023
// Assignment: Final Project
// File: BankRob.h
// Purpose: used to store all classes for the bankrob program and define all functions inside them
#ifndef BANKROB
#define BANKROB

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

const int JEWELMAX = 47; //Max number of jewels
const int POLICENUM = 1; //2 Total police
const int ROBBERNUM = 2; //2 "Ordinary" robbers
const int GreedyNUM = 2; //2 "Greedy" robbers, 4 robbers in total

// defines all classes
// note: function definitions are put at top of each class definition.
class City;
class Jewel;
template <typename Jewel>
class Robber;
class Police;


class City {
public:
  City() : grid(10, vector<char>(10, ' ')), jewelCount(0) {}
  
  // Desc: This function is used for removing jewels from city class and updating jewel count
  // Pre: list of jewels in city must be greater than 0.
  // Post: removes jewel at specified x and y location.
  void removeJewel(int x, int y);

  // Desc: generates all police, robbers, and jewels in city.
  // Pre: list to put each class in and jewel, robber, and police classes defined.
  // Post: creates all classes with unique x,y locations and ids, and values for jewels.
  void generatecords();

  // Desc: outputs the 10x10 grid to console
  // Pre: 10x10 grid in city
  // Post: outputs the 10x10 grid with specialized colors for each class and in their respective locations.
  void printGrid();

  // Desc: adds back jewels from greedy robbers running into other robbers
  // Pre: valid x and y within 0 to 10
  // Post: adds jewel back to city class in correct x and y location, if something is at that spot with generate location for an empty spot.
  void addJewel(int value, int x, int y);

  // functions used to pull list of police, robber, and jewel
  list<Police>& getPolice() {
    return police;
  }
  list<Robber<Jewel>>& getRobbers() {
    return robbers;
  }
  list<Jewel>& getJewels() {
    return jewels;
  }
  // function used to pull jewel count from private location
  int getJewelCount() {
    return jewelCount;
  }
  // vector definition for the grid
  vector<vector<char>> grid;
  // list definition for robber
  list<Robber<Jewel>> robbers;

private:
  int jewelCount;
  // list definition for jewels and polive
  list<Jewel> jewels;
  list<Police> police;
  // friends all other classes to allow values to be cross compatible
  friend class Jewel;
  template <typename T>
  friend class Robber;
  friend class Police;
};

class Police {
public:
  Police(int id, int x, int y)
    : id(id), x(x), y(y), confiscatedLootValue(0), robbersCaught(0) {}

  // Desc: moves police in identical direction to an "ordinary" robber
  // Pre: ordinary robbers last move vector pair.
  // Post: checks if robber is at point then moves police in the same vector direction as robber then calls arrest to check for robber and arrest also checks for jewels to pick up.
  void move(City& city, list<Robber<Jewel>>& robbers);

  // Desc: function used to arrest robbers and set them inactive
  // Pre: none.
  // Post: checks if a robber is at same x and y and if so sets their active value to false then removes all jewels in their bag and updates police confiscated value
  void arrest(City& city, int x, int y);

  // functions used to pull private values from police class
  int getValue(){
    return confiscatedLootValue;
  }
  int getCaught(){
    return robbersCaught;
  }
  int getid(){
    return id;
  }

private:
  int id;
  int x;
  int y;
  int confiscatedLootValue;
  int robbersCaught;

  // friends city and robber to allow values to be pulled
  friend class City;
  template <typename Jewel>
  friend class Robber;
};

class Jewel {
public:
  Jewel(int value, int x, int y) : value(value), x(x), y(y) {}

  // functions used to pull private values of jewel.
  int getValue() const {
    return value;
  }
  int getX() const {
    return x;
  }

  int getY() const {
    return y;
  }

private:
  int value;
  int x;
  int y;

  // friends city and police to allow them to pull private values
  friend class City;
  friend class Police;
};

template <typename Jewel>
class Robber {
public:
  Robber(int id, int x, int y, string type = "Ordinary")
    : id(id), x(x), y(y), type(type), isActive(true) {}

  // Desc: function used to move robber
  // Pre: robber with valid x and y location
  // Post: first checks if robber is greedy, if so moves robber in path of a randomly valid jewel direction, otherwise moves robber randomly in a valid direction,
  //       then calls pickUpLoot, then checks if robber is greedy and ran into another robber, if so halfs robbers bag and returns jewels to city, then stores direction used.
  void rmove(City& city, list<Robber<Jewel>>& robbers);

  // Desc: picks up jewels on x and y spot
  // Pre: none
  // Post: checks city for any jewels on x and y location, if so calls removeJewel to remove it from city and pushes the jewel into robber bag
  void pickUpLoot(City& city, list<Robber<Jewel>>& robbers);
  
  // used to store robbers last direction
  pair<int, int> lastMove;
  
  // functions used to pull private values
  string getType() const {
    return type;
  }
  int getid() const {
    return id;
  }
  int getX() const {
    return x;
  }
  int getY() const {
    return y;
  }
  bool isRActive() const {
    return isActive;
  }
  list<Jewel>& getJewels() {
    return bag;
  }

  list<Jewel> bag;
private:
  int id;
  int x;
  int y;
  string type;
  bool isActive;

  // friends city and police to allow them to pull values
  friend class City;
  friend class Police;
};

void City::removeJewel(int x, int y) {
  bool jewelRemoved = false;

  // loops through jewels in city and erases jewel if on x and y location
  for (auto it = jewels.begin(); it != jewels.end();) {
    if (it->x == x && it->y == y) { // Access jewels.x and jewels.y directly
      jewelRemoved = true;
      it = jewels.erase(it);
    } else {
      ++it;
    }
  }

  // if a jewel was removed updates jewel count.
  if (jewelRemoved) {
    jewelCount--;
  }
}

void City::generatecords() {
  // sets all values to constant values
  int j = JEWELMAX;
  int p = POLICENUM;
  int r = ROBBERNUM;
  int g = GreedyNUM;
  int id_r = 1, id_p = 1;
  int x, y;
  // while all values have not reached 0 continue to generate x and y locations and store objects into them
  while (j > 0 || p > 0 || r > 0 || g > 0) {
    x = rand() % 10;
    y = rand() % 10;
    // checks if grid spot is empty
    if (grid[x][y] == ' ') {
      // checks if police still need to be generated
      if (p > 0) {
        // adds police object to city list
        Police new_police(id_p++, x, y);
        police.push_back(new_police);
        // updates grid value
        grid[x][y] = 'p';
        // counts police needed down
        p--;
      // checks if robbers need to be made
      } else if (r > 0) {
        // adds robber object to city list
        Robber<Jewel> new_robber(id_r, x, y, "Ordinary");
        robbers.push_back(new_robber);
        // updates grid
        grid[x][y] = 'r';
        // counts robber down
        r--;
        id_r++;
      // same as robber but with greedy
      } else if (g > 0) {
        Robber<Jewel> new_robber(id_r, x, y, "Greedy");
        robbers.push_back(new_robber);
        grid[x][y] = 'r';
        g--;
        id_r++;
      // same as rest but for jewel.
      } else if (j > 0) {
        Jewel new_jewel((x+y), x, y);
        jewels.push_back(new_jewel);
        grid[x][y] = 'J';
        j--;
        jewelCount++;
      }
    }
  }
}

void City::printGrid() {
  const int numRows = grid.size();
  const int numCols = grid[0].size();

  // print top border
  cout << "\033[90m+\033[0m";
  for (int j = 0; j < numCols; ++j) {
    cout << "\033[90m---+\033[0m";
  }
  cout << endl;

  // print rows
  for (int i = 0; i < numRows; ++i) {
    // print left border
    cout << "\033[90m|\033[0m";

    // print cells
    for (int j = 0; j < numCols; ++j) {
      char cell = grid[i][j];
      // checks each cell type and uses unique color based on text in cell
      if (cell == 'J') {
        cout << " \033[38;2;135;206;235m" << cell << "\033[0m\033[90m |\033[0m"; // light green for J
      }
      else if (cell == 'p') {
        cout << " \033[37m" << cell << "\033[0m\033[90m |\033[0m"; // light blue for p
      }
      else if (cell == 'r' || cell == 'R') {
        cout << " \033[91m" << cell << "\033[0m\033[90m |\033[0m"; // light red for r or R
      }
      else {
        cout << " " << cell << " \033[90m|\033[90m";
      }
    }

    cout << endl;

    // print horizontal divider
    cout << "\033[90m+\033[0m";
    for (int j = 0; j < numCols; ++j) {
      cout << "\033[90m---+\033[0m";
    }
    cout << endl;
  }
}

void City::addJewel(int value, int x, int y) {
  // if city grid is occupied creates a new x and y until an empty spot is found
  if(grid[x][y] != ' '){
      int newx, newy;
    do{
      newx = rand()%10;
      newy = rand()%10;
    }while(grid[newx][newy] != ' ');
    x = newx;
    y = newy;
  }
  // once valid x and y places jewel and adds to city list
  grid[x][y] = 'J';
  Jewel new_jewel(value, x, y);
  jewels.push_back(new_jewel);
  jewelCount++;
}

void Police::arrest(City& city, int x, int y) {
  // checks robbers cordinates in city to police cordinates
  for (auto& robber : city.getRobbers()) {
    // if robber matches same spot and isnt active turns robber inactive
    if (robber.x == x && robber.y == y && robber.isActive) {
      robber.isActive = false;
      robbersCaught++;
      // removes all jewels from robbers bag and adds value to police value
      for (const auto& jewel : robber.bag) {
      confiscatedLootValue += jewel.getValue(); // Use the getter function
      }
      robber.bag.clear();
    }
  }
}

void Police::move(City& city, list<Robber<Jewel>>& robbers) {
  // Check and arrest any robbers at the current location.
  arrest(city, x, y);
  // removes previous police location mark
  city.grid[x][y] = ' ';

  // Find the first Ordinary robber in the list
  Robber<Jewel>* Ordinary_robber = nullptr;
  for (auto& robber : city.getRobbers()) {
      if (robber.type == "Ordinary" && robber.isActive) {
          Ordinary_robber = &robber;
          break;
      }
  }

  int newX = x;
  int newY = y;
  // moves police in same direction as ordinary robber
  if (Ordinary_robber) {
      newX = x + Ordinary_robber->lastMove.first;
      newY = y + Ordinary_robber->lastMove.second;
  }

  // Choose a random direction if the new position is out of grid boundaries or no Ordinary robber found
  while (newX < 0 || newX >= 10 || newY < 0 || newY >= 10 || (newX == x && newY == y)) {
      vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
      int direction = rand() % directions.size();
      newX = x + directions[direction].first;
      newY = y + directions[direction].second;
  }

  x = newX;
  y = newY;

  for (auto& jewel : city.getJewels()) {
      // Check if the jewel is at the robber's current position
      if (x == jewel.x && y == jewel.y) {
          confiscatedLootValue += jewel.getValue();
          // Remove the jewel from the city's list
          city.removeJewel(x, y);
          // Break the loop as we've found and picked up the jewel
          break;
      }
  }
  // calls remove jewel function
  city.removeJewel(x, y);
  // updates grid to new location
  city.grid[x][y] = 'p';

  // Check and arrest any robbers at the new location.
  arrest(city, x, y);
}

template <typename Jewel>
void Robber<Jewel>::rmove(City& city, list<Robber<Jewel>>& robbers) {
  // defines all possible locations in vector pair
  vector<pair<int, int>> directions = {{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {1, 0}, {-1, -1}, {0, -1}, {1, -1}};
  int direction, newX, newY;
  bool canMove = false;
  // resets canMove value
  canMove = false;
  // checks if robber is greedy and if so finds jewel path
  if(type == "Greedy"){
    // ensures jewels are in city
    if (city.jewelCount > 0) {
      // creates new vector to store possible jewel path vectors
      vector<int> jewelDirectionIndices;
      for (int i = 0; i < directions.size(); ++i) {
        newX = x;
        newY = y;
        while (true) {
          newX += directions[i].first;
          newY += directions[i].second;
          // goes till borders of grid
          if (newX < 0 || newX >= 10 || newY < 0 || newY >= 10) {
            break;
          }
          // loops through in each direction to location "J" on grid
          if (city.grid[newX][newY] == 'J') {
            // if a "J" is found stores that vector direction in jewel vector
            jewelDirectionIndices.push_back(i);
            break;
          }
        }
      }
      // if their are valid directions randomly selects from the valid options
      if (!jewelDirectionIndices.empty()) {
        direction = jewelDirectionIndices[rand() % jewelDirectionIndices.size()];
        newX = x + directions[direction].first;
        newY = y + directions[direction].second;
        x = newX;
        y = newY;
        // sets canMove to true so the robber does move again
        canMove = true;
      }
    }
  }
  // if the robber is ordinary or couldnt find a path moves randomly
  if (!canMove) {
    do {
      direction = rand() % 8;
      newX = x + directions[direction].first;
      newY = y + directions[direction].second;
      // ensures direction is within borders
      if (newX >= 0 && newX < 10 && newY >= 0 && newY < 10) {
        canMove = true;
        x = newX;
        y = newY;
      }
    } while (!canMove);
  }
  
  // calls pick up function
  pickUpLoot(city, robbers);
  // if a robber was at this grid location
  if(city.grid[x][y] == 'R' || city.grid[x][y] == 'r'){
    // checks if robber is greedy and if so halfs robbers back and calls function to place jewels back.
    if(type == "Greedy"){
      int halfIndex = bag.size() / 2;
      auto bagIter = bag.begin();
      for (int i = 0; i < halfIndex; ++i) {
          if (bagIter != bag.end()) {
              city.addJewel(bagIter->getValue(), bagIter->getX(), bagIter->getY());
              bagIter = bag.erase(bagIter);
          }
      }
    }
  }
  // stores last direction vector
  lastMove = directions[direction];
}

template <typename Jewel>
void Robber<Jewel>::pickUpLoot(City& city, list<Robber<Jewel>>& robbers) {
    int consecutive_moves = 0;
    // Iterate over the city's jewels list
    for (auto& jewel : city.getJewels()) {
        // Check if the jewel is at the robber's current position
        if (jewel.getX() == x && jewel.getY() == y) {
            // Add the jewel to the robber's bag
            if(type == "Greedy"){
              if(jewel.getValue()%2 == 0){
                consecutive_moves++;
              }
              else{
                consecutive_moves = 0;
              }
            }
            bag.push_back(jewel);
            // Remove the jewel from the city's list
            city.removeJewel(x, y);
            // Break the loop as we've found and picked up the jewel
            break;
        }
    }
    // checks if consecutive move is triggered if so calls move function
    if(consecutive_moves > 0){
      if(consecutive_moves == 4){
        // if 3 consecutive moves made resets consecutive moves
        consecutive_moves = 0;
      }
      else{
        rmove(city, robbers);
      }
    }
}
#endif