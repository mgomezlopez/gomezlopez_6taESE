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
#define IN 0
#define PAQUETE_TECLA 1
#define PIN_TECLA_1_0 0
#define PIN_TECLA_1_1 1
#define PIN_TECLA_1_2 2
#define PIN_TECLA_1_6 6
#define NUM_PUERTO_0 0
#define NUM_PUERTO_1 1
#define PUERTO_0_4 1<<4
#define PUERTO_0_8 1<<8
#define PUERTO_0_9 1<<9
#define PUERTO_1_9 1<<9
#define TECLA1 8
#define TECLA2 4
#define TECLA3 2
#define TECLA4 1

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
void IniciaTecla ()
{
	Chip_GPIO_Init(LPC_GPIO_PORT);
	Chip_SCU_PinMux (PAQUETE_TECLA,PIN_TECLA_1_0,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	Chip_SCU_PinMux (PAQUETE_TECLA,PIN_TECLA_1_1,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	Chip_SCU_PinMux (PAQUETE_TECLA,PIN_TECLA_1_2,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	Chip_SCU_PinMux (PAQUETE_TECLA,PIN_TECLA_1_6,MD_PUP|MD_EZI|MD_ZI,FUNC0);

	Chip_GPIO_SetDir(LPC_GPIO_PORT,NUM_PUERTO_0,PUERTO_0_4,IN);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,NUM_PUERTO_0,PUERTO_0_8,IN);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,NUM_PUERTO_0,PUERTO_0_9,IN);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,NUM_PUERTO_1,PUERTO_1_9,IN);

}
uint8_t LeeTecla(void)
{
	uint8_t tecla;

	if (!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,NUM_PUERTO_0,4))
	{
		tecla=TECLA1;//tecla1
		return tecla;
	}
	else if (!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,NUM_PUERTO_0,8))
	{
		tecla=TECLA2;//tecla2
		return tecla;
	}
	else if (!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,NUM_PUERTO_0,9))
	{
		tecla=TECLA3;//tecla3
		return tecla;
	}
	else if (!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,NUM_PUERTO_1,9))
	{
		tecla=TECLA4;//tecla4
		return tecla;
	}
	else
	{
		return 0;
	}
}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

