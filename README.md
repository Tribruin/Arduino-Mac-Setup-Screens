# Arduino-Mac-Setup-Screens

## Introduction

Since the introduction of macOS High Sierra, Apple has effectively eliminated imaging as an option for macOS devices. While tools such as `startosinstall` and TwoCanoes' [MDS] (https://twocanoes.com/products/mac/mac-deploy-stick/) have help bridge the gap and simplify reinstalling macOS on new and existing devices. 

However, even when MDM is invovled, there is still a minimum number touches that are required on each Mac to step through User Setup. At minmum, a user must pick a Country, a keyboard layout, and (if using an MDM) agree to the remote management screen. Then depending on the Mac and any MDM setup, a number of other setup screens might require user involvement. 

For personal devices being handed out to end users, this is not that big of a deal, however in a lab environment, having a tech have to step through the setup screens can be cumbersome.

## Solution 
I started looking at ways to simulate keystrokes through a USB device. Arduino makes a number of devies that can act like a HID keyboard and mouse device. The Arduino Leonardo and Arduino Mirco both support acting as a HID device and can be powered solely by the USB port. This is an ideal hardware setup. 

From a software side, there is a Arduino Library to supports HID Keyboards and Mice (along with other HID devices). The library provides a number of commands that can send keyboard commands either as keystrokes or a full text. However, as commands and keystokes get more complex, it can be cumbersome to program the right sequence of keystrokes or follow the logic of the keystrokes once written. 

## Arduino Mac Setup Screens

I wrote the Arduino Mac Setup Screens as a way to simplify setting up workflows. Instead of having to write a keypress command for each step, a list of keystokes can be sent to a function. This simplifies the setup and makes it easier to understand the code as it written. 

In addition, feedback can be provided to the user through either an onboard LED or even and LCD display. 

## How to build a script using the functions

Arduino's programming language is based on C. It is functional, but is somewhat limtied as it is not an object orientated based programming language. In addition, the Arduino language requires a certian order of the functions. The order is:

1. Setup - `void setup` - Runs immediately upon power on or reset of device
2. Function and Constant defination - Define all functions and constants (as necessary) 
3. Main Loop - `void loop` - This is the main application and will run once setup is complete. Once the loop is complete, it will immediately start again. (See below on how to prevent that.) 

### Setup Section
The script include a standard setup function that inititalizes the onboard LED and and LCD screen (if attached). The LCD constants are appropriate for and the LCD shield attached to the Aurdino Leonardo. They can be modified for alternative LCD screens or setups. 

### Constants 
To ease the scripting of the keystokes, a number of constants have been defined. See below on how to use these constants in the functions. 

### Functions 
These are all the functions that are avaliable to be used in scripts. Please see below on how to script these functions. 

### Void Loop
As mentioned above, this is the main function that runs. In this loop, you would build your setup keystrokes, one screen at a time. 

By default, this loop will automatically repeat once the loop is complete. To prevent the loop from restarting, use the `while(true)` command at the end of your loop. This is will leave the Arduino doing nothing until either power is remove or the reset button is pressed. 

## Functions 

The followings functions have been establised to make sending keystrokes and commands to the Mac. In addtion, there are addtional functions to help make user interactions a little more friendly. 





