// Made by Udey Rishi & Aaron Plamondon

#ifndef __game_header_h__
#define __game_header_h__

#include <Arduino.h> // Standard Arduino library
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

// standard U of A library settings, assuming Atmel Mega SPI pins
#define SD_CS    5  // Chip select line for SD card
#define TFT_CS   6  // Chip select line for TFT display
#define TFT_DC   7  // Data/command line for TFT
#define TFT_RST  8  // Reset line for TFT (or connect to +5V)
#define VERT 0 // Joystick's VERT analog pin
#define HOR 1 // Joystick's HORZ analog pin
#define SEL 9 // Joystick's Sel digital button

#define BRICK_NUMBER 20 // Number of bricks drawn

// The size used to create the bricks border.
#define BRICK_BORDER_X 32
#define BRICK_BORDER_Y 9

// The size of the brick to be printed inside the border.
#define BRICK_SIZE_X 28
#define BRICK_SIZE_Y 5

// Speaker pin
#define SPEAKER_PIN 2

// Contains the ball info
struct ball_stats  {
    int16_t x_coord; // Center's x
    int16_t y_coord; // Center's y
    int16_t length; // Current length 
    int16_t x_vel; // Velocity in x direction
    int16_t y_vel; // Velocity in y direction
};

// Contains the platform info
struct platform_stats {
    int16_t length; // Current length of platform
    int16_t width; // CUrrent width of platform
    int16_t x_coord; // Center's x
    int16_t y_coord; // Center's
    int16_t vel; // Current horizontal velocity (vertical movement is not allowed)
};

// Contains the info of each brick
struct brick_info {
    int8_t brick_colour; // Colour: Invisible = -1; Green = 0; Blue = 1; Red = 2; Black = 3
    uint8_t brick_location_x; // Corner's x
    uint8_t brick_location_y; // Corner's y
};

// Environment functions
brick_info* environment_draw();
void brick_draw(brick_info brick);
void high_scores();
void menu_option1();
void menu_option2();
void menu_bricks();
int menu (int16_t vRest);
void update_score();
void update_lives();
void scoreboard();
void playTone(int period, int duration);

// Physics functions
void reset_platform(platform_stats *platform);
void reset_ball(ball_stats *ball, platform_stats *platform);
void draw_ball(ball_stats *ball);
void delete_ball(ball_stats *ball);
void draw_platform(platform_stats *platform);
void delete_platform(platform_stats *platform);
void play_ball(ball_stats *ball, platform_stats *platform, brick_info* bricks);
void play_platform(platform_stats *platform, int16_t hRest);
void platform_bounce_check(ball_stats *ball, platform_stats *platform);
void wall_bounce_check(ball_stats *ball);
void brick_bounce_check(ball_stats *ball, brick_info* bricks);
int16_t h_calibrate_joystick();
int16_t v_calibrate_joystick();
int play_game(brick_info* bricks, int16_t hRest, int round);
void check_pause(int16_t initial, platform_stats *platform, int16_t hRest, int8_t platform_allow);
#endif 
