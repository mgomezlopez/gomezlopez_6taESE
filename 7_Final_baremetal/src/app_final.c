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
#include "app_final.h"       /* <= own header */
#include "adc.h"
#include "dac.h"
#include "tecla.h"
#include "timer.h"
#include "led.h"
#include "uart.h"
#include "stdint.h"
/*==================[macros and definitions]=================================*/


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
uint8_t dec,un,rx;
uint16_t mil,cen, resto_mil,resto_cen,resto_dec;
int cc=0;
int c=0;
int d,nn;
int n=0;
float e=0;
float ganancia, offset;
float amplitud;
uint16_t adc=0;
uint32_t dac_int;
int tecla;

void ISR_RIT (void)
	{
	if (n<6)
	{
		n=n+1;
		e=620;
	}
	else if (n<11)
	{
		n=n+1;
		e=310;
	}
	else {
		n=0;
	}
	dac_int=(uint32_t) e;
	EscribeDAC(dac_int);
	adc=LeeADC();
	amplitud=(float) adc;
	amplitud=ganancia*amplitud+offset;
	if (nn<50) {
		nn=nn+1;
		}
	else if (nn==50){
		nn=0;
		ConmutaLed(GREEN);
		EscribeUART('M');EscribeUART('A');EscribeUART('X');EscribeUART(':');
		EscribeUART('\n');EscribeUART('\r');

		EscribeUART('M');EscribeUART('I');EscribeUART('N');EscribeUART(':');
		EscribeUART('\n');EscribeUART('\r');

		EscribeUART('G');EscribeUART('A');EscribeUART('N');EscribeUART(':');
		EscribeUART('\n');EscribeUART('\r');

		EscribeUART('O');EscribeUART('F');EscribeUART('F');EscribeUART('S');
		EscribeUART('E');EscribeUART('T');EscribeUART(':');	EscribeUART('\n');EscribeUART('\r');
	}
	ClearRIT();
	}
int main(void)
{
    IniciaADC();
	IniciaDAC();
	IniciaRIT();
	SeteaRIT(10);
	IniciaPuerto();
	IniciaUART();
	IniciaTecla();

	for(;;)
	{
		while (LeeTecla()==0);
		tecla = LeeTecla();
		for ( d = 1 ; d <= 3276700; d++ ); /*delay ()*/
		switch(tecla)	{
			case TECLA1:
				if (c<6)
				{
				c=c+1;
				}
				else
				{
				c=c;
				}
				break;
			case TECLA2:
				if (c>1)
				{
				c=c-1;
				}
				else
				{
				c=c;
				}
				break;
			case TECLA3:
				//periodo=T_LOW;
				if (cc<6)
				{
				cc=cc+1;
				}
				else
				{
				cc=cc;
				}
				break;

			case TECLA4:
				if (cc>1)
				{
				cc=cc-1;
				}
				else
				{
				cc=cc;
				}
				break;
			}
		switch(c)	{
					case 1:
						ganancia=0.8;
						break;
					case 2:
						ganancia=0.9;
						break;
					case 3:
						ganancia=1;
						break;
					case 4:
						ganancia=1.1;
						break;
					case 5:
						ganancia=1.2;
						break;
					}
		switch(cc)	{
					case 1:
						offset-0.2;
						break;
					case 2:
						offset=-0.1;
						break;
					case 3:
						offset=0;
						break;
					case 4:
						offset=0.1;
						break;
					case 5:
						offset=0.2;
						break;
					}
	}
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

