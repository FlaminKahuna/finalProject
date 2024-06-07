# finalProject

Game Description:
	This game is a memory game, and basically it will involve the LEDs lighting and sounds playing in a certain pattern, and then having the player replicate the pattern by touching the corresponding capacitance nodes and pressing a button. The game will start with an easy pattern, only 5 lights/sound, and then every round the length of the pattern will increase. 

Game Rules: 
	An initial pattern will play, and then then player will have to replicate it. To mimic the LED, the player will touch the closest capacitance sensor, and to input the sound the player will press the right button on the Playground board. After every correct round, the pattern will get increasingly more difficult. Inputting an incorrect value will end the game, and the lights and board will reset. Once the player has successfully completed all 3 rounds, the game will play a short win light pattern and sound, and then reset to the start.
 
How to Input:
	The most effective way to play the game is by holding(or taping) the board flat against a desk or table. Then, while playing, inputs can be registered with a quick tap to the capacitance sensors or a quick press of the button. Doing this will reduce the amount of accidental inputs and the overall stability of the game.
 
Inputs:
	Capacitance readings from the sensors on the perimeter of the board(except A0). When touching the sensors with your hand they will change to a value of 0, and when they do this the computer will know that the player is touching the respective sensor. The usual value for these is around 200-250, and anything that escapes that threshold will read as an input.
	Button Press(to mimic a sound). Button press has no thresholds and is simply recorded when the button rising function.
