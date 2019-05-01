#include <HID-Project.h>
#include <HID-Settings.h>
#include <LiquidCrystal.h>

/* This project simulates a keyboard and contains functions to allow easy programming of mulitple step programs. 
 * This program was inspired by a blog post by Tim Perfitt of Two Canoes software and builds on those ideals
 *  https://twocanoes.com/automating-macos-and-package-installation-from-the-recovery-partition/
 *  
 *  You must install the HID-Project library for this application to work. 
 *  See https://www.arduinolibraries.info/libraries/hid-project to dwonload and install the latest version
 *  
 */


// Pin constants for LCD Display. the Arduino Duo constants work with the standard LCD Sheilds. 
// const int rs = 5, en = 7, d4 = 9, d5 = 10, d6 = 11, d7 = 12; // Adafruit Itsy Bitsy Board
const int rs=8, en=9, d4=4, d5=5, d6=6, d7=7;      // Arduino Duo/Leonardo

const int dButtonPin = 3;       // Digital Button Pin
const int aButtonPin = 0;       // Analog Pin in
const int LCD_TOP_ROW=0;
const int LCD_BOTTOM_ROW=1; 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Constants for modifier keys on the keyboard 

#define CTRL 256        // CTRL key modifer
#define SHIFT 512       // SHIFT key modifer
#define OPT 1024        // Option or ALT key modifer
#define ALT 1024
#define CMD 2048        // Command or Windows key modifier
#define WIN 2048

// Constants for special keys on keyboard

#define UP 218             // Up Arrow
#define DOWN 217           // Down Arrow
#define LEFT 216         // Left Arrow
#define RIGHT 215         // Right Arrow
#define BACKSPACE 178      // Backspace
#define TAB 179
#define RETURN 176          // Return
#define ESC 177            // Escape
#define INSERT 209
#define DELETE 212
#define PGUP 211
#define PGDOWN 214
#define HOME 210
#define END 213
#define CAPSLOCK 193
#define F1 194
#define F2 195
#define F3 196
#define F4 197
#define F5 198
#define F6 199
#define F7 200
#define F8 201
#define F9 202
#define F10 203
#define F11 204
#define F12 205
#define SPACE ' '

void setup() {
  // setup code
  BootKeyboard.begin();         // Initialize BootKeyboard Interface on board. 
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the onboard LED

  lcd.begin(16,2);              // Start the LCD Display
  lcd.clear();                  // Clear the LCD from any residual display

  pinMode(dButtonPin, INPUT_PULLUP);    // Start the LCD Display
}

void keystroke(int key) {
  
/* This function will send a keystroke through the HID interface
 *  variables:
 *    key = keystroke to send. Use the key enclosed in ' ' to send the keystroke
 *  to add modifieres, use <modifer> + '<key>' as key
 *  e.g. keystroke (cmd + 'q') will send the CMD+Q key. 
 */

/* This section checks to see if the keyboard modifiers have been added to the key command. If mulitple modifiers are added, it will press all of them
 */
  String keyDisplay = "";
  if (key >= CMD) {
      key = key - CMD;
      keyDisplay=keyDisplay+"CM+";
      BootKeyboard.press(KEY_LEFT_GUI);
      
      }

  if (key >= OPT) {
      key = key - OPT;
      keyDisplay=keyDisplay+"OP+";
      BootKeyboard.press(KEY_LEFT_ALT);
      }

  if (key >= SHIFT) {
      key = key - SHIFT;
      keyDisplay=keyDisplay+"SH+";
      BootKeyboard.press(KEY_LEFT_SHIFT);
      }

  if (key >= CTRL) {
      key = key - CTRL;
      keyDisplay=keyDisplay+"CT+";
      BootKeyboard.press(KEY_LEFT_CTRL);
      }

  digitalWrite(LED_BUILTIN, HIGH);        // Turn on LED before keystroke

  // Check for "special" keys due to the way that HID-PROJECT handles non-ASCII keys on the keyboard.
  switch(key) {
    
    case UP:
      BootKeyboard.press(KEY_UP_ARROW);
      keyDisplay=keyDisplay+"UP";
      break;

    case DOWN:
      BootKeyboard.press(KEY_DOWN_ARROW);
      keyDisplay=keyDisplay+"DOWN";
      break;

    case LEFT:
      BootKeyboard.press(KEY_LEFT_ARROW);
      keyDisplay=keyDisplay+"LEFT";
      break;

    case RIGHT:
      BootKeyboard.press(KEY_RIGHT_ARROW);
      keyDisplay=keyDisplay+"RGHT";
      break;

     case BACKSPACE:
      BootKeyboard.press(KEY_BACKSPACE);
      keyDisplay=keyDisplay+"BKSP";
      break;

    case TAB:
      BootKeyboard.press(KEY_TAB);
      keyDisplay=keyDisplay+"TAB";
      break;

    case RETURN:
      BootKeyboard.press(KEY_RETURN);
      keyDisplay=keyDisplay+"ENTR";
      break;

    case ESC:
      BootKeyboard.press(KEY_ESC);
      keyDisplay=keyDisplay+"ESC";
      break;

    case INSERT:
      BootKeyboard.press(KEY_INSERT);
      keyDisplay=keyDisplay+"ISRT";
      break;

    case DELETE:
      BootKeyboard.press(KEY_DELETE);
      keyDisplay=keyDisplay+"DEL";
      break;

    case PGUP:
      BootKeyboard.press(KEY_PAGE_UP);
      keyDisplay=keyDisplay+"PGUP";
      break;

    case PGDOWN:
      BootKeyboard.press(KEY_PAGE_DOWN);
      keyDisplay=keyDisplay+"PGDN";
      break;

    case HOME:
      BootKeyboard.press(KEY_HOME);
      keyDisplay=keyDisplay+"HOME";
      break;

    case END:
      BootKeyboard.press(KEY_END);
      keyDisplay=keyDisplay+"END";
      break;

    case CAPSLOCK:
      BootKeyboard.press(KEY_CAPS_LOCK);
      keyDisplay=keyDisplay+"CPSLK";
      break;

    case F1:
      BootKeyboard.press(KEY_F1);
      keyDisplay=keyDisplay+"F1";
      break;

    case F2:
      BootKeyboard.press(KEY_F2);
      keyDisplay=keyDisplay+"F2";
      break;

    case F3:
      BootKeyboard.press(KEY_F3);
      keyDisplay=keyDisplay+"F3";
      break;

    case F4:
      BootKeyboard.press(KEY_F4);
      keyDisplay=keyDisplay+"F4";
      break;

    case F5:
      BootKeyboard.press(KEY_F5);
      keyDisplay=keyDisplay+"F5";
      break;

    case F6:
      BootKeyboard.press(KEY_F6);
      keyDisplay=keyDisplay+"F6";
      break;

    case F7:
      BootKeyboard.press(KEY_F7);
      keyDisplay=keyDisplay+"F7";
      break;

    case F8:
      BootKeyboard.press(KEY_F8);
      keyDisplay=keyDisplay+"F8";
      break;

    case F9:
      BootKeyboard.press(KEY_F9);
      keyDisplay=keyDisplay+"F9";
      break;

    case F10:
      BootKeyboard.press(KEY_F10);
      keyDisplay=keyDisplay+"F10";
      break;

    case F11:
      BootKeyboard.press(KEY_F11);
      keyDisplay=keyDisplay+"F11";
      break;

    case F12:
      BootKeyboard.press(KEY_F12);
      keyDisplay=keyDisplay+"F12";
      break;

    case SPACE:
      BootKeyboard.press(' ');
      keyDisplay=keyDisplay+"SPC";
      break;

    default:
      BootKeyboard.press(key);
      keyDisplay=keyDisplay+char(key);
      break;
    }

  statusToLCD(keyDisplay,LCD_BOTTOM_ROW);
  delay(100);                       // Press and hold key 0.1 seconds
  BootKeyboard.releaseAll();
  digitalWrite(LED_BUILTIN, LOW);   // Turn off LED
  delay(200);
  statusToLCD("", LCD_BOTTOM_ROW); 
  delay(200);                       // Wait for 0.5 secs after keyrelease
}

void delayWait(int timeInSecs){
  /* This function executes a delay and prints a count down on the LCD 
   *    timeInSecs = # of secs to wait
   */
   for (int i = timeInSecs; i > 0; i = i - 1) {
      String message = String(String(i) + " secs");
      statusToLCD(message, LCD_BOTTOM_ROW);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
   }
}

void statusToLCD(String message, int row) {
  /* This function prints a message on the LCD display. 
   *    message = message to display
   *    row = row (LCD_TOP_ROW or LCD_BOTTOM_ROW) to display the message
   *  message is left justified. 
   */
  lcd.setCursor(0,row);                 // Set cursor to row
  lcd.print("                ");        // Clear the row of any existing text
  lcd.setCursor(0,row);                 // Set cursor back to the beginning of the row. 
  lcd.print(message);                   // Print the message
}

void sendKeystrokes( String screenName, int keyArray[], int keyArrayLen, int delayLength) {
  /* This function sends a series of keystrokes in sucession to the HID devices
   *    screenName = name of the screen to displayed on the LCD
   *    keyArray = Array of keystrokes to send in succession (see below for details)
   *    keyArrayLen = Num of keystrokes that will be sent. 
   *    delayLength = delay BEFORE executing
   *    
   *  Notes about keyArray and keyArrayLen:
   *    keyArray can be constructed by a series of keystokes. 
   *      Regular keys can be listed as the characters enclosed in single quotes. Ex.  'r', '1', 'z')
   *      Special keys can be listed by their names. Ex. TAB, SPACE, RETURN. See declarations for list of special keys)
   *      Modifier keys can be ADDED to regular or special keys. Ex. CMD+'q', OPT+SPACE, CTRL+'c"
   *      sample of a keyArray {'1', '2', '3', '4', TAB, SPACE, BACKSPACE, BACKSPACE, CMD+'q'}
   *    keyArrayLen is necessary due to a limitation of passing arrays to functions in C. C only passes a pointer to the first  
   *    first entry of the arry to the function. keyArrayLen ensures the functions knows how many keystrokes to execute. 
   */
   
  statusToLCD(screenName, LCD_TOP_ROW);
  if (delayLength > 0) {
    delayWait(delayLength);
  }
  for (int i = 0; i < keyArrayLen; i++) {
    keystroke(keyArray[i]);  
  }
}

void sendText(String screenName, String command, int delayLength) {
  /* This function sends a line of text to the USB HID output
   *    screenName = name of the screen to displayed on the LCD
   *    command = text to be "typed" by the HID device. To add a return at the end, use \n at the end of your test
   *    delayLength = delay BEFORE executing 
   */

  statusToLCD(screenName, LCD_TOP_ROW);
  if (delayLength > 0) {
    delayWait(delayLength);
  }
  digitalWrite(LED_BUILTIN, HIGH);     // Turn on LED for 0.1 seconds
  BootKeyboard.print(command);         // Changed to print from println to eliminate \n at the end. Use \n in your command code. 
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}

void waitForButton(int timeOut) {
  /* Wait for the the button to close before proceeding
   * This function works with either an analog pin or a digital pin. It wait for either
   * the digital pin to go LOW or the analog pin to down below 790
   *    timeOut = time before wait expires (for devices without a button - Set to high value to never time out
   * 
   */ 
  // while ( (digitalRead(dButtonPin) == HIGH) && (analogRead(aButtonPin) > 790));
  int i=0;
  int x=0;
  bool buttonPushed = false;
  for (i = timeOut; i > 0; i = i - 1) {
    digitalWrite(LED_BUILTIN, HIGH);
    for (x = 0; x < 500; x++) {
      delay(1);
      if ((digitalRead(dButtonPin) == LOW ) || (analogRead(aButtonPin) < 790)) {
        buttonPushed = true; 
      }
    }
    digitalWrite(LED_BUILTIN, LOW);
    for (x = 0; x < 500; x++) {
      delay(1);
      if ((digitalRead(dButtonPin) == LOW ) || (analogRead(aButtonPin) < 790)) {
        buttonPushed = true; 
      }
    }
    if (buttonPushed) {
      break;
    }
  }
}

void pushButtonToProgram(int timeOut) {
  /* Wait for the the button to close before proceeding
   * This function works with either an analog pin or a digital pin. It wait for either
   * the digital pin to go LOW or the analog pin to down below 790
   *    timeOut = time before wait expires (for devices without a button - Set to high value to never time out
   * If button is push, enter an endless loop to wait for programming wihtout running the application 
   */ 
  // while ( (digitalRead(dButtonPin) == HIGH) && (analogRead(aButtonPin) > 790));
  int i=0;
  int x=0;
  bool buttonPushed = false;
  for (i = timeOut; i > 0; i = i - 1) {
    digitalWrite(LED_BUILTIN, HIGH);
    for (x = 0; x < 500; x++) {
      delay(1);
      if ((digitalRead(dButtonPin) == LOW ) || (analogRead(aButtonPin) < 790)) {
        buttonPushed = true; 
      }
    }
    digitalWrite(LED_BUILTIN, LOW);
    for (x = 0; x < 500; x++) {
      delay(1);
      if ((digitalRead(dButtonPin) == LOW ) || (analogRead(aButtonPin) < 790)) {
        buttonPushed = true; 
      }
    }
    if (buttonPushed) {
      statusToLCD("Programming", LCD_TOP_ROW);
      statusToLCD("Mode", LCD_BOTTOM_ROW);
      while(true);             // Do not proceed. 
    }
  }
}

void loop() {

  // Wait to see if user wants to program device
  statusToLCD("Press Button to", LCD_TOP_ROW);
  statusToLCD("Program", LCD_BOTTOM_ROW);
  pushButtonToProgram(10);
  
  // Prompt User to press button to continue
  statusToLCD("Press Button to", LCD_TOP_ROW);
  statusToLCD("begin macOS Setup", LCD_BOTTOM_ROW);
  waitForButton(30);
     
  // Welcome
  int keys1[] = {TAB, SPACE};
  sendKeystrokes("Welcome", keys1, 2, 5);
  
  //Select Keyboard
  int keys2[] = {TAB, TAB, TAB, SPACE};
  sendKeystrokes("Keyboard", keys2, 4, 1);

  // Data Privacy
  int keys3[] = {TAB, TAB, TAB, OPT+SPACE};
  sendKeystrokes("Data Privacy", keys3, 4, 1);

  // Transfer Information to this Mac
  int keys4[] = {TAB, TAB, TAB, OPT+SPACE};
  sendKeystrokes("Transfer", keys4, 4, 1);

   // AppleID Setup
  int keys5[] = {TAB, TAB, TAB, TAB, TAB, TAB, OPT+SPACE};
  sendKeystrokes("AppleID", keys5, 7, 1);
  int keys6[] = {TAB, OPT+SPACE};
  sendKeystrokes("AppleID Confirm", keys6, 2, 1);

  // Terms & Conditions
  int keys7[] = {TAB, TAB, OPT+SPACE};
  sendKeystrokes("T&Cs", keys7, 3, 5);
  int keys8[] = {TAB, OPT+SPACE};
  sendKeystrokes("T&Cs Confirm", keys8, 2, 1);
  
   // Account Creation
  sendText("Account Creation", "admin", 1);
  int  keys9[]={TAB, TAB};
  sendKeystrokes("Account Creation", keys9, 2, 0);
  sendText("Account Creation", "Password", 0);
  keystroke(TAB);
  sendText("Account Creation", "Password", 0);
  int keys10[]={TAB, TAB, TAB, OPT+SPACE};
  sendKeystrokes("Account Creation", keys10, 4, 0);
  
  // Express Setup
  int keys11[]={TAB, TAB, TAB, OPT+SPACE};
  sendKeystrokes("Express Setup", keys11, 4, 20);

  // Choose Look
  int keys12[]={TAB, TAB, TAB, OPT+SPACE};
  sendKeystrokes("Choose Look", keys12, 4, 2);

    // Close out script and clear LCD
  lcd.clear();
  statusToLCD("Exec Complete", LCD_TOP_ROW);
  statusToLCD("Remove USB", LCD_BOTTOM_ROW);


  while(true);                        // Run continously to prevent additonal keystrokes. 
 
}
