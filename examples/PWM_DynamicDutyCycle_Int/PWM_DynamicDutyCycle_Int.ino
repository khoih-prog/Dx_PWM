/****************************************************************************************************************************
  PWM_DynamicDutyCycle_Int.ino

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

#if defined(PIN_PF5)
  #define pinToUse       PIN_PF5
#else
  #define pinToUse       PIN_PC0
#endif

//creates pwm instance
Dx_PWM* PWM_Instance;

float frequency;
uint16_t dutyCycle;

char dashLine[] = "=====================================================================================";

void printPWMInfo(Dx_PWM* PWM_Instance)
{
  SerialDebug.println(dashLine);
  SerialDebug.print("Actual data: pin = ");
  SerialDebug.print(PWM_Instance->getPin());
  SerialDebug.print(", PWM DC = ");
  SerialDebug.print(PWM_Instance->getActualDutyCycle());
  SerialDebug.print(", PWMPeriod = ");
  SerialDebug.print(PWM_Instance->getPWMPeriod());
  SerialDebug.print(", PWM Freq (Hz) = ");
  SerialDebug.println(PWM_Instance->getActualFreq(), 4);
  SerialDebug.println(dashLine);
}

void setup()
{
  SerialDebug.begin(115200);

  while (!Serial && millis() < 5000);

  delay(500);

  SerialDebug.print(F("\nStarting PWM_DynamicDutyCycle_Int on "));
  SerialDebug.println(BOARD_NAME);
  SerialDebug.println(DX_PWM_VERSION);

  frequency = 1000.0f;

  PWM_Instance = new Dx_PWM(pinToUse, frequency, 0.0f);

  if (!PWM_Instance)
  {
    SerialDebug.print(F("Stop here forever"));

    while (true)
      delay(10000);
  }

  SerialDebug.println(dashLine);
}

void loop()
{
  frequency = 5000.0f;

  // 50% dutyCycle = (real_dutyCycle * 65536) / 100
  dutyCycle = 32768;

  SerialDebug.print(F("Change PWM DutyCycle to (%) "));
  SerialDebug.println((float) dutyCycle * 100 / 65536);
  PWM_Instance->setPWM_Int(pinToUse, frequency, dutyCycle);

  printPWMInfo(PWM_Instance);

  delay(5000);

  // 20% dutyCycle = (real_dutyCycle * 65536) / 100
  dutyCycle = 13107;

  SerialDebug.print(F("Change PWM DutyCycle to (%) "));
  SerialDebug.println((float) dutyCycle * 100 / 65536);
  PWM_Instance->setPWM_Int(pinToUse, frequency, dutyCycle);
  printPWMInfo(PWM_Instance);

  delay(5000);
}
