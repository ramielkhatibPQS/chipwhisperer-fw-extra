/* This file combines several STM32F4 HAL Functions into one file. This was done
   for space reasons, to avoid having several MB of HAL functions that most people
   will not use. In addition this HAL is slightly less demanding (no interrupts),
   but less robust as doesn't implement the timeouts.
   
   The original HAL files are COPYRIGHT STMicroelectronics, as shown below:
*/

/*
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
*/ 


#ifndef STM32F2_HAL_LOWLEVEL_H
#define STM32F2_HAL_LOWLEVEL_H

/* ########################## HSE/HSI Values adaptation ##################### */
/**
  * @brief Adjust the value of External High Speed oscillator (HSE) used in your application.
  *        This value is used by the RCC HAL module to compute the system frequency
  *        (when HSE is used as system clock source, directly or through the PLL).
  */
#if !defined  (HSE_VALUE)
  #define HSE_VALUE    (7372800U) /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSE_STARTUP_TIMEOUT)
  #define HSE_STARTUP_TIMEOUT    (100U)   /*!< Time out for HSE start up, in ms */
#endif /* HSE_STARTUP_TIMEOUT */

#if !defined (HSE_PLLM_VALUE)
  #define HSE_PLLM_VALUE (7U)
#endif /* HSE_PLLM_VALUE */

#if !defined (HSE_PLLN_VALUE)
  #define HSE_PLLN_VALUE (319U)
#endif /* HSE_PLLN_VALUE */

#if !defined (HSE_PLLP_VALUE)
  #define HSE_PLLP_VALUE (8U)
#endif /* HSE_PLLP_VALUE */

#if !defined (HSE_PLLQ_VALUE)
  #define HSE_PLLQ_VALUE (7U)
#endif /* HSE_PLLQ_VALUE */

#if !defined (HSE_AHBCLKDIV_VALUE)
  #define HSE_AHBCLKDIV_VALUE (1U)
#endif /* HSE_AHBCLKDIV_VALUE */

#if !defined (HSE_APB1CLKDIV_VALUE)
  #if defined(USE_PLL)
    #define HSE_APB1CLKDIV_VALUE (2U)        /* PCLK1 max freq is 30 MHz */
  #else
    #define HSE_APB1CLKDIV_VALUE (1U)
  #endif
#endif /* HSE_APB1CLKDIV_VALUE */

#if !defined (HSE_APB2CLKDIV_VALUE)
  #define HSE_APB2CLKDIV_VALUE (1U)           /* PCLK2 max freq is 60 MHz */
#endif /* HSE_APB2CLKDIV_VALUE */

/**
  * @brief Internal High Speed oscillator (HSI) value.
  *        This value is used by the RCC HAL module to compute the system frequency
  *        (when HSI is used as system clock source, directly or through the PLL).
  */
#if !defined  (HSI_VALUE)
  #define HSI_VALUE    (16000000U) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

/**
  * @brief Internal Low Speed oscillator (LSI) value.
  */
#if !defined  (LSI_VALUE)
 #define LSI_VALUE  (32000U)
#endif /* LSI_VALUE */                      /*!< Value of the Internal Low Speed oscillator in Hz
                                             The real value may vary depending on the variations
                                             in voltage and temperature.  */
/**
  * @brief External Low Speed oscillator (LSE) value.
  */
#if !defined  (LSE_VALUE)
 #define LSE_VALUE  (32768U)    /*!< Value of the External Low Speed oscillator in Hz */
#endif /* LSE_VALUE */

#if !defined  (LSE_STARTUP_TIMEOUT)
  #define LSE_STARTUP_TIMEOUT    (5000U)   /*!< Time out for LSE start up, in ms */
#endif /* LSE_STARTUP_TIMEOUT */

/**
  * @brief External clock source for I2S peripheral
  *        This value is used by the I2S HAL module to compute the I2S clock source
  *        frequency, this source is inserted directly through I2S_CKIN pad.
  */
#if !defined  (EXTERNAL_CLOCK_VALUE)
  #define EXTERNAL_CLOCK_VALUE    (12288000U) /*!< Value of the External oscillator in Hz*/
#endif /* EXTERNAL_CLOCK_VALUE */

/* Tip: To avoid modifying this file each time you need to use different HSE,
   ===  you can define the HSE value in your toolchain compiler preprocessor. */

/* ########################### UART Configuration ######################### */
/**
  * @brief UART initial baudrate
  */
#if !defined(UART_INITBAUD)
  #if SS_VER==SS_VER_2_1
    #define UART_INITBAUD 230400
  #else
    #define UART_INITBAUD 38400
  #endif
#endif

/* ########################### System Configuration ######################### */
/**
  * @brief This is the HAL system configuration section
  */
#define  VDD_VALUE                    (3300U) /*!< Value of VDD in mv */
#define  TICK_INT_PRIORITY            (0x0FU) /*!< tick interrupt priority */
#define  USE_RTOS                     0U
#define  PREFETCH_ENABLE              0U /* The prefetch will be enabled in SystemClock_Config(), depending on the used
                                            STM32F405/415/07/417 device: RevA (prefetch must be off) or RevZ (prefetch can be on/off) */
#define  INSTRUCTION_CACHE_ENABLE     1U
#define  DATA_CACHE_ENABLE            1U


//#define STM32F215xx
#include "stm32f2xx.h"

/* ########################### Generated Values ######################### */
#if defined(USE_INTERNAL_CLK)
    #define SYSCLK_FREQ (HSI_VALUE)
#elif defined(USE_PLL)
    #define SYSCLK_FREQ (HSE_VALUE / HSE_PLLM_VALUE * HSE_PLLN_VALUE / HSE_PLLP_VALUE)
#else
    #define SYSCLK_FREQ (HSE_VALUE)
#endif

#define HCLK_FREQ  (SYSCLK_FREQ / HSE_AHBCLKDIV_VALUE)
#define PCLK1_FREQ (HCLK_FREQ / HSE_APB1CLKDIV_VALUE)
#define PCLK2_FREQ (HCLK_FREQ / HSE_APB2CLKDIV_VALUE)

#if HSE_VALUE > 26000000U
  #error "Maximum allowed HSE_VALUE is 26MHz"
#endif
#if HCLK_FREQ > 120000000U
  #error "Maximum allowed HCLK_FREQ is 120MHz"
#endif
#if PCLK1_FREQ > 30000000U
  #error "Maximum allowed PCLK1_FREQ is 30MHz"
#endif
#if PCLK2_FREQ > 60000000U
  #error "Maximum allowed PCLK2_FREQ is 60MHz"
#endif

#if HSE_PLLM_VALUE < 2U || HSE_PLLM_VALUE > 63U
  #error "HSE_PLLM_VALUE not supported"
#endif
#if HSE_PLLN_VALUE < 192U || HSE_PLLN_VALUE > 432U
  #error "HSE_PLLN_VALUE not supported"
#endif
#if HSE_PLLP_VALUE != 2U && HSE_PLLP_VALUE != 4U && HSE_PLLP_VALUE != 6U && HSE_PLLP_VALUE != 8U
  #error "HSE_PLLP_VALUE not supported"
#endif
#if HSE_PLLQ_VALUE < 2U || HSE_PLLQ_VALUE > 15U
  #error "HSE_PLLQ_VALUE not supported"
#endif

#if HSE_AHBCLKDIV_VALUE == 1
  #define HSE_AHBCLKDIV_HVALUE RCC_CFGR_HPRE_DIV1
#elif HSE_AHBCLKDIV_VALUE == 2
  #define HSE_AHBCLKDIV_HVALUE RCC_CFGR_HPRE_DIV2
#elif HSE_AHBCLKDIV_VALUE == 4
  #define HSE_AHBCLKDIV_HVALUE RCC_CFGR_HPRE_DIV4
#elif HSE_AHBCLKDIV_VALUE == 8
  #define HSE_AHBCLKDIV_HVALUE RCC_CFGR_HPRE_DIV8
#elif HSE_AHBCLKDIV_VALUE == 16
  #define HSE_AHBCLKDIV_HVALUE RCC_CFGR_HPRE_DIV16
#elif HSE_AHBCLKDIV_VALUE == 64
  #define HSE_AHBCLKDIV_HVALUE RCC_CFGR_HPRE_DIV64
#elif HSE_AHBCLKDIV_VALUE == 128
  #define HSE_AHBCLKDIV_HVALUE RCC_CFGR_HPRE_DIV128
#elif HSE_AHBCLKDIV_VALUE == 256
  #define HSE_AHBCLKDIV_HVALUE RCC_CFGR_HPRE_DIV256
#elif HSE_AHBCLKDIV_VALUE == 512
  #define HSE_AHBCLKDIV_HVALUE RCC_CFGR_HPRE_DIV512
#else
  #error "HSE_AHBCLKDIV_VALUE not supported"
#endif

#if HSE_APB1CLKDIV_VALUE == 1
  #define HSE_APB1CLKDIV_HVALUE RCC_CFGR_PPRE1_DIV1
#elif HSE_APB1CLKDIV_VALUE == 2
  #define HSE_APB1CLKDIV_HVALUE RCC_CFGR_PPRE1_DIV2
#elif HSE_APB1CLKDIV_VALUE == 4
  #define HSE_APB1CLKDIV_HVALUE RCC_CFGR_PPRE1_DIV4
#elif HSE_APB1CLKDIV_VALUE == 8
  #define HSE_APB1CLKDIV_HVALUE RCC_CFGR_PPRE1_DIV8
#elif HSE_APB1CLKDIV_VALUE == 16
  #define HSE_APB1CLKDIV_HVALUE RCC_CFGR_PPRE1_DIV16
#else
  #error "HSE_APB1CLKDIV_VALUE not supported"
#endif

#if HSE_APB2CLKDIV_VALUE == 1
  #define HSE_APB2CLKDIV_HVALUE RCC_CFGR_PPRE2_DIV1
#elif HSE_APB2CLKDIV_VALUE == 2
  #define HSE_APB2CLKDIV_HVALUE RCC_CFGR_PPRE2_DIV2
#elif HSE_APB2CLKDIV_VALUE == 4
  #define HSE_APB2CLKDIV_HVALUE RCC_CFGR_PPRE2_DIV4
#elif HSE_APB2CLKDIV_VALUE == 8
  #define HSE_APB2CLKDIV_HVALUE RCC_CFGR_PPRE2_DIV8
#elif HSE_APB2CLKDIV_VALUE == 16
  #define HSE_APB2CLKDIV_HVALUE RCC_CFGR_PPRE2_DIV16
#else
  #error "HSE_APB2CLKDIV_VALUE not supported"
#endif

#if HCLK_FREQ <= 30000000U
  #define FLASH_LATENCY_HVALUE FLASH_ACR_LATENCY_0WS
#elif HCLK_FREQ <= 60000000U
  #define FLASH_LATENCY_HVALUE FLASH_ACR_LATENCY_1WS
#elif HCLK_FREQ <= 90000000U
  #define FLASH_LATENCY_HVALUE FLASH_ACR_LATENCY_2WS
#elif HCLK_FREQ <= 120000000U
  #define FLASH_LATENCY_HVALUE FLASH_ACR_LATENCY_3WS
#else
  #error "HCLK_FREQ not supported"
#endif

#endif