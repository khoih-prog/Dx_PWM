/****************************************************************************************************************************
  PWM_Multi.ino

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

// Be careful to select pins for different frequencies
uint32_t PWM_Pins[] = { PIN_PB2, PIN_PC0, PIN_PF4, PIN_PF5 };

float frequency[]   = { 2000.0f, 3000.0f, 4000.0f, 8000.0f };
float dutyCycle[]   = { 20.0f, 30.0f, 40.0f, 80.0f };

#define NUM_OF_PINS   ( sizeof(PWM_Pins) / sizeof(uint32_t) )

Dx_PWM* PWM_Instance[NUM_OF_PINS];

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

  SerialDebug.print(F("\nStarting PWM_Multi on "));
  SerialDebug.println(BOARD_NAME);
  SerialDebug.println(DX_PWM_VERSION);

  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    PWM_Instance[index] = new Dx_PWM(PWM_Pins[index], frequency[index], dutyCycle[index]);

    if (PWM_Instance[index])
    {
      PWM_Instance[index]->setPWM();
    }
  }

  SerialDebug.println(dashLine);
  SerialDebug.println("Index\tPin\tPWM_freq\tDutyCycle\tActual Freq");
  SerialDebug.println(dashLine);

  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    if (PWM_Instance[index])
    {
      SerialDebug.print(index);
      SerialDebug.print("\t");
      SerialDebug.print(PWM_Pins[index]);
      SerialDebug.print("\t");
      SerialDebug.print(frequency[index]);
      SerialDebug.print("\t\t");
      SerialDebug.print(dutyCycle[index]);
      SerialDebug.print("\t\t");
      SerialDebug.println(PWM_Instance[index]->getActualFreq(), 4);
    }
    else
    {
      SerialDebug.println();
    }
  }

  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    printPWMInfo(PWM_Instance[index]);
  }
}

void loop()
{
  //Long delay has no effect on the operation of hardware-based PWM channels
  delay(1000000);
}
