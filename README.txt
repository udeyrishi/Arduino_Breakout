Breakout for Arduino

Created by:- Udey Rishi & Aaron Plamondon

Disclaimer: This game is inspired from Atari's original classic arcade game. Our
intention is not infringing any copyrights that they might have. This is just a
for fun project. Imitation is a form of flattery :-) This project was created as
a CMPUT 274 course (University of Alberta) final project.

Assumptions: This assumes that all the default arduino libraries are set up as
instructed on this University of Alberta webpage http://ugweb.cs.ualberta.ca/~c274/web/VM/index.htm 
All other additions are mentioned in the game files. 

For details regarding parts used, see http://ugweb.cs.ualberta.ca/~c274/web/Kit-V2/PartsList.txt
(Not all of these parts are used for this specific project).
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
Game Instructions:
Play the game by moving the paddle at the bottom of the screen and trying to break all of the blocks. The game is controlled by the joystick moving it left and right and pushing it in to elect a mode or pause the game.

Pin setup:-
Do not connect anything to pin A7 or the game will not properly generate random bricks.

LCD Screen:

1 GND to BB GND bus
2 VCC to BB positive bus
3 RESET to Pin 8
4 D/C (Data/Command) to Pin 7
5 CARD_CS (Card Chip Select) to Pin 5
6 TFT_CS (TFT/screen Chip Select) to Pin 6
7 MOSI (Master Out Slave In) to Pin 51
8 SCK (Clock) to Pin 52
9 MISO (Master In Slave Out) to 50
10 LITE (Backlite) to BB positive bus 

Joystick:

1 VCC to BB positive bus
2 VERT to Pin A0
3 HOR to Pin A1
4 SEL to Pin 9
5 GND to BB GND bus 

Speaker:

1 VCC to BB positive bus
2 Speaker Output to Pin 2

Tips:
Have Something to help anchor down the joystick so it does not move around.
