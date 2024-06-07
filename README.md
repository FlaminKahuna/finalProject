# finalProject
finalProject
## Game Description:
	This game is a memory game, and basically it will involve the LEDs lighting and sounds playing in a certain pattern, and then having the player replicate the pattern by touching the corresponding capacitance nodes and pressing a button. The game will start with an easy pattern, like only 3 lights, and then keep increasing in both length of the pattern and the speed. Points can be calculated at the end of each “round” by seeing how far you got and how long was the longest pattern you could replicate. 

Game Rules: 
	The initial pattern will play, and then then player will have to replicate it. To mimic the LED, the player will touch the closest capacitance sensor, and to input the sound the player will press one of the two buttons. After every correct round, the pattern will get increasingly more difficult until the player does it incorrectly. Then, the board will announce the score(based on how many rounds you did), and then it will reset to the start.

Inputs:
	Capacitance readings from the sensors on the perimeter of the board(except A0). When touching the sensors with your hand they will change to a value of 0, and when they do this the computer will know that the player is touching the respective sensor. The usual value for these is around 200-250, and anything that escapes that threshold will read as an input.
	Button Press(to mimic a sound). This has no thresholds and is simply recorded when the button rising function.

