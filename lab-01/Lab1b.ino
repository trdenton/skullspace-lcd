/***
 * Millenium Library - Arduino Workshop
 * 
 * TITLE:        Lab #3b
 * DESCRIPTION:  Moving pacman with the buttons.
 * AUTHOR:       Dario Schor (schor@ieee.org)
 * DATE:         November 14,2015
 *
 * This example uses the LiquidCrystal librady from:
 * http://arduino.cc/en/Reference/LiquidCrystal
 *
 * The display has 2 rows of 16 characters:
 * 
 *     0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15   < COLS
 *   -----------------------------------------------------------------
 *   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |  < ROW-0
 *   -----------------------------------------------------------------
 *   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |  < ROW-1
 *   -----------------------------------------------------------------
 **/ 

#include <LiquidCrystal.h>

// Size of screen
#define NUM_ROWS        2
#define NUM_COLS        16

// Custom pinout for the shield used in the workshop
#define LCD_RS_PIN      8
#define LCD_RW_PIN      13
#define LCD_EN_PIN      9
#define LCD_D4_PIN      4
#define LCD_D5_PIN      5
#define LCD_D6_PIN      6
#define LCD_D7_PIN      7

// Analog 0 reads the input from the buttons
#define READ_BUTTON     0
#define NUM_KEYS        5
#define INVALID_KEY     -1

// Each button has a different resistance value
#define KEY_RIGHT       50
#define KEY_UP          200
#define KEY_DOWN        400
#define KEY_LEFT        600
#define KEY_SELECT      800

// Define id for pacman character
#define PACMAN_OPEN     0x1

// Pacman with the mouth opened
byte pacmanOpenDef[8] = {
  0b00000,
  0b01110,
  0b10100,
  0b11000,
  0b11100,
  0b01110,
  0b00000,
  0b00000
};

// Create instance of LiquidCrystal object
LiquidCrystal lcd(
  LCD_RS_PIN,   // Register Select
  LCD_RW_PIN,   // H-Read, L-Write
  LCD_EN_PIN,   // Enable (data strobe, active high)
  LCD_D4_PIN,   // Data pins
  LCD_D5_PIN, 
  LCD_D6_PIN, 
  LCD_D7_PIN
  );

// Analog value corresponding to each key pressed
int keyMapping[NUM_KEYS] = {
  KEY_RIGHT, 
  KEY_UP, 
  KEY_DOWN, 
  KEY_LEFT, 
  KEY_SELECT 
  };
  
int key = INVALID_KEY;
int x   = 0;
int y   = 0;

/***
 * setup()
 * Description:  Initialize the LCD.
 **/
void setup()
{
  // Clear the LCD screen
  lcd.clear(); 
  
  // Set the dimensions of the LCD screen.
  lcd.begin(NUM_COLS, NUM_ROWS);
  
  // Define pacman character
  lcd.createChar(PACMAN_OPEN,  pacmanOpenDef);
  
  x = 0;
  y = 0;
  lcd.setCursor(x, y);
  
  // Write pacman to the home position
  lcd.write(PACMAN_OPEN);
  
  Serial.begin(9600);
}

/***
 * loop()
 * Description:  Read a key and print a msg to the LCD.
 **/
void loop()
{
  // Read key
  key = readKey();
  
  //Serial.println("COORDINATE: " + x + " " + y);
  
  // If a key is pressed, print the message
  if(INVALID_KEY != key)
  {
    lcd.setCursor(x, y);
    lcd.write(' ');
    
    if(KEY_RIGHT == key && x < NUM_COLS-1)
    {
      x++;
    }
    else if(KEY_LEFT == key && x > 0)
    {
      x--; 
    }
    else if(KEY_DOWN == key && y < NUM_ROWS-1)
    {
      y++; 
    }
    else if(KEY_UP == key && y > 0)
    {
      y--; 
    }
    
    lcd.setCursor(0,0);
    lcd.print(x);
    lcd.setCursor(0,1);
    lcd.print(y);
  }
  
  // Delay before printing next message
  delay(100);
}

/***
 * readKey()
 * Description:  Find which key was pressed.
 **/
int readKey(void)
{
  int key = analogRead(READ_BUTTON);
  int index;
  
  // Find which key was pressed
  for(index = 0; index < NUM_KEYS; index++)
  {
    if(key < keyMapping[index])
    {
       return keyMapping[index]; 
    }
  }
   
  // No key found
  return INVALID_KEY;  
}
	
