/* Calibration is done on first time use of the ESC only.

The order is curcial to simulate a Radio Transmitter follow the following:
1. Upload code to Arduino and set it up.
2. Connect the ESC to the motor (without the battery) then the Pins to the 
signal cables on the ESC 
3. Have all the components ready and aligned since you need to type in to iniate some steps.
4. Run the code (without the battery connected) then open serial monitor first
and plug in the battery only when prompted only. *Since opening/closing serial monitor will rest the Uno
5. Let the callibration code run. */

#include <Servo.h>

Servo esc;

const int ESC_PIN = 9;       // ESC signal wire connected to Pin 9
const int RUN_SPEED = 1200;   // Low test speed after calibration finishes

void setup() {
  Serial.begin(9600);
  esc.attach(ESC_PIN, 1100, 1940);

  // STEP 1: Simulate "Full Throttle Stick Up"
  
  esc.writeMicroseconds(1940); // The ESC must receive this max signal the exact microsecond it boots up
  
  Serial.println("------------------------------");
  Serial.println("[!] Step 1: Plug in the Battery to the ESC now.");
  Serial.println("(1.The ESC will sound a tune to confirm power.)");
  Serial.println("(2.The ESC will beep 2 times on max throttle)");
  Serial.println("(3.After 2 beeps, you have 5 seconds to follow [!] Step 2");
  Serial.println("------------------------------");
  Serial.println("[!] Step 2: Type 'Y' and press ENTER to switch to minimum throttle.");
 
  
  while (true) { // Hold max throttle until the serial monitor reads Y input.
	if (Serial.available() > 0) {
		char userInput = Serial.read();
		if (userInput == 'Y' || userInput == 'y') {
		break; 
	 }
   }
  }
  
  Serial.println("\n[+] Starting Calibration Sequence...");

}

void loop() {
  // We use static variables to handle the calibration timing stages
  static unsigned long startTime = millis();
  unsigned long elapsed = millis() - startTime;
  static bool calibrationDone = false; 
  
  // If the calibration is already done, skip everything else.
  if (calibrationDone == true) {
	esc.writeMicroseconds (1100); // Stop motor and exit loop
	return;
  }

  // Initated by user via the Serial Monitor, last step before finishing calibration
  if (elapsed < 2000) {   //Minimum throttle position will be accepted 1 second later
    esc.writeMicroseconds(1100);
  }

  // Calibration is done! Spin the motor at a safe test speed for 3s and stop
  else {
  Serial.println("[+] The calibration sequence has been completed, as a final test the motor will spin for 3 seconds.");
	esc.writeMicroseconds(RUN_SPEED);
	delay(3000);
	esc.writeMicroseconds(1100);
	Serial.println("[-] Motor has spun for 3 seconds. The ESC is full calibrated and is ready for use. Unplug battery.");
	calibrationDone = true;
  }

  delay(20);
}
