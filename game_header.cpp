// Made by Udey Rishi & Aaron Plamondon 

#include <Arduino.h>
#include "game_header.h"

extern Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
extern int score; // Current score
extern int lives; // Lives left
extern int old_score; // Previous round's score

// Environment functions:
brick_info* environment_draw() {
    tft.fillScreen(ST7735_WHITE);
   
    // Total number of bricks to be displayed and amount of each type.
    int brick_ttl = BRICK_NUMBER;
    int colour_brick_ttl[3] = {8, 7, 5}; // Green, Blue, Red, Black respectively

    // Position to print the bricks on the screen.
    int brick_position_x = 0;
    int brick_position_y = 9; // Top 9 pixels left for scoreboard
    
    // Used to store the brick information.
    uint8_t brick_info_counter = 0;
    static brick_info bpointer[BRICK_NUMBER];

    while(brick_ttl) {
        // The bricks to be printed of each colour
        int colour_brick_print[3] = {0, 0, 0}; // Green, Blue, Red, Black respectively
        int brick_1 = 0;
        int brick_2 = 0;

        // Randomly chooses a number of bricks to be printed on one line.
        if (brick_ttl < 4) {
            brick_1 = brick_ttl;
        } 
        else {
            brick_1 = random(1,4);
        }
        brick_2 = brick_1;
        // Changes the total number of bricks left.
        brick_ttl = brick_ttl - brick_1;
        // Chooses which bricks are which colour.
        while (brick_1) {
        // Randomly chooses a number which corresponds each block.
            int random_num = random(0,255) % 3;
    
            if (colour_brick_ttl[random_num] > 0) {
                colour_brick_print[random_num]++;
                colour_brick_ttl[random_num]--;
                brick_1--;
            }
        }

        int position_array[4] = {0, 1, 2, 3};
        int start_2 = 0;
        // Randomly chooses one of four positions to print block;
        while (brick_2) {
	    // Random Position in the below array
            int end_2 = 4;
            int random_num = random(start_2, end_2);

            // Chooses the position number and swaps it so its not repeated
            int position_num;
            int temp;

            temp = position_array[start_2];
            position_array[start_2] = position_array[random_num];
            position_array[random_num] = temp;

            // Increase the starting positon so no overwriting of blocks occurs
            start_2++;

            // Alocates the brick position for the LCD screen
            brick_position_x = (position_array[start_2 - 1])*32;
            
            int check = 1;
            while(check) {
                int random_num_draw = random(0,255) % 3;
                if (colour_brick_print[random_num_draw] > 0) {
                    // Draws bricks.
                    bpointer[brick_info_counter].brick_colour = random_num_draw;
                    bpointer[brick_info_counter].brick_location_x = brick_position_x;
                    bpointer[brick_info_counter].brick_location_y = brick_position_y;
                    brick_draw(bpointer[brick_info_counter]);
                    colour_brick_print[random_num_draw]--;
                    brick_2--;
                    brick_info_counter++;
                    check = 0;
                } 
            } 
        }
        // Shifts to the next row.
        brick_position_y = brick_position_y + BRICK_BORDER_Y;    
    }
    return bpointer;
}

void brick_draw(brick_info brick) {
    uint16_t colour_border = 0x0000;
    uint16_t colour;
    
    if (brick.brick_colour == 0) {
        colour = 0x07E0; // Green
    }
    
    else if (brick.brick_colour == 1) {
        colour = 0x001F; // Blue
    }
    
    else if (brick.brick_colour == 2) {
        colour = 0xF800; // Red
    }
    
    /*
    else if (brick.brick_colour == 3) {
        colour = 0x0000; // Black invincible bricks
        colour_border = 0x0000;
    }*/
    
    else if (brick.brick_colour == -1) {
        colour = 0xFFFF; // Invisible
        colour_border = 0xFFFF;
    }    
    
    // Border    
    tft.fillRect(brick.brick_location_x,brick.brick_location_y,BRICK_BORDER_X,BRICK_BORDER_Y,colour_border);
    // Middle Rectangle
    tft.fillRect(brick.brick_location_x+2,brick.brick_location_y+2,BRICK_SIZE_X,BRICK_SIZE_Y,colour);
}

void high_scores () {
    // High score display. Under development
    tft.fillScreen(ST7735_CYAN);

    tft.setTextSize(1);
    tft.setCursor(2,10);
    tft.println("In developement");

    // Enter menu mode.
    while(1) {
        int select = digitalRead(SEL);
        if (select == 0) {
            delay(100);
            break;
        }
    }
}

void menu_option1 () { // First menu option
    tft.setCursor(32, 78);
    tft.setTextColor(ST7735_MAGENTA);
    tft.setTextSize(1);
    tft.println("Start Game");
}

void menu_option2 () { // Second menu option
    tft.setCursor(30, 95);
    tft.setTextColor(ST7735_MAGENTA);
    tft.setTextSize(1);
    tft.println("High Scores");
}

void menu_bricks() { // Displays the brick design on the menu screen
    // Draws three bricks on the top
    brick_info bricks[6];
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 3; i++) {
            bricks[i+j*3].brick_location_x = 15 + i*32;     
            bricks[i+j*3].brick_location_y = 54 + j*61;
            if ((i+j*3) > 2) bricks[i+j*3].brick_colour = (i+j*3) - 3;
            else bricks[i+j*3].brick_colour = 2 - (i+j*3);
        }
    }
    for (int k = 0; k < 6; k++) {
        brick_draw(bricks[k]);
    }
} 

int menu(int16_t vRest) { // Menu Screen
    tft.fillScreen(ST7735_CYAN);

    // Prints Title
    tft.setCursor(12, 18);
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(2);
    tft.println("Breakout!");

    // Prints "Copyright info."
    tft.setTextColor(ST7735_BLACK);
    tft.setTextSize(1);
    tft.setCursor(40,130);
    tft.println("Made by");
    tft.setCursor(13,140);
    tft.println("Aaron Plamondon &");
    tft.setCursor(34,150);
    tft.println("Udey Rishi");

    // Prints menu options and background bricks.
    menu_option1();
    menu_option2();
    menu_bricks();

    // Select a Mode
    int menu_option = 1;
    int OFFSET = 50;
    int16_t vPlus = vRest + OFFSET;
    int16_t vMinus = vRest - OFFSET;

    while (1) {
        tft.fillRect(29, 75, 65, 13, ST7735_BLACK);
        menu_option1();
        while (menu_option == 1) {
            int select = digitalRead(SEL); 
            int16_t v = analogRead(VERT);
            if (v > vPlus) {
                menu_option = 2;
                tft.fillRect(29, 75, 65, 13, ST7735_CYAN);
                menu_option1();
            }
            if (select == 0) {
                delay(100);
                return menu_option;
            }
        }
        tft.fillRect(27, 92, 71, 13, ST7735_BLACK);
        menu_option2();
        playTone(5000, 50);
        while (menu_option == 2) {
            int select = digitalRead(SEL); 
            int16_t v = analogRead(VERT);
            if (v < vMinus) {
                menu_option = 1;
                tft.fillRect(27, 92, 71, 13, ST7735_CYAN);
                menu_option2();
            }
            if (select == 0) {
                delay(100);
                return menu_option;
            }
        }   
        playTone(5000, 50);
    }
}

void update_score() { // Updates the score on the scoreboard
    tft.setTextSize(1);
    tft.setTextColor(0x0000);
    tft.setCursor(100, 0);
    tft.print(old_score + score - 1);
    tft.setTextColor(0xFFFF);
    tft.setCursor(100, 0);
    tft.print(old_score + score);
}

void update_lives() { // Updates the remaining lives on the scoreboard
    tft.setTextSize(1);
    tft.setTextColor(0x0000);
    tft.setCursor(35, 0);
    tft.print(lives + 1);
    tft.setTextColor(0xFFFF);
    tft.setCursor(35, 0);
    tft.print(lives);
}

// Creates the basic framework of the scorboard/notification bar
void scoreboard() {
    tft.fillRect(0, 0, tft.width(), 9, ST7735_BLACK); // Score bar
    tft.setTextSize(1);
    tft.setTextColor(0xFFFF);
    tft.setCursor(0,0);
    tft.print("Lives: ");
    update_lives();
    tft.setCursor(60, 0);
    tft.print("Score: ");
    update_score();
}

void playTone(int period, int duration) {
    // elapsed time in microseconds, the long is needed to get
    // a big enough range.

    long elapsedTime = 0;

    // note we are making a slight error here if period is not even
    int  halfPeriod = period / 2;

    while (elapsedTime < duration * 1000L) {
        // generate a square wave of the given period.  Half the 
        // period is on, the other half is off.
        digitalWrite(SPEAKER_PIN, HIGH);
        delayMicroseconds(halfPeriod);

        digitalWrite(SPEAKER_PIN, LOW);
        delayMicroseconds(halfPeriod);

        // count the time we just consumed for one cycle of the tone
        elapsedTime = elapsedTime + period;
    }

}

// Physics functions:
void reset_platform(platform_stats *platform) { // Resets platform to original state
    platform->x_coord = tft.width()/2 - 1;
    platform->y_coord = tft.height() - 3;
    platform->length = tft.width()/4;
    platform->width = 2; 
    platform->vel = 0;
}

void reset_ball(ball_stats *ball, platform_stats *platform) { // Resets ball to original state
    ball->length = 3;
    ball->x_coord = platform->x_coord;
    ball->y_coord = platform->y_coord - 4*(ball->length) ;
    ball->x_vel = 1; 
    ball->y_vel = 1;
}

void draw_ball(ball_stats *ball) { // Draws ball using ball data
    tft.fillRect(ball->x_coord - (ball->length)/2, ball->y_coord - (ball->length)/2, ball->length, ball->length, ST7735_MAGENTA);   
}

void delete_ball(ball_stats *ball) { // Draws white ball (i.e., deletes old ball)
    tft.fillRect(ball->x_coord - (ball->length)/2, ball->y_coord - (ball->length)/2, ball->length, ball->length, ST7735_WHITE);
}
void draw_platform(platform_stats *platform) { // Draws platform using platform data
    tft.fillRect((platform->x_coord) - (platform->length)/2, (platform->y_coord) - (platform->width)/2, platform->length, platform->width, ST7735_BLACK);
}

void delete_platform(platform_stats *platform) { // Draws white platform (i.e., deletes old platform)
    tft.fillRect((platform->x_coord) - (platform->length)/2, (platform->y_coord) - (platform->width)/2, platform->length, platform->width, ST7735_WHITE);
}

void play_ball(ball_stats *ball, platform_stats *platform, brick_info* bricks) { //Controls ball motion 
    ball_stats temp = *ball;
    ball->x_coord = ball->x_coord + ball->x_vel; // Moves ball as per current velocity
    ball->y_coord = ball->y_coord + ball->y_vel;
    platform_bounce_check(ball, platform); // Checks and implements platform bounce
    wall_bounce_check(ball); // Checks and implements wall bounce
    brick_bounce_check(ball, bricks); // Checks and implements brick bounce
    delete_ball(&temp);
    draw_ball(ball);
}

void play_platform(platform_stats *platform, int16_t hRest) { // Controls platform motion
    int16_t max_left = -1*hRest; 
    int16_t max_right = 1012 - hRest;
    int16_t OFFSET = analogRead(HOR) - hRest;
    platform->vel = map(OFFSET, max_left, max_right, -4, 4); // Reads platform velocity from joystick and calibrated joystick position
    // -4 and 4 control platform sensitivity. Increase to increase the sensitivity
    
    if ((platform->x_coord + (platform->length)/2 < tft.width() -1 && platform->vel > 0) ||
        (platform->x_coord - (platform->length)/2 > 0 && platform->vel < 0)) { // Prevents movement of platform off screen
        delete_platform(platform);
        platform->x_coord = platform->x_coord + platform->vel;        
        draw_platform(platform);
    }
}

void platform_bounce_check(ball_stats *ball, platform_stats *platform) { // Checks for platform bounce
    if (ball->y_coord + (ball->length)/2 +1 == platform->y_coord - (platform->width)/2) {
        if (ball->x_coord + (ball->length)/2 >= platform->x_coord - 1 - (platform->length)/2) {
            if (ball->x_coord - (ball->length)/2 <= platform->x_coord + 1 + (platform->length)/2) {
                ball->y_vel = -1*(ball->y_vel); // Reflect
                playTone(3000, 50);
            }
        }
    }
    
    if (ball->x_vel == 0) ball->x_vel = 1; // To prevent exact vertical motion doesn't happen
}

void wall_bounce_check(ball_stats *ball) { // Checks for wall bounce
    if (ball->x_coord + (ball->length)/2  >= tft.width() - 1 || ball->x_coord - (ball->length)/2 <= 0) { // Left and right walls
        ball->x_vel = -1*ball->x_vel; // Reflect
        playTone(2000, 50); // Sound
    }

    if (ball->y_coord - (ball->length)/2 <= 9) { // Ceiling
        ball->y_vel = -1*ball->y_vel; // Reflect
        playTone(2000, 50); // Sound
    }    
}

void brick_bounce_check(ball_stats *ball, brick_info* bricks) { // Checks for brick bounce
    int i = 0;
    while (i < BRICK_NUMBER) { // Checks for all bricks
        int break_check = 0;
        if (bricks[i].brick_colour >= 0) { // Only if ball is not "invisible"
           if (bricks[i].brick_location_y + BRICK_BORDER_Y + 1 == ball->y_coord - (ball->length)/2) {
               if (ball->x_coord - (ball->length)/2 <= bricks[i].brick_location_x + BRICK_BORDER_X) {
                   if (ball->x_coord + (ball->length)/2 >= bricks[i].brick_location_x) {
                       // Bottom collision
                       playTone(5000, 50);
                       ball->y_vel = -1*(ball->y_vel);
                       break_check = 1;
                   }
               }
           }
           
           else if (bricks[i].brick_location_y - 1 == ball->y_coord + (ball->length)/2) {
               if (ball->x_coord -(ball->length)/2 <= bricks[i].brick_location_x + BRICK_BORDER_X) {
                   if (ball->x_coord + (ball->length)/2 >= bricks[i].brick_location_x) {
                       // Left edge collision
                       playTone(5000, 50);
                       ball->y_vel = -1*(ball->y_vel);
                       break_check = 1;
                   }
               }
           }
           
           else if (bricks[i].brick_location_x + BRICK_BORDER_X + 1 == ball->x_coord - (ball->length)/2) {
               if (ball->y_coord - (ball->length)/2 <= bricks[i].brick_location_y + BRICK_BORDER_Y ) {
                   if (ball->y_coord + (ball->length)/2 >= bricks[i].brick_location_y) {
                       // Right edge collision
                       playTone(5000, 50);
                       ball->x_vel = -1*(ball->x_vel);
                       break_check = 1;
                   }
               }
           }
           
           else if (bricks[i].brick_location_x - 1 == ball->x_coord + (ball->length)/2) {
               if (ball->y_coord -(ball->length)/2 <= bricks[i].brick_location_y + BRICK_BORDER_Y) {
                   if (ball->y_coord + (ball->length)/2 >= bricks[i].brick_location_y) {
                       // Left edge collision
                       playTone(5000, 50);
                       ball->x_vel = -1*(ball->x_vel);
                       break_check = 1;
                   }
               }
           }

            
        }        
    
        if (break_check == 1 && bricks[i].brick_colour > -1) {
            // Reduces bricks strength if brick is hit and brick is either green, blue or red.
            // Brick is destroyed (turned invisible) if it were green 
            bricks[i].brick_colour--;
            brick_draw(bricks[i]);   
            score++;
            update_score();            
            break;
        }
        i++;    
    }
}

int16_t h_calibrate_joystick() { // Calibrates joystick's horizontal motion
    delay(10); // Delays to let joystick settle down
    long joy_rest = 0;
    for (int i = 0; i < 50; i++) {
        joy_rest = joy_rest + analogRead(HOR);   
    }
    joy_rest = joy_rest/50; // Averages 50 analogReads to find avergae resting position
    return joy_rest;
}

int16_t v_calibrate_joystick() { // Calibrates joystick's vertical motion
    delay(10); // Delays to let joystick settle down
    long joy_rest = 0;
    for (int i = 0; i < 50; i++) {
        joy_rest = joy_rest + analogRead(VERT);   
    }
    joy_rest = joy_rest/50; // Averages 50 analogReads to find avergae resting position
    return joy_rest;
}

int play_game(brick_info* bricks, int16_t hRest, int round) {
    
    // Physics controller data
    ball_stats ball;
    platform_stats platform;

    // Resets platform
    reset_platform(&platform);
    
    // Draws platform to initiate game
    draw_platform(&platform);
    check_pause(1, &platform, hRest, 1); // Begin game in paused state but allows movement of platform

    reset_ball(&ball, &platform); // Resets ball wrt to platform location
    draw_ball(&ball); // Draws ball
    
    while(1) {
        check_pause(0, &platform, hRest, 0); // Check if pause button is pressed
        play_ball(&ball, &platform, bricks); // Initiate ball physics
        delayMicroseconds(500000 - 1000*round);; // Increases speed as round progresses! Max 500 rounds possible
        play_platform(&platform, hRest); // Inititate platform physics
        
        if (score == 37 && lives > 0) { // Won a round
            old_score = old_score + score;
            score = 0;
            tft.setTextWrap(true);
            tft.setTextSize(1);
            tft.setTextColor(0x0000);
            tft.fillScreen(0xFFFF);
            tft.setCursor(15, 60);
            if (round <= 500) {
                tft.print("You won the round!");
                tft.setCursor(14,80);
                tft.print("Let's increase the");
                tft.setCursor(50,90);
                tft.print("speed!");
            }
            
            else {
                tft.print("You won all rounds!");
            }
            tft.setCursor(20, 100);
            tft.print("Tap to continue!");
            while(digitalRead(SEL)) { // Wait till SEL is pressed again to continue
                delay(50);       
            }
            
            return 1; // Returns 1 to let parent function know that the user won in this round
        }
        
        if (lives > 1 && ball.y_coord + (ball.length)/2 >= tft.height() - 1) { // Lost a life
            playTone(10000, 50);
            lives--;
            update_lives();
            delete_ball(&ball);
            draw_platform(&platform);
            
            tft.setTextWrap(false);
            tft.setTextSize(1);
            tft.setTextColor(0xFFFF);
            tft.fillRect(0, 0, tft.width(), 9, ST7735_BLACK); // Blank bar
            tft.setCursor(0,0);
            tft.print(lives);
            tft.print(" life left!");
            delay(500);
            check_pause(1, &platform, hRest, 1);
            scoreboard(); // Prints scoreboard again when game is resumed
            
                        
            //reset_platform(&platform);
            reset_ball(&ball, &platform);
    
            draw_ball(&ball);
            draw_platform(&platform);    
            delay(100); // So that another button press is not picked up (to inititate pause)
        }
        
        else if (lives == 1 && ball.y_coord + (ball.length)/2 >= tft.height() - 1) { // Game Over 
            lives--;
            update_lives();
            tft.setTextWrap(false);
            tft.setTextSize(1);
            tft.setTextColor(0x0000);
            tft.fillScreen(0xFFFF);
            tft.setCursor(40, 70);
            tft.print("Game Over!");
            tft.setCursor(25, 80);
            // Display the final game result on the white screen
            tft.print("Final Score: ");
            tft.print(old_score + score);
            int time1 = millis();
            int time2;
            while(digitalRead(SEL)) { // Wait till SEL is pressed again to resume game
                delay(50);
                time2 = millis();
                if (time2 - time1 >= 3000) return 0;         
            }
            return 0; // Returns 1 to let parent function know that the user won in this round
        }
    }
}

void check_pause(int16_t initial, platform_stats *platform, int16_t hRest, int8_t platform_allow) {
    if ((!digitalRead(SEL)) || initial) { // Game Pause mechanism
        tft.fillRect(0,0,tft.width(),9,ST7735_BLACK);
        tft.setTextSize(1);
        tft.setTextColor(0xFFFF);
        tft.setCursor(0, 0);
        if (initial == 1) {
            tft.print("Tap to begin");
        }
        else {
            tft.print("Tap to resume");
        }
        delay(200);
        while(digitalRead(SEL)) { // Wait till SEL is pressed again to resume game
            if (platform_allow == 1) {            
                delay(20);
                play_platform(platform, hRest);
            }
        } 
        scoreboard();
        delay(200);
    } 
}
