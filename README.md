# Arduino-Mac-Setup-Screens

## Introduction

Since the introduction of macOS High Sierra, Apple has effectively eliminated imaging as an option for macOS devices. While tools such as `startosinstall` and TwoCanoes' [MDS](https://twocanoes.com/products/mac/mac-deploy-stick/) have helped bridge the gap and simplify reinstalling macOS on new and existing devices. 

However, even when MDM is invovled, there is still a number touches that are required on each Mac to walk through User Setup. At minimum, a user must pick a Country, a keyboard layout, and (if using an MDM) agree to the remote management screen. Then depending on the Mac and any MDM setup, a number of other setup screens might require user involvement. 

For personal devices being handed out to end users, this is not that big of a deal, however in a lab environment, having a tech have to step through each setup screen can be cumbersome.

## Solution 
I started looking at ways to simulate keystrokes through a USB device. Arduino makes a number of devies that can simulate a HID keyboard and mouse device. The Arduino Leonardo and Arduino Micro both support emulating a HID device and can be powered solely by the USB port.  

From a software side, Adurino provide an IDE and a development library that emulates a USB HID device. The library provides a number of commands that can send keyboard commands either as keystrokes or a full text. However, as commands and keystokes get more complex, it can be cumbersome to program the right sequence of keystrokes or follow the logic of the keystrokes once written. 

## Arduino Mac Setup Screens

I wrote the Arduino Mac Setup Screens as a way to simplify setting up workflows. Instead of having to write a keypress command for each step, a list of keystokes can be sent to a function. This simplifies the setup and makes it easier to understand the code as it written. 

In addition, feedback can be provided to the user through either an onboard LED or even and LCD display. 

## How to build a script using the functions

Arduino's programming language is based on C. It is functional, but is somewhat limited as it is not an object orientated based programming language. In addition, the Arduino language requires a certian order of the functions. The order is:

1. Setup - `void setup` - Runs immediately upon power on or reset of device
2. Function and Constant defination - Define all functions and constants (as necessary) 
3. Main Loop - `void loop` - This is the main application and will run once setup is complete. Once the loop is complete, it will immediately start again. (See below on how to prevent that.) 

### Setup Section
The script include a standard setup function that inititalizes the onboard LED and and LCD screen (if attached). The LCD constants are appropriate for and the LCD shield attached to the Aurdino Leonardo. They can be modified for alternative LCD screens or setups. 

### Constants 
To ease the scripting of the keystokes, a number of constants have been defined. For example, you can use RETURN or ESC or F2 instead of their cooresponding ASCII codes. Modifier keys (SHIFT, CTRL, CMD, OPT) are also avaliable. A complete list of keys and modifier keys can be found in the source code. See below on how to use these constants in the functions. 

### Functions 
These are all the functions that are avaliable to be used in scripts. Please see below on how to script these functions. 

### Void Loop
As mentioned above, this is the main function that runs. In this loop, you would build your setup keystrokes, one screen at a time. 

By default, this loop will automatically repeat once the loop is complete. To prevent the loop from restarting, use the `while(true)` command at the end of your loop. This is will leave the Arduino doing nothing until either power is remove or the reset button is pressed. 

## User Functions 

The followings functions have been establised to make sending keystrokes and commands to the Mac. In addtion, there are addtional functions to help make user interactions a little more friendly. 

`keystroke(key)` - This function will send a single keystroke to the device through the USB port. 

* _key_ can be either a character ('r') one of the special keys defined as constanats (ESC, RETURN). Modifier keys should be added to the main key with a + sign (e.g CMD+'s' or SHIFT+CMD+'q'). 

`sendkeystokes(screenName, keyArray, keyArrayLen, delayLength)` - This function will will send a series of keystrokes, one every 0.5 seconds, to the device through the USB port.

Arugments required:

* _screenName_ - The name that is displayed on the optional LCD when the keysequence is running. If you are not using an LCD, you can just use `""`. 
* _keyArray_ - A variable with an array of keystrokes. **NOTE:** You must define variable prior to the function call. Due to C limitations you, can't just pass an array in the function arguments. The array should defined as:
	* int _variableName[]_={keystroke1, keystroke2, etc}
	* The keystroke folllows the same guidelines as the keystroke function above. 
	* The variable MUST be defined as an _Int_ array. The complier will convert and text to it's cooresponding ASCII code. 
* _keyArrayLen_ - The number of keystrokes in the in the _keyArray_ variable.
* _delayLength_ - Number of seconds to wait before sending the keystrokes. 

`sendText(screenName, command, delayLength)` - Send a string to the device through the USB. Good for sending longer text only commands. 

Arguements required:

* _screenName_ - The name that is displayed on the optional LCD when the keysequence is running. If you are not using an LCD, you can just use `""`. 
* _command_ - A string of text. 
* _delayLength_ - Number of seconds to wait before sending the command. 

**NOTE:** If you need a return after sending the text, either add the `\n` escape code to the end of the command or send a `keystroke(RETURN)` command immediatly following. 

_delayWait(timeInSecs)_ - Wait _timeInSecs_ seconds before proceeding. The LED will blink during this wait. 

_waitForButton(timeOut)_ - Wait for the on-board button (or the LCD button if avaliable) to be pressed. If not button is pressed before _timeOut_ seconds, the script will automatically continue. If is suggested this be your first command in the _loop()_ to allow time after plugging in the Arduino to reprogram it. Otherwise, when plugging in to your programming computer, your computer will start receiving keystokes. 

_statusToLCD(message, row)_ - Send _message_ to the LCD screen. Use the constants `LCD__TOP__ROW` or `LCD_BOTTOM_ROW` for _row_

## User Feedback
While not required, there is a minimal amount of user feedback avaliable in the manner:

* LED - The Built-in LED will flash quickly when the script is sending keystrokes. In additon, when the script is paused, either by _delayWait()_ or _waitForButton()_, the LED wil blink on and off on a 0.5 second interval.

* LCD - When sending keystrokes, the LCD will display the key combination pressed on the bottom row of the LCD. This can be very helpful when troubleshooting keystrokes. 

## Sample Code & Best Practices
* The script includes the subsections to walk through the setup screens on a non-MDM enrolled MacBookPro (2015) on Mojave. It should provide a tempalate for creating subsections for other setup screens not listed. 
* The Arduino will initizalize quickly once power is supplied. It is suggested that the USB key be inserted at the first setup screen to prevent keys from being sent before the Mac is ready. 
* There are a few common keystrokes that are useful when walking through setup:
	* _TAB_ - Move between elements on the screen. 
	* _SPACE_ - Selects the current highlighted item or presses the highlight button.
	* _CTRL+F2_ - Allows keyboard access to the macOS menu, when the menu bar is avaliable. Once the menu is active, the arrows keystrokes and _ENTER_ key can be used to select a specific menu item.  
	* _CTRL+OPT+CMD+t_ - Open the terminal while in setup
* Make sure you allow enough time between before sending the keystrokes. Time between screens can vary between devices. Add extra seconds when using the _delayLength_ argument. If you find that keystrokes are often being missed, increase the _delayLength_ for that screen. 
* Having at least one Arduino Leonardo with an LCD shield for troubleshooting purposes is really helpful. You can review each keystroke as they are happening. Once your script is working properly, you can use cheaper Arduino Micros or Adafruit IstyBitys 
* You will need to download the [Arduino IDE](https://www.arduino.cc/en/Main/Software) and [HID-Project Library](https://www.arduinolibraries.info/libraries/hid-project) to use the code and install the script on to an Adurino device.
* While my script primarily focuses on the macOS setup screens, any computer that can use a HID keyboard input could be scripted. For example, setting BIOS screens on Windows PCs. 
* Because the script will run as soon as the device is plugged in, it is possible and even likely, that the existing script will run while trying to program the device. The sample script includes a function to wait for a button press and, if pressed, put the script in to infinite loop. This will allow you to prevent the script from running while trying to program. 

## Questions and Feedback
Please ask any question or provide any feedback. 