/****************************************************************************************************************************
  Dx_PWM.h

  For Arduino AVRDx-based boards (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/megaAVR_PWM
  Licensed under MIT license

  This is pure hardware-based PWM

  Version: 1.1.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K.Hoang      09/11/2022 Initial coding to support AVR Dx (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore
  1.1.0   K.Hoang      30/12/2022 Add support to AVR DD (AVR64DD, AVR32DDx, AVR16DD, etc.) using breaking DxCore v1.5.1+
*****************************************************************************************************************************/

#pragma once

#ifndef DX_PWM_H
#define DX_PWM_H

#if defined(BOARD_NAME)
  #undef BOARD_NAME
#endif

#ifndef _PWM_LOGLEVEL_
  #define _PWM_LOGLEVEL_        1
#endif

#if defined(DXCORE)

  #define PWM_USING_DX_CORE        true

  #if !defined(BOARD_NAME)

    ////////////////////////// __AVR_DA__ //////////////////////////

    #if ( defined(__AVR_AVR128DA64__) || defined(__AVR_AVR128DA48__) || defined(__AVR_AVR128DA32__) || defined(__AVR_AVR128DA28__) )
      #define BOARD_NAME      F("AVR128DA" )
    #elif ( defined(__AVR_AVR64DA64__) || defined(__AVR_AVR64DA48__) || defined(__AVR_AVR64DA32__) || defined(__AVR_AVR64DA28__) )
      #define BOARD_NAME      F("AVR64DA")
    #elif ( defined(__AVR_AVR32DA48__) || defined(__AVR_AVR32DA32__) || defined(__AVR_AVR32DA28__) )
      #define BOARD_NAME      F("AVR32DA")

      ////////////////////////// __AVR_DB__ //////////////////////////

    #elif ( defined(__AVR_AVR128DB64__) || defined(__AVR_AVR128DB48__) || defined(__AVR_AVR128DB32__) || defined(__AVR_AVR128DB28__) )
      #define BOARD_NAME      F("AVR128DB")
    #elif ( defined(__AVR_AVR64DB64__) || defined(__AVR_AVR64DB48__) || defined(__AVR_AVR64DB32__) || defined(__AVR_AVR64DB28__) )
      #define BOARD_NAME      F("AVR64DB")
    #elif ( defined(__AVR_AVR32DB48__) || defined(__AVR_AVR32DB32__) || defined(__AVR_AVR32DB28__) )
      #define BOARD_NAME      F("AVR32DB")

      ////////////////////////// __AVR_DD__ //////////////////////////

    #elif ( defined(__AVR_AVR64DD32__) || defined(__AVR_AVR64DD28__) || defined(__AVR_AVR64DD20__) || defined(__AVR_AVR64DD14__) )
      #define BOARD_NAME      F("AVR64DD")
      #if ( (DXCORE_MAJOR == 1) && (DXCORE_MINOR < 5) )
        #error AVR64DD not supported yet
      #endif
    #elif ( defined(__AVR_AVR32DD32__) || defined(__AVR_AVR32DD28__) || defined(__AVR_AVR32DD20__) || defined(__AVR_AVR32DD14__) )
      #define BOARD_NAME      F("AVR32DD")
      
      #if ( (DXCORE_MAJOR == 1) && (DXCORE_MINOR < 5) )
        #error AVR32DD not supported yet
      #endif

    #elif ( defined(__AVR_AVR16DD32__) || defined(__AVR_AVR16DD28__) || defined(__AVR_AVR16DD20__) || defined(__AVR_AVR16DD14__) )
      #define BOARD_NAME      F("AVR16DD")
      
      #if ( (DXCORE_MAJOR == 1) && (DXCORE_MINOR < 5) )
        #error AVR16DD not supported yet
      #endif

      ////////////////////////// __AVR_DU__ //////////////////////////

    #elif ( defined(__AVR_AVR64DU32__) || defined(__AVR_AVR64DU28__) )
      #define BOARD_NAME      F("AVR64DU")
    #elif ( defined(__AVR_AVR32DU32__) || defined(__AVR_AVR32DU28__) || defined(__AVR_AVR32DU20__) || defined(__AVR_AVR32DU14__) )
      #define BOARD_NAME      F("AVR32DU")
    #elif ( defined(__AVR_AVR16DU32__) || defined(__AVR_AVR16DU28__) || defined(__AVR_AVR16DU20__) || defined(__AVR_AVR16DU14__) )
      #define BOARD_NAME      F("AVR16DU")

      ////////////////////////// __AVR_EA__ //////////////////////////

    #elif ( defined(__AVR_AVR64EA48__) || defined(__AVR_AVR64EA32__) || defined(__AVR_AVR64EA28__) )
      #define BOARD_NAME      F("AVR64EA")
    #elif ( defined(__AVR_AVR32EA48__) || defined(__AVR_AVR32EA32__) || defined(__AVR_AVR32EA28__) )
      #define BOARD_NAME      F("AVR32EA")
    #elif ( defined(__AVR_AVR16EA48__) || defined(__AVR_AVR16EA32__) || defined(__AVR_AVR16EA28__) )
      #define BOARD_NAME      F("AVR16EA")
    #elif ( defined(__AVR_AVR8EA48__) || defined(__AVR_AVR8EA32__) || defined(__AVR_AVR8EA28__) )
      #define BOARD_NAME      F("AVR8EA")

      ////////////////////////////////////////////////////////////////

    #endif

  #endif  // #if !defined(BOARD_NAME)

#else

  #error This is designed only for AVRDx boards using DxCore or megaTinyCore ! Please check your Tools->Board setting

#endif

////////////////////////////////////////

#ifndef DX_PWM_VERSION
  #define DX_PWM_VERSION           F("Dx_PWM v1.1.0")

  #define DX_PWM_VERSION_MAJOR     1
  #define DX_PWM_VERSION_MINOR     1
  #define DX_PWM_VERSION_PATCH     0

  #define DX_PWM_VERSION_INT      1001000
#endif

////////////////////////////////////////

#include "Arduino.h"

#include "PWM_Generic_Debug.h"

////////////////////////////////////////

#define MAX_COUNT_8BIT            256UL
#define MAX_COUNT_12BIT           4096UL
#define MAX_COUNT_16BIT           65536UL

#define MAX_8BIT                  255UL
#define MAX_12BIT                 4095UL
#define MAX_16BIT                 65535UL

////////////////////////////////////////

#define TIMERA_RESOLUTION 65536UL   // TimerA is 16 bit for PWM
#define TIMERB_RESOLUTION 255UL     // TimerB is  8 bit for PWM

////////////////////////////////////////

#define CLK_TCA_FREQ            (250000UL)

#define TCB_CLKSEL_CLKDIV1      0x00
#define TCB_CLKSEL_CLKDIV2      0x02
#define TCB_CLKSEL_CLKDIV64     0x04      // TCA clock = 250KHz
#define TCB_CLKSEL_CLKTCA       0x04      // TCA clock = 250KHz

////////////////////////////////////////
////////////////////////////////////////

// From DxCore v1.5.1, must use __PeripheralControl instead of PeripheralControl
#if ( (DXCORE_MAJOR == 1) && (DXCORE_MINOR >= 5) )
  #define PeripheralControl			__PeripheralControl
#endif

extern uint8_t PeripheralControl;

////////////////////////////////////////
////////////////////////////////////////

class Dx_PWM
{
  public:

    Dx_PWM(const uint8_t& pin, const float& frequency, const float& dutycycle)
    {
      _timer      = digitalPinToTimer(pin);

      if (_timer != 0 && !(_timer & PeripheralControl))
      {
        _timer = 0;
        PWM_LOGDEBUG1("Dx_PWM: not PWM pin =", pin);

        return;
      }

      PWM_LOGDEBUG1("Dx_PWM: freq =", frequency);

      if (frequency < 367)
      {
        PWM_LOGERROR("Dx_PWM: frequency must > 367Hz. Trim @ 367Hz");
        _frequency = 367;
      }
      else
      {
        _frequency = frequency;
      }

      _pin        = pin;

      _dutycycle  = map(dutycycle, 0, 100.0f, 0, MAX_16BIT);

      _PWMEnabled = false;

      PWM_LOGDEBUG1("Dx_PWM: _dutycycle =", _dutycycle);

      pinMode(pin, OUTPUT);
    }

    ///////////////////////////////////////////

    ~Dx_PWM();

    ///////////////////////////////////////////
    ///////////////////////////////////////////

  private:

    ///////////////////////////////////////////

    void setPeriod_TimerA0(uint32_t microseconds) __attribute__((always_inline))
    {
      // TCA Clock is F_CPU / 64, 375.0KHz for 24MHz
      float TCA_Freq_mult = (float) 24000000 / F_CPU;

      PWM_LOGDEBUG5("setPeriod_TimerA0: F_CPU =", F_CPU, ", microseconds =", microseconds,
                    ", TCA_Freq_mult =", TCA_Freq_mult);

      uint16_t prescaler = 8;

      // To prevent unit32_t overflow @ low frequencies
      pwmPeriod = ( microseconds * (F_CPU / ( prescaler * 100000.0f)  ) ) / (TCA_Freq_mult * (10.0f) );

      if ( pwmPeriod < 256 )
      {
        TCA0.SPLIT.CTRLA   = (TCA_SPLIT_CLKSEL_DIV8_gc) | (TCA_SPLIT_ENABLE_bm);
        PWM_LOGDEBUG("setPeriod_TimerA0: CLKSEL_DIV8");
      }
      else if ( pwmPeriod < 256 * 2 )
      {
        prescaler = 16;
        TCA0.SPLIT.CTRLA   = (TCA_SPLIT_CLKSEL_DIV16_gc) | (TCA_SPLIT_ENABLE_bm);
        PWM_LOGDEBUG("setPeriod_TimerA0: CLKSEL_DIV16");

        pwmPeriod = round(pwmPeriod / 2.0f);
      }
      else if ( pwmPeriod < 256 * 8 )
      {
        prescaler = 64;
        TCA0.SPLIT.CTRLA   = (TCA_SPLIT_CLKSEL_DIV64_gc) | (TCA_SPLIT_ENABLE_bm);
        PWM_LOGDEBUG("setPeriod_TimerA0: CLKSEL_DIV64");

        pwmPeriod = round(pwmPeriod / 8.0f);
      }
      else if ( pwmPeriod < 256 * 32 )
      {
        prescaler = 256;
        TCA0.SPLIT.CTRLA   = (TCA_SPLIT_CLKSEL_DIV256_gc) | (TCA_SPLIT_ENABLE_bm);
        PWM_LOGDEBUG("setPeriod_TimerA0: CLKSEL_DIV256");

        pwmPeriod = round(pwmPeriod / 32.0f);
      }
      else
      {
        prescaler = 256;
        TCA0.SPLIT.CTRLA   = (TCA_SPLIT_CLKSEL_DIV256_gc) | (TCA_SPLIT_ENABLE_bm);
        PWM_LOGERROR("setPeriod_TimerA0: CLKSEL_DIV256, Too low PWM frequency. Trim for higher frequency");

        pwmPeriod = 0xFF;
      }

      // Must be 8-bit in split mode
      TCA0.SPLIT.CTRLD   = TCA_SPLIT_SPLITM_bm;
      TCA0.SPLIT.LPER    = pwmPeriod;
      TCA0.SPLIT.HPER    = pwmPeriod;

      _actualFrequency =  (F_CPU / prescaler) / pwmPeriod;

      PWM_LOGDEBUG3("setPeriod_TimerA0: pwmPeriod =", pwmPeriod, ", _actualFrequency =", _actualFrequency);
    }

    ///////////////////////////////////////////

#if defined(TCA1)

    void setPeriod_TimerA1(uint32_t microseconds) __attribute__((always_inline))
    {
      // TCA Clock is F_CPU / 64, 375.0KHz for 24MHz
      float TCA_Freq_mult = (float) 24000000 / F_CPU;

      uint16_t prescaler = 8;

      // To prevent unit32_t overflow @ low frequencies
      pwmPeriod = ( microseconds * (F_CPU / ( prescaler * 100000.0f)  ) ) / (TCA_Freq_mult * (10.0f) );

      PWM_LOGDEBUG7("setPeriod_TimerA1: F_CPU =", F_CPU, ", microseconds =", microseconds,
                    ", TCA_Freq_mult =", TCA_Freq_mult, ", beginning pwmPeriod = ", pwmPeriod);

      if ( pwmPeriod < 256 )
      {
        TCA1.SPLIT.CTRLA   = (TCA_SPLIT_CLKSEL_DIV8_gc) | (TCA_SPLIT_ENABLE_bm);
        PWM_LOGDEBUG("setPeriod_TimerA1: CLKSEL_DIV8");
      }
      else if ( pwmPeriod < 256 * 2 )
      {
        prescaler = 16;
        TCA1.SPLIT.CTRLA   = (TCA_SPLIT_CLKSEL_DIV16_gc) | (TCA_SPLIT_ENABLE_bm);
        PWM_LOGDEBUG("setPeriod_TimerA1: CLKSEL_DIV16");

        pwmPeriod = round(pwmPeriod / 2.0f);
      }
      else if ( pwmPeriod < 256 * 8 )
      {
        prescaler = 64;
        TCA1.SPLIT.CTRLA   = (TCA_SPLIT_CLKSEL_DIV64_gc) | (TCA_SPLIT_ENABLE_bm);
        PWM_LOGDEBUG("setPeriod_TimerA1: CLKSEL_DIV64");

        pwmPeriod = round(pwmPeriod / 8.0f);
      }
      else if ( pwmPeriod < 256 * 32 )
      {
        prescaler = 256;
        TCA1.SPLIT.CTRLA   = (TCA_SPLIT_CLKSEL_DIV256_gc) | (TCA_SPLIT_ENABLE_bm);
        PWM_LOGDEBUG("setPeriod_TimerA1: CLKSEL_DIV256");

        pwmPeriod = round(pwmPeriod / 32.0f);
      }
      else
      {
        prescaler = 256;
        TCA1.SPLIT.CTRLA   = (TCA_SPLIT_CLKSEL_DIV256_gc) | (TCA_SPLIT_ENABLE_bm);
        PWM_LOGERROR("setPeriod_TimerA1: CLKSEL_DIV256, Too low PWM frequency. Trim for higher frequency");

        pwmPeriod = 0xFF;
      }

      // Must be 8-bit in split mode
      TCA1.SPLIT.CTRLD   = TCA_SPLIT_SPLITM_bm;
      TCA1.SPLIT.LPER    = pwmPeriod;
      TCA1.SPLIT.HPER    = pwmPeriod;

      _actualFrequency =  (F_CPU / prescaler) / pwmPeriod;

      PWM_LOGDEBUG3("setPeriod_TimerA1: pwmPeriod =", pwmPeriod, ", _actualFrequency =", _actualFrequency);
    }
#endif
    ///////////////////////////////////////////

    void setPeriod_TimerB(unsigned long microseconds) __attribute__((always_inline))
    {
      const uint32_t cycles = ( ( (F_CPU / 100000) * microseconds ) / 10 );

      uint32_t cur_TCB_CLKSEL_VALUE = TCB_CLKSEL_CLKDIV1;

      PWM_LOGDEBUG3("setPeriod_TimerB: F_CPU =", F_CPU, ", cycles =", cycles);

      if (cycles < TIMERB_RESOLUTION)
      {
        PWM_LOGDEBUG("setPeriod_TimerB: cycles < TIMERB_RESOLUTION, using divider = 1");
        cur_TCB_CLKSEL_VALUE = TCB_CLKSEL_CLKDIV1;
        pwmPeriod = cycles;
      }
      else if (cycles / 2 < TIMERB_RESOLUTION)
      {
        PWM_LOGDEBUG("setPeriod_TimerB: cycles < TIMERB_RESOLUTION * 2, using divider = 2");
        cur_TCB_CLKSEL_VALUE = TCB_CLKSEL_CLKDIV2;
        pwmPeriod = cycles / 2;
      }
      else if (cycles / 64 < TIMERB_RESOLUTION)
      {
        PWM_LOGDEBUG("setPeriod_TimerB: cycles < TIMERB_RESOLUTION * 64, using divider = 64");
        cur_TCB_CLKSEL_VALUE = TCB_CLKSEL_CLKDIV64;
        pwmPeriod = cycles / 64;
      }
      else
      {
        PWM_LOGDEBUG1("setPeriod_TimerB: Error, min freq (Hz) =", (float) F_CPU / (64 *  TIMERB_RESOLUTION) );

        pwmPeriod = TIMERB_RESOLUTION - 1;
      }

      timer_B = ((TCB_t *)&TCB0 + (_timer - TIMERB0));

      timer_B->CTRLA = cur_TCB_CLKSEL_VALUE | TCB_ENABLE_bm;       // Enable timer

      // Assign 8-bit period TODO, mapping to 8-bit
      timer_B->CCMPL = pwmPeriod;

      _actualFrequency = (float) F_CPU / ( cycles);

      PWM_LOGDEBUG3("setPeriod_TimerB: pwmPeriod =", pwmPeriod, ", _actualFrequency =", _actualFrequency);
    }

    ///////////////////////////////////////////

    void setPeriod_TimerD0(uint32_t microseconds) __attribute__((always_inline))
    {
      // 12-bit TCD0
      // TCD Clock min is F_CPU / 32
      float TCD_Freq_mult = (float) 24000000 / F_CPU;

      uint16_t prescaler = 1;

      // To prevent unit32_t overflow @ low frequencies
      pwmPeriod = ( microseconds * (F_CPU / ( prescaler * 100000.0f)  ) ) / (TCD_Freq_mult * (10.0f) );

      PWM_LOGDEBUG7("setPeriod_TimerD0: F_CPU =", F_CPU, ", microseconds =", microseconds,
                    ", TCD_Freq_mult =", TCD_Freq_mult, ", beginning pwmPeriod = ", pwmPeriod);

      if ( pwmPeriod < (uint32_t) 4096 )
      {
        PWM_LOGDEBUG("setPeriod_TimerD0: CLKSEL_DIV1");
      }
      else if ( pwmPeriod < (uint32_t) 4096 * 4 )
      {
        prescaler = 4;
        PWM_LOGDEBUG("setPeriod_TimerD0: CLKSEL_DIV4");

        pwmPeriod = round(pwmPeriod / 4.0f);
      }
      else if ( pwmPeriod < (uint32_t) 4096 * 32 )
      {
        prescaler = 32;
        PWM_LOGDEBUG("setPeriod_TimerD0: CLKSEL_DIV32");

        pwmPeriod = round(pwmPeriod / 32.0f);
      }
      else
      {
        prescaler = 32;
        PWM_LOGERROR("setPeriod_TimerD0: CLKSEL_DIV32, Too low PWM frequency. Trim for higher frequency");

        // 12-bit
        pwmPeriod = MAX_12BIT;    //0x0FFF;
      }

      PWM_LOGDEBUG1("setPeriod_TimerD0: pwmPeriod =", pwmPeriod);

      TCD0.CMPACLR  = pwmPeriod;      //0x0FFF;
      TCD0.CTRLC    = 0x80;
      TCD0.CTRLB    = TIMERD0_WGMODE_SETTING;
      TCD0.CMPBCLR  = pwmPeriod;    //TIMERD0_TOP_SETTING;

#if defined(TIMERD0_SET_CLOCK)
      _PROTECTED_WRITE(CLKCTRL_OSCHFCTRLA, (TIMERD0_SET_CLOCK));
#endif

      // #define TIMERD0_CLOCK_SETTING (TCD_CNTPRES_DIV4_gc | TCD_SYNCPRES_DIV1_gc | TCD_CLKSEL_OSCHF_gc)
      // #define TIMERD0_CLOCK_SETTING (TCD_CNTPRES_DIV32_gc | TCD_SYNCPRES_DIV1_gc | TCD_CLKSEL_OSCHF_gc)

      TCD0.CTRLA    = TIMERD0_CLOCK_SETTING | TCD_ENABLE_bm;

      //TCD0.CTRLA    = (TCD_CNTPRES_DIV4_gc | TCD_SYNCPRES_DIV1_gc | TCD_CLKSEL_OSCHF_gc) | TCD_ENABLE_bm;

      _actualFrequency =  (F_CPU / prescaler) / pwmPeriod;

      PWM_LOGDEBUG3("setPeriod_TimerD0: pwmPeriod =", pwmPeriod, ", _actualFrequency =", _actualFrequency);
    }

    ///////////////////////////////////////////
    ///////////////////////////////////////////

  public:

    // dutycycle from 0-65536 for 0%-100% to make use of 16-bit top register
    bool setPWM_Int(const uint8_t& pin, const float& frequency, uint16_t dutycycle)
    {
      uint8_t bit_mask = digitalPinToBitMask(pin);

      if (bit_mask == NOT_A_PIN)
      {
        PWM_LOGERROR1("setPWM_Int: NOT_A_PIN, pin =", pin);

        return false;
      }

      pinMode(pin, OUTPUT);

      uint8_t digital_pin_timer =  digitalPinToTimer(pin); // NON-TCA timer!

      if (digital_pin_timer != 0 && !(digital_pin_timer & PeripheralControl))
      {
        digital_pin_timer = 0;
      }

      ///////////////////////////////////////////

      uint8_t* timer_cmp_out;

      // Timer TCA is 16-bit

      if (bit_mask < 0x40 )
      {
        uint8_t portnum  = digitalPinToPort(pin);
        uint8_t tcaroute = PORTMUX.TCAROUTEA;

        if ((portnum == (tcaroute & (0x07))) && (PeripheralControl & TIMERA0))
        {
          if ( (_frequency != frequency) || !_PWMEnabled )
          {
            setPeriod_TimerA0(1000000UL / frequency);
            _frequency = frequency;
            _PWMEnabled = true;
          }

          _dutycycle = ( (uint32_t) (pwmPeriod + 1) * (dutycycle + 1) ) >> 16;

          if (_dutycycle < 254)
            _dutycycle++;

          uint8_t offset = 0;

          if (bit_mask > 0x04)   // separate high from low timers
          {
            bit_mask <<= 1;
            offset = 1;
          }

          if (bit_mask & 0x44)
            offset += 4;
          else if (bit_mask & 0x22)
            offset += 2;

          timer_cmp_out = ((uint8_t*) (&TCA0.SPLIT.LCMP0)) + offset;

          PWM_LOGDEBUG1("setPWM_Int 4: _dutycycle =", _dutycycle);

          (*timer_cmp_out) = (_dutycycle);

          TCA0.SPLIT.CTRLB |= bit_mask;

          return true;
        }

        ///////////////////////////////////////////

#if defined(TCA1)
        /*  case TIMERA1:
        */
        tcaroute &= (0x18);

        if (((portnum == 6 && tcaroute == 0x18) || (portnum == 1 && tcaroute == 0)) && (PeripheralControl & TIMERA1))
        {
          if ( (_frequency != frequency) || !_PWMEnabled )
          {
            setPeriod_TimerA1(1000000UL / frequency);
            _frequency = frequency;
            _PWMEnabled = true;
          }

          _dutycycle = ( (uint32_t) (pwmPeriod + 1) * (dutycycle + 1) ) >> 16;

          if (_dutycycle < 254)
            _dutycycle++;

          uint8_t offset = 0;

          if (bit_mask > 0x04)
          {
            bit_mask <<= 1;
            offset = 1;
          }

          if (bit_mask & 0x44)
            offset += 4;
          else if (bit_mask & 0x22)
            offset += 2;

          timer_cmp_out = ((uint8_t*) (&TCA1.SPLIT.LCMP0)) + offset;

          PWM_LOGDEBUG1("setPWM_Int: TIMER_TCA1, _dutycycle =", _dutycycle);

          (*timer_cmp_out) = (_dutycycle);

          TCA1.SPLIT.CTRLB |= bit_mask;

          return true;
        }

#endif
      }

      ///////////////////////////////////////////

      switch (digital_pin_timer)
      {
        case TIMERB0:
        case TIMERB1:
        case TIMERB2:
        case TIMERB3:
        case TIMERB4:

          TCB_t *timer_B;

          timer_B = ((TCB_t *)&TCB0 + (digital_pin_timer - TIMERB0));

          // 8 bit PWM mode
          timer_B->CTRLB = (TCB_CNTMODE_PWM8_gc);

          if ( (_frequency != frequency) || !_PWMEnabled )
          {
            setPeriod_TimerB(1000000UL / frequency);
            _frequency = frequency;
            _PWMEnabled = true;
          }

          dutycycle = map(dutycycle, 0, MAX_16BIT, 0, pwmPeriod);

          // start from 0, so to add 1 to DC and period
          PWM_LOGDEBUG3("setPWM_Int: TIMERB, dutycycle =", dutycycle, ", DC % =", dutycycle * 100.0f / pwmPeriod);

          // set duty cycle
          timer_B->CCMPH = dutycycle + 1;

          // Enable Timer Output
          timer_B->CTRLB |= (TCB_CCMPEN_bm);

          break;

          ///////////////////////////////////////////

#if (defined(TCD0) && defined(USE_TIMERD0_PWM))

        case TIMERD0:
        {
          if (_frequency != frequency)
          {
            PWM_LOGDEBUG3("setPWM_Int: setPeriod_TimerD0, dutycycle =", dutycycle, ", frequency =", frequency);

            setPeriod_TimerD0(1000000UL / frequency);
            _frequency = frequency;
          }

          PWM_LOGDEBUG3("setPWM_Int: pwmPeriod =", pwmPeriod, ", frequency =", frequency);

          dutycycle = map(dutycycle, 0, MAX_16BIT, 0, pwmPeriod);

          PWM_LOGDEBUG3("setPWM_Int: TIMERD0, dutycycle =", dutycycle, ", DC % =", dutycycle * 100.0f / pwmPeriod);


          PWM_LOGERROR("setPWM_Int: TIMERD0, not supported yet");

          // KH, not supported yet
          return false;
        }

        break;// case TIMERD0:

#endif      // #if (defined(TCD0) && defined(USE_TIMERD0_PWM))

        ///////////////////////////////////////////

        /* If non timer pin, or unknown timer definition. */
        /* do a digital write */
        case NOT_ON_TIMER:
        default:

          PWM_LOGERROR1("setPWM_Int: NOT_ON_TIMER, pin =", pin);

          if (dutycycle < 128)
          {
            digitalWrite(pin, LOW);
          }
          else
          {
            digitalWrite(pin, HIGH);
          }

          break;
      }

      // End switch case
      ///////////////////////////////////////////

      _PWMEnabled = true;

      return true;
    }

    ///////////////////////////////////////////

    bool setPWM()
    {
      return setPWM_Int(_pin, _frequency, _dutycycle);
    }

    ///////////////////////////////////////////

    bool setPWM(const uint8_t& pin, const float& frequency, const float& dutycycle)
    {
      _dutycycle = map(dutycycle, 0, 100.0f, 0, MAX_16BIT);

      PWM_LOGDEBUG1("setPWM: _dutycycle =", _dutycycle);

      return setPWM_Int(pin, frequency, _dutycycle);
    }

    ///////////////////////////////////////////

    bool setPWM_Period(const uint8_t& pin, const float& period_us, const float& dutycycle)
    {
      _dutycycle = map(dutycycle, 0, 100.0f, 0, MAX_16BIT);

      PWM_LOGDEBUG1("setPWM_Period: _dutycycle =", _dutycycle);

      return setPWM_Int(pin, 1000000.0f / period_us, _dutycycle);
    }

    ///////////////////////////////////////////

    // Must have same frequency
    bool setPWM_manual(const uint8_t& pin, const uint16_t& DCValue)
    {
      // Not the same pin or overvalue
      if (_pin != pin)
        return false;

      return setPWM_Int(pin, _frequency, DCValue);
    }

    ///////////////////////////////////////////

    inline float getActualDutyCycle()
    {
      // start from 0, so to add 1 to DC and period
      return ( (float) (_dutycycle + 1) * 100 / pwmPeriod);
    }

    ///////////////////////////////////////////

    inline float getActualFreq()
    {
      return _actualFrequency;
    }

    ///////////////////////////////////////////

    inline float getPWMPeriod()
    {
      return pwmPeriod;
    }

    ///////////////////////////////////////////

    inline uint32_t get_freq_CPU()
    {
      return F_CPU;
    }

    ///////////////////////////////////////////

    inline uint32_t getPin()
    {
      return _pin;
    }

    ///////////////////////////////////////////

    bool isPWMEnabled()
    {
      return _PWMEnabled;
    }

    ///////////////////////////////////////////////////////////////////

  private:

    float           _actualFrequency;
    float           _frequency;

    // dutycycle from 0-65535 for 0%-100% to make use of 16-bit top register
    // _dutycycle = map(dutycycle, 0, 100.0f, 0, 65535) for better accuracy
    uint16_t        _dutycycle;
    //////////

    uint8_t         _pin;

#define INVALID_TIMER     255

    uint8_t         _timer = INVALID_TIMER;

    TCB_t*          timer_B;

    uint16_t*       timer_cmp_out;

    uint16_t        pwmPeriod;

    bool            _PWMEnabled = false;

    ///////////////////////////////////////////
};

///////////////////////////////////////////


#endif    // DX_PWM_H

