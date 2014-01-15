// Made by Udey Rishi & Aaron Plamondon

#include <Arduino.h> // Standard Arduino library
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h> 
#include "game_header.h" // Game specific library

extern Adafruit_ST7735 tft; // Contains tft info. Defined in project_head.cpp 

// Global variables:
int score; //  Current round's score
int lives; // Total lives left
int old_score; // Cumulative score upto previous round
//Total score = old_score + score

void setup() {
    Serial.begin(9600);
    tft.initR(INITR_BLACKTAB);
    randomSeed(analogRead(7)); // Seed for all random functions

    // Detects resting values of joystick and calibrates it        
    int16_t vRest = v_calibrate_joystick();
    int16_t hRest = h_calibrate_joystick();
    
    // SEL is used for starting (from main menu), pausing and resuming game   
    pinMode(SEL,INPUT);
    digitalWrite(SEL,HIGH);
    
    // Speaker output
    pinMode(SPEAKER_PIN, OUTPUT);
    
    int menu_option; // Records the menu option chosen - play game (1) or highscores (2)
    int win = 0; // Tracks if the last round was won, = 0 if lost, = 1 if won
    int round;    
    while(1) {
        if (win == 0) { // Resetting will be skipped if last round was won. Game progress will be retained. 
            // Reset everything if lost a round and go back to main menu
            old_score = 0;
            score = 0;
            lives = 5;
            round = 1;
            menu_option = menu(vRest); // Run the main menu and return the menu option chosen
        }
        
        if (menu_option == 1) { // Load the game
               brick_info* bricks = environment_draw(); // Draws bricks and returns a pointer to array containg their info
               scoreboard(); // Launch the top scoreboard bar / notification bar
               win = play_game(bricks, hRest, round); // Run the game. Returns 0 or 1 if round was lost or won respectively
            
            if (win == 1) round++;
            if (round > 500) win = 0; // End game if 500 rounds are won (I dare the player! ;-) )
        }
        
        else if (menu_option == 2) { // Launch the list of high scores
            high_scores();
        }
    }
}

void loop () {}
