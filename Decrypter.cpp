// Programmer: James Callender
// Student ID: jrcnb4
// Section: 102
// Date: 2/21/2023
// File: Caesar.cpp
// Purpose: decipher messages

#include  <iostream>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

int main()
  {
/*------------------------------------ Inputs ---------------------------------- */

  string msg, choice, choice2;
  int val, lock, error;
  char option, repeater;

/*------------------------------------ Intro -------------------------------------- */

  cout << "Welcome to the Oscar Academy of Magic Caesar Cipher Program!" << endl << endl;
  cout << "Unraveling the secret acceptance decision letter from the Oscar Academy of Magic..." << endl << endl;
  cout << "Using a shift value of 2..." << endl << endl << "..." << endl << endl << "Drumroll please..." << endl << endl;
  cout << "The acceptance letter says: " << endl << endl;

/*----------------------------------- Encoder/Decoder Prompt ------------------------- */

  lock = 2; // lock set to prevent certain functions till after conditions are met
  val = -2; // set to negative for decoder mode to activate
  msg = "Eqpitcvwncvkqpu! Vjg Quect Cecfgoa qh Ocike ku vjtknngf vq kphqto aqw vjcv aqw jcxg dggp cfokvvgf vq qwt rtguvkikqwu kpuvkvwvkqp. Aqwt jctf yqtm, vcngpv, cpf rcuukqp hqt ocike jcxg gctpgf aqw c rnceg coqpi vjg pgzv igpgtcvkqp qh vjg yqtnf'u itgcvguv ykbctfu. Kp cffkvkqp vq vjg 8 ycpfu tgswktgf hqt vjg qrgpkpi yggm, yg yqwnf nkmg vq tgokpf aqw vq cnuq dtkpi c ecogn ykvj aqw cu c ocikecn etgcvwtg rgv. Vjku ku c pgy tgswktgogpv hqt cnn uvwfgpvu, cu ecognu ctg mpqyp hqt vjgkt cdknkva vq vtcxgtug gxgp vjg jctujguv qh vgttckpu, ocmkpi vjgo rgthgev eqorcpkqpu hqt cpa aqwpi ykbctf qp vjg iq. Rngcug pqvg vjcv vjg vwkvkqp hgg ku pqy hkzgf cv $50,000 rgt ugoguvgt hqt cnn uvwfgpvu fwg vq kphncvkqp. Vjku kpxguvogpv kp aqwt gfwecvkqp cpf vtckpkpi yknn ugv aqw wr hqt c nkhgvkog qh ocikecn uweeguu. Yg nqqm hqtyctf vq ygneqokpi aqw vq vjg cecfgoa cpf jgnrkpi aqw wpnqem aqwt hwnn rqvgpvkcn. Ygnn fqpg!";
  do {
	if(lock == 1){ // checks if program has already decoded first message
		do {
			cout << "Do you want to encrypt or decrypt a message? (e/d) " << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // prevents multiple characters from breaking case check (e.g. user inputs "usdjfd" and system picks up d for decoding)
			cin >> option;
			switch(option){
				case 'e': // enables future messages to be written as encoding
					choice = "encoded";
					choice2 = "Encrypted message: ";
					error = 0;
					break;
				case 'd': // enables future messages to be written as decoding
					choice = "decoded";
					choice2 = "Decrypted message: ";
					error = 0;
					break;
				default: // system could not find correct input
					cout << "Error: invalid input, try again" << endl;
					error = 1;
			}
		}while(error == 1); // repeats if error detected
		cout << "Enter the message to be " << choice << ": " << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // resets input again for message to prevent any problems
		getline(cin, msg);
		do {
			cout << "Enter the shift value (0-200): " << endl;
			cin >> val;
			if (-200 > val || 200 < val){ // checks if shift value is between -200 and 200 inclusive
				cout << "Error: invalid input, try again" << endl;
				error = 1;
			}
			else{
				error = 0;
			}
		}while(error == 1); // repeats if shift value not in correct range
		if(option == 'd'){ // sets shift value to negative of original value if decoding is chosen
			val = -val;
		}
	}
	cout << choice2; // sends message based on coder picked
/*---------------------------------- Decoder/Encoder Function ------------------------------------------------ */
	for(int i = 0; i < static_cast<int>(msg.length()); i++){ //repeats function for every character in message
		if(isalpha(msg[i])){ //checks if character is a letter
			if(isupper(msg[i])){ // checks if character is uppercase
				if(static_cast<int>(msg[i] + val) > 90){ // checks if decoder goes over range
					cout << static_cast<char>((msg[i]+val)-(26*(((msg[i]+val)-90)/26)));// adjust output based on amount gone over
				}
				else if(static_cast<int>(msg[i] + val) < 65){
					cout << static_cast<char>((msg[i] + val) - (26*(((msg[i]+val)-90)/26)));//adjust output based on amount gone under
				}
				else{
					cout << static_cast<char>(msg[i] + val);//if amount correct then no adjustment
				}
			}
			else if(islower(msg[i])){
				if(static_cast<int>(msg[i] + val) > 122){//checks if amount goes over range
					cout << static_cast<char>((msg[i] + val) - (26*(((msg[i]+val)-97)/26)));//adjust output based on amount gone over
				}
				else if(static_cast<int>(msg[i] + val) < 97){//check if amount goes under range
					cout << static_cast<char>((msg[i] + val) - (26*(((msg[i]+val)-122)/26)));//adjust output based on amount gone under
				}
				else{
					cout << static_cast<char>(msg[i] + val);//if amount correct then no adjustment
				}
			}
		}
		else{
			cout << msg[i];//prints non alphabetical characters
		}
	}
	if (lock == 2){ // makes sure it's still first segment
		cout << "Now, let's start encoding and decoding some messages!" << endl << endl;
	  	lock = 1; //enables decoder for free use
	}
/*------------------------------------------ Repeater ----------------------------------------------*/
	do {
		cout << "Would you like to continue the program? (y/n): " << endl;
		cin >> repeater;//ask if user would like to repeat
		if(repeater == 'y' || repeater == 'n'){//ensures user doesn't submit invalid input
			error = 0;
		}
		else{
			cout << "Error: Invalid input, try again" << endl;
			error = 1;
		}
	}while(error == 1);//repeats if invalid input
  }while(repeater == 'y');//repeats if user says yes
  return 0;
  }
