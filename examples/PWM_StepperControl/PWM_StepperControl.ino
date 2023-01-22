/****************************************************************************************************************************
  PWM_StepperControl.ino
  For Arduino AVRDx-based boards (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/Dx_PWM
  Licensed under MIT license

  Credits of Paul van Dinther (https://github.com/dinther). Check https://github.com/khoih-prog/RP2040_PWM/issues/16
*****************************************************************************************************************************/

// Use with Stepper-Motor driver, such as TMC2209

#define _PWM_LOGLEVEL_       4

#if defined(__AVR_AVR128DA48__)
  #define SerialDebug   Serial1
#elif defined(__AVR_AVR128DB48__)
  #define SerialDebug   Serial3
#else
  // standard Serial
  #define SerialDebug   Serial
#endif

#define PWM_GENERIC_DEBUG_PORT    SerialDebug

#include "Dx_PWM.h"

// On DX AVR128DB48
// PA0-3: Not PWM
// PA4-7: TD0 => not supported yet
// PB0-5: TCA1
// PC0-5: TCA0
// PC6-7: Not PWM
// PD0-7: Not PWM
// PE0-3: Not PWM
// PF0-3: Not PWM
// PF4-5: TCB

#if defined(PIN_PF5)
  #define STEP_PIN       PIN_PF5
#else
  #define STEP_PIN       PIN_PC0
#endif

#define DIR_PIN          PIN_PA0

Dx_PWM* stepper;

void setSpeed(int speed)
{
  if (speed == 0)
  {
    // Use DC = 0 to stop stepper
    stepper->setPWM(STEP_PIN, 500, 0);
  }
  else
  {
    //  Set the frequency of the PWM output and a duty cycle of 50%
    digitalWrite(DIR_PIN, (speed < 0));
    stepper->setPWM(STEP_PIN, abs(speed), 50);
  }
}

void setup() 
{
  pinMode(DIR_PIN, OUTPUT);
  
  Serial.begin(115200);

  while (!Serial && millis() < 5000);

  delay(100);

  Serial.print(F("\nStarting PWM_StepperControl on "));
  Serial.println(BOARD_NAME);
  Serial.println(DX_PWM_VERSION);
  
  // Create PWM object and passed just a random frequency of 500
  // The duty cycle is how you turn the motor on and off
  stepper = new Dx_PWM(STEP_PIN, 500, 0);
}

void loop() 
{
  setSpeed(1000);
  delay(3000);

  // Stop before reversing
  setSpeed(0);
  delay(3000);

  // Reversing
  setSpeed(-500);
  delay(3000);

  // Stop before reversing
  setSpeed(0);
  delay(3000);
}
