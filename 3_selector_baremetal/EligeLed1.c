/* Copyright 2016, XXXXXX
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

/** \brief Blinking Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
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
#include "EligeLed.h"       /* <= own header */
#include "tecla.h"
#include "timer.h"
#include "led.h"
#include "stdint.h"
#
/*==================[macros and definitions]=================================*/
#define DELAY_LOW 1000
#define DELAY_HIGH 100

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
uint8_t tecla;
uint32_t c,d;
	void ISR_RIT (void)
	{

		switch(c){
				case 1:
					ConmutaLed(LED_R);
					ApagaLed(LED_G);
					ApagaLed(LED_B);
					ApagaLed(ROJO);
					ApagaLed(YELLOW);
					ApagaLed(GREEN);
					ClearRIT();
					break;
				case 2:
					ConmutaLed(LED_G);
					ApagaLed(LED_R);
					ApagaLed(LED_B);
					ApagaLed(ROJO);
					ApagaLed(YELLOW);
					ApagaLed(GREEN);
					break;
				case 3:
					ConmutaLed(LED_B);
					ApagaLed(LED_R);
					ApagaLed(LED_G);
					ApagaLed(ROJO);
					ApagaLed(YELLOW);
					ApagaLed(GREEN);
					break;
				case 4:
					ConmutaLed(YELLOW);
					ApagaLed(LED_R);
					ApagaLed(LED_B);
					ApagaLed(ROJO);
					ApagaLed(LED_G);
					ApagaLed(GREEN);
					break;
				case 5:
					ConmutaLed(ROJO);
					ApagaLed(LED_R);
					ApagaLed(LED_B);
					ApagaLed(LED_G);
					ApagaLed(YELLOW);
					ApagaLed(GREEN);
					break;
				case 6:
					ConmutaLed(GREEN);
					ApagaLed(LED_R);
					ApagaLed(LED_B);
					ApagaLed(ROJO);
					ApagaLed(YELLOW);
					ApagaLed(LED_G);
					break;
					}
		ClearRIT();
	}

int main(void)
{

   /* perform the needed initialization here */
    c=1;
    IniciaPuerto();
	SeteaRIT(1000);
	IniciaTecla();
	IniciaRIT();

	/*for(;;)
	{
		while (LeeTecla()==0);
		tecla = LeeTecla();
		for ( d = 1 ; d <= 3276700; d++ ); /*delay ()*/
		/*switch(tecla)
		{
			case TECLA3:
				SeteaRIT(50);
				break;
			case TECLA4:
				SeteaRIT(1000);
				break;
		}*/


		/*switch(tecla)
		{
			case TECLA1:
				c=c+1;
				break;
			case TECLA2:
				c=c-1;
				break;
		}

	}*/
	for (;;);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

