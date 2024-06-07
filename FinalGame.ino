/*////////////////////////////////////////////////////////////////////////////////////////////////////////

Caleb Mikeska -- Final Project -- Memory Game

░░░░░░░░░▄██████████▄▄░░░░░░░░
░░░░░░▄█████████████████▄░░░░░
░░░░░██▀▀▀▀▀▀▀▀▀▀▀████████░░░░
░░░░██░░░░░░░░░░░░░░███████░░░
░░░██░░░░░░░░░░░░░░░████████░░
░░░█▀░░░░░░░░░░░░░░░▀███████░░
░░░█▄▄██▄░░░▀█████▄░░▀██████░░
░░░█▀███▄▀░░░▄██▄▄█▀░░░█████▄░
░░░█░░▀▀█░░░░░▀▀░░░▀░░░██░░▀▄█
░░░█░░░█░░░▄░░░░░░░░░░░░░██░██
░░░█░░█▄▄▄▄█▄▀▄░░░░░░░░░▄▄█▄█░
░░░█░░█▄▄▄▄▄▄░▀▄░░░░░░░░▄░▀█░░
░░░█░█▄████▀██▄▀░░░░░░░█░▀▀░░░
░░░░██▀░▄▄▄▄░░░▄▀░░░░▄▀█░░░░░░
░░░░░█▄▀░░░░▀█▀█▀░▄▄▀░▄▀░░░░░░
░░░░░▀▄░░░░░░░░▄▄▀░░░░█░░░░░░░
░░░░░▄██▀▀▀▀▀▀▀░░░░░░░█▄░░░░░░
░░▄▄▀░░░▀▄░░░░░░░░░░▄▀░▀▀▄░░░░
▄▀▀░░░░░░░█▄░░░░░░▄▀░░░░░░█▄░░
█░░░░░░░░░░░░░░░░░░░░░░░░░░▀█▄
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
//Random Obama face lol

//////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include <Adafruit_CircuitPlayground.h>
double ten; double nine; double six; double three; double two; double one; double zero; // creating initial capacitance storing variables
int number; bool newRound; int Round; const byte lbuttonPin = 4; const byte rbuttonPin = 5; // more misc variables for rounds, numbers, array location, and booleans
int value = 0; //The input value from the player at each action
int location = 0; //The location in the array that we are comparing the input to
bool playing = false; //A "safeguard"  variable, keeps things working smoothly and prevents weird bugs from things like super-fast reading
bool readable = false; // Another safeguard variable
bool intflag = 0; //for the button control, is used the same as the capacitance readings for the others

void setup() {
  Serial.begin(9600); while(!Serial); CircuitPlayground.begin(); // begin playground and open serial monitor
  newRound = true; //set the mode to newRound and start at round 1
  Round = 1;
  attachInterrupt(digitalPinToInterrupt(rbuttonPin), press, RISING); // create the interrupt for the right button
  //attachInterrupt(digitalPinToInterrupt(lbuttonPin), press, RISING);
}

void loop() {
  //Serial.println(location); Serial.println(value); // just for debugging purposes
  int sequence1[5] = {1, 2, 4, 3, 5}; //round 1
  int sequence2[7] = {2,4,2,3,2,4,1}; //round 2
  int sequence3[9] = {1,2,3,4,1,2,5,4,3}; //round 3
  ten =  CircuitPlayground.readCap(10); nine = CircuitPlayground.readCap(9); six = CircuitPlayground.readCap(6); three = CircuitPlayground.readCap(3); two = CircuitPlayground.readCap(2); zero = CircuitPlayground.readCap(0); one = CircuitPlayground.readCap(1);
//Line 51 records all the capacitance values from the pins around the board
  if (intflag) {value = 5; delay(200); intflag = 0;} //Reads if the button is pressed, and if so sets value = 5 and intflag back off
  if (ten < 100 || ten > 500 || nine < 100 || nine > 500) {CircuitPlayground.setPixelColor(8, 0,0,255); playing = true;value = 4; readable = false;delay(200);} else CircuitPlayground.setPixelColor(8, 0,0,0); readable = true;
  if (six < 100 || six > 500) {CircuitPlayground.setPixelColor(6, 255,0,0); playing = true; value = 3;  readable = false;delay(200);} else CircuitPlayground.setPixelColor(6, 0,0,0);readable = true;
  if (two < 100 || two > 500 || three < 100 || three > 500) {CircuitPlayground.setPixelColor(1, 0,255,0); playing = true;  value = 1; readable = false; delay(200);}  else CircuitPlayground.setPixelColor(1, 0,0,0);readable = true;
  if (zero < 100 || zero > 500 || one < 100 || one > 500) {CircuitPlayground.setPixelColor(3, 200,0,200); playing = true; value = 2;  readable = false;delay(200);}  else CircuitPlayground.setPixelColor(3, 0,0,0);readable = true;
//The lines above this are what actually read the input, and they determine if the player is touching one of the pins, and then sets the corresponding value and plays the light

  if(Round == 1) {
    if (newRound == true) {  //This chunk basically starts round 1, and checks to see if everything else is in order before beginning the game
      Round1();
      newRound = false;
    }

            //This first chunk compares the first value in round 1 sequence to the first player input
    if (location == 0 && value == sequence1[0] && playing == true && readable == true) {
      location = 1;
      value = 200;
    } 
    if (location == 0 && value != sequence1[0] && value != 200 && playing == true && readable == true) { // this plays when the player messed up!
      location = 10; Restart();
    } 
          //Does the same as the previous chunk except for the next value in the array sequence
    if (location == 1 && value == sequence1[1] && playing == true&& readable == true) {
      location = 2;
      value = 200;
    } 
    if (location == 1 && value != sequence1[1]&& value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
        //Does the same as the previous chunk except for the next value in the array sequence
    if (location == 2 && value == sequence1[2] && playing == true&& readable == true) {
      location = 3; value = 200;
    } 
    if (location == 2 && value != sequence1[2]&& value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
        //Does the same as the previous chunk except for the next value in the array sequence
    if (location == 3 && value == sequence1[3] && playing == true&& readable == true) {
      location = 4; value = 200;
    } 
    if (location == 3 && value != sequence1[3]&& value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
        //This one determines the end of the round, resets the necessary variables, then starts allows round 2
    if (location == 4 && value == sequence1[4] && playing == true&& readable == true) {
      location = 0; value = 200; playing = false; Round = 2; newRound = true;  CircuitPlayground.clearPixels(); value = 0; delay(2000);
    } 
    if (location == 4 && value != sequence1[4]&& value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
    
  }

  if(Round == 2) {            //This chunk checks that it is round 2, then runs the round 2 function
    if (newRound == true) {
      Round2();
      newRound = false;
    }
                              //This first chunk compares the first value in round 2 sequence to the first player input
    if (location == 0 && value == sequence2[0] && playing == true&& readable == true) {
      location = 1;
      value = 200;
    } 
    if (location == 0 && value != sequence2[0] && value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10; Restart();
    } 
//Does the same as the previous chunk except for the next value in the array sequence
    if (location == 1 && value == sequence2[1] && playing == true&& readable == true) {
      location = 2;
      value = 200;
    } 
    if (location == 1 && value != sequence2[1]&& value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
//Does the same as the previous chunk except for the next value in the array sequence
    if (location == 2 && value == sequence2[2] && playing == true&& readable == true) {
      location = 3; value = 200;
    } 
    if (location == 2 && value != sequence2[2] && value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
//Does the same as the previous chunk except for the next value in the array sequence
    if (location == 3 && value == sequence2[3] && playing == true&& readable == true) {
      location = 4; value = 200;
    } 
    if (location == 3 && value != sequence2[3]&& value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
//Does the same as the previous chunk except for the next value in the array sequence
    if (location == 4 && value == sequence2[4] && playing == true&& readable == true) {
      location = 5; value = 200;
    } 
    if (location == 4 && value != sequence2[4]&& value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
    //Does the same as the previous chunk except for the next value in the array sequence
    if (location == 5 && value == sequence2[5] && playing == true&& readable == true) {
      location = 6; value = 200;
    } 
    if (location == 5 && value != sequence2[5]&& value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
//Does the same as the previous chunk except for the next value in the array sequence
    if (location == 6 && value == sequence2[6] && playing == true&& readable == true) { //the same as the end of round 2, it resets variables and then allows round 3 to take place
      location = 0; value = 200; playing = false; Round = 3; newRound = true;  CircuitPlayground.clearPixels(); value = 0; delay(2000);
    } 
    if (location == 6 && value != sequence2[6]&& value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
  }

  if(Round == 3) {         //This chunk checks that it is round 3, then runs the round 3 function
    if (newRound == true) {
      Round3();
      newRound = false;
    }
                              //This first chunk compares the first value in round 3 sequence to the first player input
    if (location == 0 && value == sequence3[0] && playing == true&& readable == true) {
      location = 1;
      value = 200;
    } 
    if (location == 0 && value != sequence3[0] && value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10; Restart();
    } 
//Does the same as the previous chunk except for the next value in the array sequence
    if (location == 1 && value == sequence3[1] && playing == true&& readable == true) {
      location = 2;
      value = 200;
    } 
    if (location == 1 && value != sequence3[1]&& value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
//Does the same as the previous chunk except for the next value in the array sequence
    if (location == 2 && value == sequence3[2] && playing == true&& readable == true) {
      location = 3; value = 200;
    } 
    if (location == 2 && value != sequence3[2] && value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
//Does the same as the previous chunk except for the next value in the array sequence
    if (location == 3 && value == sequence3[3] && playing == true&& readable == true) {
      location = 4; value = 200;
    } 
    if (location == 3 && value != sequence3[3]&& value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
//Does the same as the previous chunk except for the next value in the array sequence
    if (location == 4 && value == sequence3[4] && playing == true&& readable == true) {
      location = 5; value = 200;
    } 
    if (location == 4 && value != sequence3[4]&& value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
    //Does the same as the previous chunk except for the next value in the array sequence
    if (location == 5 && value == sequence3[5] && playing == true&& readable == true) {
      location = 6; value = 200;
    } 
    if (location == 5 && value != sequence3[5]&& value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
    //Does the same as the previous chunk except for the next value in the array sequence
    if (location == 6 && value == sequence3[6] && playing == true&& readable == true) {
      location = 7; value = 200;
    } 
    if (location == 6 && value != sequence3[6]&& value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
    //Does the same as the previous chunk except for the next value in the array sequence
    if (location == 7 && value == sequence3[7] && playing == true&& readable == true) {
      location = 8; value = 200;
    } 
    if (location == 7 && value != sequence3[7]&& value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 

    if (location == 8 && value == sequence3[8] && playing == true&& readable == true) {
      location = 0; value = 200; playing = false; Round = 1; newRound = true;  CircuitPlayground.clearPixels(); value = 0;  Win();
    } 
    if (location == 8 && value != sequence3[8]&& value != 200 && playing == true&& readable == true) { // this plays when the player messed up!
      location = 10;Restart();
    } 
}
value = 200; // kind of a tricky thing, but this is like a holding status for the value variable, so that it doesnt trip the restarts on the if statements.
intflag = 0;
}
//This is the Round 1 display sequence, and it basically takes the sequence numbers and fires the corresponding display function
void Round1() {
  value = 200;
  int sequence1[5] = {1, 2, 4, 3, 5};
  if (sequence1[0] == 1) Fire1(500); if (sequence1[0] == 2) Fire3(500); if (sequence1[0] == 3) Fire6(500); if (sequence1[0] == 4) Fire8(500); if (sequence1[0] == 5) FireTone(500);
   if (sequence1[1] == 1) Fire1(500); if (sequence1[1] == 2) Fire3(500); if (sequence1[1] == 3) Fire6(500); if (sequence1[1] == 4) Fire8(500); if (sequence1[1] == 5) FireTone(500);
    if (sequence1[2] == 1) Fire1(500); if (sequence1[2] == 2) Fire3(500); if (sequence1[2] == 3) Fire6(500); if (sequence1[2] == 4) Fire8(500); if (sequence1[2] == 5) FireTone(500);
     if (sequence1[3] == 1) Fire1(500); if (sequence1[3] == 2) Fire3(500); if (sequence1[3] == 3) Fire6(500); if (sequence1[3] == 4) Fire8(500); if (sequence1[3] == 5) FireTone(500);
      if (sequence1[4] == 1) Fire1(500); if (sequence1[4] == 2) Fire3(500); if (sequence1[4] == 3) Fire6(500); if (sequence1[4] == 4) Fire8(500); if (sequence1[4] == 5) FireTone(500);
}
//This is the Round 2 display sequence, and it basically takes the sequence numbers and fires the corresponding display function
void Round2() {
  value = 200;
  int sequence2[7] = {2,4,2,3,2,4,1};
  if (sequence2[0] == 1) Fire1(500); if (sequence2[0] == 2) Fire3(500); if (sequence2[0] == 3) Fire6(500); if (sequence2[0] == 4) Fire8(500); if (sequence2[0] == 5) FireTone(500);
   if (sequence2[1] == 1) Fire1(500); if (sequence2[1] == 2) Fire3(500); if (sequence2[1] == 3) Fire6(500); if (sequence2[1] == 4) Fire8(500); if (sequence2[1] == 5) FireTone(500);
    if (sequence2[2] == 1) Fire1(500); if (sequence2[2] == 2) Fire3(500); if (sequence2[2] == 3) Fire6(500); if (sequence2[2] == 4) Fire8(500); if (sequence2[2] == 5) FireTone(500);
     if (sequence2[3] == 1) Fire1(500); if (sequence2[3] == 2) Fire3(500); if (sequence2[3] == 3) Fire6(500); if (sequence2[3] == 4) Fire8(500); if (sequence2[3] == 5) FireTone(500);
      if (sequence2[4] == 1) Fire1(500); if (sequence2[4] == 2) Fire3(500); if (sequence2[4] == 3) Fire6(500); if (sequence2[4] == 4) Fire8(500); if (sequence2[4] == 5) FireTone(500);
        if (sequence2[5] == 1) Fire1(500); if (sequence2[5] == 2) Fire3(500); if (sequence2[5] == 3) Fire6(500); if (sequence2[5] == 4) Fire8(500); if (sequence2[5] == 5) FireTone(500);
          if (sequence2[6] == 1) Fire1(500); if (sequence2[6] == 2) Fire3(500); if (sequence2[6] == 3) Fire6(500); if (sequence2[6] == 4) Fire8(500); if (sequence2[6] == 5) FireTone(500);
}
//This is the Round 2 display sequence, and it basically takes the sequence numbers and fires the corresponding display function
void Round3() {
  value = 200;
  int sequence3[9] = {1,2,3,4,1,2,5,4,3};
  if (sequence3[0] == 1) Fire1(500); if (sequence3[0] == 2) Fire3(500); if (sequence3[0] == 3) Fire6(500); if (sequence3[0] == 4) Fire8(500); if (sequence3[0] == 5) FireTone(500);
   if (sequence3[1] == 1) Fire1(500); if (sequence3[1] == 2) Fire3(500); if (sequence3[1] == 3) Fire6(500); if (sequence3[1] == 4) Fire8(500); if (sequence3[1] == 5) FireTone(500);
    if (sequence3[2] == 1) Fire1(500); if (sequence3[2] == 2) Fire3(500); if (sequence3[2] == 3) Fire6(500); if (sequence3[2] == 4) Fire8(500); if (sequence3[2] == 5) FireTone(500);
     if (sequence3[3] == 1) Fire1(500); if (sequence3[3] == 2) Fire3(500); if (sequence3[3] == 3) Fire6(500); if (sequence3[3] == 4) Fire8(500); if (sequence3[3] == 5) FireTone(500);
      if (sequence3[4] == 1) Fire1(500); if (sequence3[4] == 2) Fire3(500); if (sequence3[4] == 3) Fire6(500); if (sequence3[4] == 4) Fire8(500); if (sequence3[4] == 5) FireTone(500);
        if (sequence3[5] == 1) Fire1(500); if (sequence3[5] == 2) Fire3(500); if (sequence3[5] == 3) Fire6(500); if (sequence3[5] == 4) Fire8(500); if (sequence3[5] == 5) FireTone(500);
          if (sequence3[6] == 1) Fire1(500); if (sequence3[6] == 2) Fire3(500); if (sequence3[6] == 3) Fire6(500); if (sequence3[6] == 4) Fire8(500); if (sequence3[6] == 5) FireTone(500);
           if (sequence3[7] == 1) Fire1(500); if (sequence3[7] == 2) Fire3(500); if (sequence3[7] == 3) Fire6(500); if (sequence3[7] == 4) Fire8(500); if (sequence3[7] == 5) FireTone(500);
              if (sequence3[8] == 1) Fire1(500); if (sequence3[8] == 2) Fire3(500); if (sequence3[8] == 3) Fire6(500); if (sequence3[8] == 4) Fire8(500); if (sequence3[8] == 5) FireTone(500);
}
//Fire NeoPixel 8
void Fire8(int time) {
  CircuitPlayground.setPixelColor(8, 0,0,255); delay(time + 500); CircuitPlayground.setPixelColor(8, 0,0,0);
}
//Fire NeoPixel 6
void Fire6(int time) {
CircuitPlayground.setPixelColor(6, 255,0,0); delay(time + 500); CircuitPlayground.setPixelColor(6, 0,0,0);
}
//Fire NeoPixel 1
void Fire1(int time) {
CircuitPlayground.setPixelColor(1, 0,255,0); delay(time + 500); CircuitPlayground.setPixelColor(1, 0,0,0);
}
//Fire NeoPixel 3
void Fire3(int time) {
CircuitPlayground.setPixelColor(3, 200,0,200); delay(time + 500); CircuitPlayground.setPixelColor(3, 0,0,0);
}
//Plays the sound tone
void FireTone(int time) {
  CircuitPlayground.playTone(300,200);
}
//The restart function, which turns all the lights red, plays a sad song, and then resets all variables and restarts the entire game
void Restart() {
  delay(500);
  for(int i=0; i<10; ++i) {
 CircuitPlayground.setPixelColor(i, 255,0,0); //sets all pixels to red
 delay(50);
  }
  CircuitPlayground.playTone(700,400);
  CircuitPlayground.playTone(500,400);//plays the "sad" song
  CircuitPlayground.playTone(300,400);
  delay(3000);
    Round = 1;
    newRound = true;
    location = 0;//resets all variables
    value = 0;
    playing = false;
    CircuitPlayground.clearPixels();//clears the neopixels
    delay(3000);
}
//Oddly similar to the restart function, just happier...
void Win() {
  for(int i=0; i<10; ++i) {
 CircuitPlayground.setPixelColor(i, 0,0,255);//sets all pixels to blue
 delay(50);
  }
    CircuitPlayground.playTone(300,200);
    CircuitPlayground.playTone(500,200); //plays the "victory" song
    CircuitPlayground.playTone(700,300);
    delay(3000);
    Round = 1;
    newRound = true;
    location = 0; //resets all variables
    value = 0;
    playing = false;
    CircuitPlayground.clearPixels(); //clears the neopixels
    delay(2000);
}
//interrupt of when the button is pressed, similar to touching one of the capacitance sensors.
void press(){
  intflag = 1;
  CircuitPlayground.playTone(300,200);
}

//The End!