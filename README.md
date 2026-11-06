# ESC-Calibration
Used to calibrate Electronic Speed Controller (ESC) without a radio transmitter (i.e. using an Arduino Uno instead).

## Setup Instructions
The order is curcial to simulate a Radio Transmitter follow steps below:
1. Upload code to Arduino and set it up.
2. Connect the ESC to the motor (without the battery) then the Pins to the signal cables on the ESC. White cable to to pin 9 (or edit as desired in the code) and black is grounded.
3. Have all the components ready and aligned since you need to type in to iniate some steps.
4. Run the code (without the battery connected) then open serial monitor first and plug in the battery only when prompted. *Since opening/closing serial monitor will rest the Uno
5. Let the callibration code run.

### Advice / Notes
The code is written for a 3s Lipo (11.1v), connected to a Skywalker ESC (40A). Edit the values in the code based on your manufacturer if needed.

Once you set up everything and the serial monitor is open, type a "Y" or "y" then you'd only have to press enter after hearing the 2 beeps. 
