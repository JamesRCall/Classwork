// Programmer 1: James Callender
// Programmer 1 Section: 102
// Date: 4/25/2023
// Assignment: Final Project
// File: main.cpp
// Purpose: uses classes defined in BankRob.h to run the program and output to console.

#include "bankrob.h"

int main() {
  srand(85); // Seed the random number generator
  int total_rob = 0, active_robs = 0;
  bool rWin=0, pWin=0;
  // create city class
  City city;
  // generates police, robbers, and jewels
  city.generatecords();
  // prints the initial grid
  std::cout << "Initial grid:\n";
  city.printGrid();

  for (int i = 0; i < 30; ++i) { // You can modify the number of steps
    std::cout << "Step: " << i + 1 << std::endl;
    
    // loops through all robbers in city
    for (auto& robber : city.getRobbers()) {
      // stores previous cordinates of robber then removes their mark on grid
      int x,y;
      x = robber.getX();
      y = robber.getY();
      city.grid[x][y] = ' ';
      // if robber is active move
      if (robber.isRActive()) {
        robber.rmove(city, city.getRobbers());
      }
    }
    // loops again through all robbers in city
    for (auto& robber : city.getRobbers()) {
      // stores new locations and updates grid with them. (done in second loop to prevent robbers incorrectly overlapping)
      int x,y;
      x = robber.getX();
      y = robber.getY();
      // loops through robbers again with a second robber to compare
      for(auto& otherRobber : city.getRobbers()){
        if(x == otherRobber.getX() && y == otherRobber.getY() && robber.getid() != otherRobber.getid()){
          // if two robbers are on same block update to "R"
          city.grid[x][y] = 'R';
        }
      }
      // if the grid isn't already defined as multiple robbers then update regularly
      if(city.grid[x][y] != 'R'){
        city.grid[x][y] = 'r';
      }
    }
    
    // get police on board then moves police
    for (auto& police : city.getPolice()) {
      police.move(city, city.getRobbers());
    }
    // prints the grid to console
    city.printGrid();
    // runs check to ensure theres still active robbers
    for (auto& robber : city.getRobbers()){
      if(robber.isRActive() == true){
        active_robs++;
      }
      // loops through robbers bags to find total accumulated value
      for(auto& bag : robber.getJewels()) {
      total_rob += bag.getValue();
      } 
    }
    // if robbers reach 438 set robber win value and break
    if(total_rob >= 438){
      rWin = true;
      break;
    }
    // else reset value
    else{
      total_rob = 0;
    }
    // if there are no active robbers set police win value and break
    if(active_robs == 0){
      pWin = true;
      break;
    }
    // else reset the active robbers
    else{
      active_robs = 0;
    }
  }
  // outputs summary of the game
  cout << "Summary of the chase: " << endl;
  // if neither values set off then turns reached 30.
  if(rWin == false && pWin == false){
    cout << "\tThe robbers wins the chase because maximum turns (30) have been reached." << endl;
  }
  // else is robbers reached 438 output to console
  else if(rWin == true){
    cout << "\tThe robbers wins the chase because networth >= $438." << endl;
  }
  // else the police won
  else{
    cout << "\tThe police won the chase because all robbers have been arrested." << endl;
  }
  // loops through police to find police values in class
  for (auto& police : city.getPolice()) {
    cout << "\tPolice id: " <<  police.getid() << endl;
    cout << "\t\tConfiscated jewels amount: $" << police.getValue() << endl;
    cout << "\t\tFinal number of robbers caught: " << police.getCaught() << endl;
  }
  // loops through robbers to find robbers values in class
  for (auto& robber : city.getRobbers()) {
    int value = 0;
    // loops through robbers bag to find accumulated value
    for(auto& bag : robber.getJewels()) {
      value += bag.getValue();
    }
    cout << "\t" << robber.getType() << " Robber id: " << robber.getid() << endl;
    cout << "\t\tFinal number of jewel picked up: " << robber.bag.size() << endl;
    cout << "\t\tTotal jewel worth: $" << value << endl;
  }
  
    return 0;
}
