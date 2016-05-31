/* Copyright 2016, XXXXXXXXX  
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif
#include "led.h"

/*==================[macros and definitions]=================================*/
#define OUT 1
#define PUERTO_5_LED_R 1<<0
#define PUERTO_5_LED_G 1<<1
#define PUERTO_5_LED_B 1<<2
#define PUERTO_0_YELLOW 1<<14
#define PUERTO_1_ROJO 1<<11
#define PUERTO_1_GREEN 1<<12
#define NUM_PUERTO_5 5
#define NUM_PUERTO_0 0
#define NUM_PUERTO_1 1
#define PAQUETE_LED 2
#define PIN_LED_2_0 0
#define PIN_LED_2_1 1
#define PIN_LED_2_2 2
#define PIN_LED_2_10 10
#define PIN_LED_2_11 11
#define PIN_LED_2_12 12
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/


/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */
void IniciaPuerto ()
{
	Chip_GPIO_Init(LPC_GPIO_PORT);
	Chip_SCU_PinMux (PAQUETE_LED,PIN_LED_2_0,MD_PUP,FUNC4); /* Map P2 0 in GPIO5[0], LED0R y hobbled el
	pull up*/
	Chip_SCU_PinMux (PAQUETE_LED,PIN_LED_2_1,MD_PUP,FUNC4);
	Chip_SCU_PinMux (PAQUETE_LED,PIN_LED_2_2,MD_PUP,FUNC4);
	Chip_SCU_PinMux (PAQUETE_LED,PIN_LED_2_10,MD_PUP,FUNC0);
	Chip_SCU_PinMux (PAQUETE_LED,PIN_LED_2_11,MD_PUP,FUNC0);
	Chip_SCU_PinMux (PAQUETE_LED,PIN_LED_2_12,MD_PUP,FUNC0);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,NUM_PUERTO_5,PUERTO_5_LED_R, OUT);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,NUM_PUERTO_5,PUERTO_5_LED_G, OUT);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,NUM_PUERTO_5,PUERTO_5_LED_B, OUT);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,NUM_PUERTO_0,PUERTO_0_YELLOW, OUT);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,NUM_PUERTO_1,PUERTO_1_ROJO, OUT);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,NUM_PUERTO_1,PUERTO_1_GREEN, OUT);
}
void PrendeLed(uint8_t led)
{
	switch(led){
	case LED_R:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,NUM_PUERTO_5,LED_R);
		break;
	case LED_G:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,NUM_PUERTO_5,LED_G);
		break;
	case LED_B:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,NUM_PUERTO_5,LED_B);
		break;
	case ROJO:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,NUM_PUERTO_1,ROJO);
		break;
	case YELLOW:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,NUM_PUERTO_0,YELLOW);
		break;
	case GREEN:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,NUM_PUERTO_1,GREEN);
		break;
	}
}
void ApagaLed(uint8_t led)
{
	switch(led){
	case LED_R:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,NUM_PUERTO_5,LED_R);
		break;
	case LED_G:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,NUM_PUERTO_5,LED_G);
		break;
	case LED_B:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,NUM_PUERTO_5,LED_B);
		break;
	case ROJO:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,NUM_PUERTO_1,ROJO);
		break;
	case YELLOW:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,NUM_PUERTO_0,YELLOW);
		break;
	case GREEN:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,NUM_PUERTO_1,GREEN);
		break;
	}
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

