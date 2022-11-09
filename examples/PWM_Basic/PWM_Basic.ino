/****************************************************************************************************************************
  PWM_Basic.ino

  For Arduino AVRDx-based boards (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/Dx_PWM
  Licensed under MIT license
*****************************************************************************************************************************/

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


#ifdef LED_BUILTIN
  #undef LED_BUILTIN

  // To modify according to your board
  // For Curiosity Nano AVR128DA48 => PIN_PC6
  // For Curiosity Nano AVR128DB48 => PIN_PB3
  #if defined(__AVR_AVR128DA48__)
    #define LED_BUILTIN   PIN_PC6   // PIN_PB3, 13
  #elif defined(__AVR_AVR128DB48__)
    #define LED_BUILTIN   PIN_PB3   // PIN_PC6, 13
  #else
    // standard Arduino pin 13
    #define LED_BUILTIN   13
  #endif
#endif

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

#define pinToUse       PIN_PC3    //PIN_PF5

//creates pwm instance
Dx_PWM* PWM_Instance;

float frequency = 1000.0f;

float dutyCycle = 0.0f;

void setup()
{
  SerialDebug.begin(115200);

  while (!Serial && millis() < 5000);

  delay(500);

  SerialDebug.print(F("\nStarting PWM_Basic on "));
  SerialDebug.println(BOARD_NAME);
  SerialDebug.println(DX_PWM_VERSION);

  //assigns PWM frequency of 1.0 KHz and a duty cycle of 0%
  PWM_Instance = new Dx_PWM(pinToUse, frequency, dutyCycle);

  if ( (!PWM_Instance) /*|| !PWM_Instance->isPWMEnabled()*/)
  {
    SerialDebug.print(F("Stop here forever"));

    while (true)
      delay(10000);
  }
}

void loop()
{
  // You can change frequency here, anytime
  frequency = 2000.0f;
  dutyCycle = 20.0f;

  PWM_Instance->setPWM(pinToUse, frequency, dutyCycle);

  delay(5000);

  // You can change frequency here, anytime
  frequency = 4000.0f;
  dutyCycle = 80.0f;

  PWM_Instance->setPWM(pinToUse, frequency, dutyCycle);

  //while (1)
  delay(5000);
}
