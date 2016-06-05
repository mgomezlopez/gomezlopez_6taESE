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
char cadena1[]="Ganancia:";
char cadena2[]="Offset:";
char cadena3[]="Maximo:";
char cadena4[]="Minimo:";
int cc=1;
int c=1,i=0;
int d;
int nn=0;
int n=0;
float e=0;
float max_mil,max_cen,max_dec,max_un,resto_max_mil,resto_max_cen,resto_max_dec;
float min_mil,min_cen,min_dec,min_un,resto_min_mil,resto_min_cen,resto_min_dec;
float gan_mil,gan_cen,gan_dec,gan_un,resto_gan_mil,resto_gan_cen,resto_gan_dec;
float ganancia=0.8;
float offset=-0.2;
float amplitud=0;
float max=3.3;
float min=0;
uint16_t adc=0;
uint32_t dac_int;
int tecla;

void ISR_RIT (void)
	{
	if (n<6){n=n+1;e=620;}
	else if (n<11) {n=n+1;e=310;}
	else {n=0;}
	dac_int=(uint32_t) e;
	EscribeDAC(dac_int);
	adc=LeeADC();
	amplitud=(float) adc;
	amplitud=(3.3/1023)*amplitud*ganancia+offset; amplitud=amplitud*100;
	if (amplitud<max){max=max;} else {max=amplitud;}
	max_mil=max/1000; resto_max_mil=(int)max%1000; max_cen=resto_max_mil/100; resto_max_cen=(int)resto_max_mil%100;
	max_dec=resto_max_cen/10; resto_max_dec=(int)resto_max_cen%10; max_un=resto_max_dec;

	if (amplitud>min){min=min;} else {min=amplitud;}
	min_mil=min/1000; resto_min_mil=(int)min%1000; min_cen=resto_min_mil/100; resto_min_cen=(int)resto_min_mil%100;
	min_dec=resto_min_cen/10; resto_min_dec=(int) resto_min_cen% 10; min_un=resto_min_dec;

	gan_mil=ganancia/1000; resto_gan_mil=(int)ganancia%1000; gan_cen=resto_gan_mil/100; resto_gan_cen=(int)resto_gan_mil%100;
	gan_dec=resto_gan_cen/10; resto_gan_dec=(int) resto_gan_cen% 10; gan_un=resto_gan_dec;

	if (nn<50) {nn=nn+1;}
	if (nn==46){for (i=0;i<=6;i++){EscribeUART(cadena3[i]);}
		EscribeUART(max_mil+'0');EscribeUART('.');EscribeUART(max_cen+'0');EscribeUART(max_dec+'0');
		EscribeUART(max_un+'0');EscribeUART('\n');EscribeUART('\r');}
	if (nn==47){for (i=0;i<=6;i++){EscribeUART(cadena4[i]);}
		EscribeUART(min_mil+'0');EscribeUART('.');EscribeUART(min_cen+'0');EscribeUART(min_dec+'0');
		EscribeUART(min_un+'0');EscribeUART('\n');EscribeUART('\r');}
	if (nn==48){for (i=0;i<=9;i++){EscribeUART(cadena1[i]);}
		switch(c){
				case 1:
					EscribeUART('0');EscribeUART('.');EscribeUART('8'); break;
				case 2:
					EscribeUART('0');EscribeUART('.');EscribeUART('9'); break;
				case 3:
					EscribeUART('1');EscribeUART('.');EscribeUART('0'); break;
				case 4:
					EscribeUART('1');EscribeUART('.');EscribeUART('1'); break;
				case 5:
					EscribeUART('1');EscribeUART('.');EscribeUART('2');	break;
				}
				if (c>5) {EscribeUART('1');EscribeUART('.');EscribeUART('2');}EscribeUART('\n');EscribeUART('\r');}

	if (nn==49){for (i=0;i<=6;i++){EscribeUART(cadena2[i]);}
		switch(cc){
			case 1:
				EscribeUART('-');EscribeUART('0');EscribeUART('.');EscribeUART('2'); break;
			case 2:
				EscribeUART('-');EscribeUART('0');EscribeUART('.');EscribeUART('1'); break;
			case 3:
				EscribeUART('0');EscribeUART('.');EscribeUART('0'); break;
			case 4:
				EscribeUART('+');EscribeUART('0');EscribeUART('.');EscribeUART('1'); break;
			case 5:
				EscribeUART('+');EscribeUART('0');EscribeUART('.');EscribeUART('2'); break;
			}
		if (cc>5) {EscribeUART('1');EscribeUART('.');EscribeUART('2');}	EscribeUART('\n');EscribeUART('\r');}
	if (nn==50){nn=0;ConmutaLed(GREEN);}
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
	{	max=0;min=0;
	while (LeeTecla()==0);
		tecla = LeeTecla();
		for ( d = 1 ; d <= 3276700; d++ ); /*delay ()*/
		switch(tecla)	{
			case TECLA1:
				if (c<6){c=c+1;} else {c=c;}	break;
			case TECLA2:
				if (c>1) {c=c-1;} else {c=c;} break;
			case TECLA3:
				if (cc<6) {cc=cc+1;} else {cc=cc;} break;
			case TECLA4:
				if (cc>1) {cc=cc-1;} else {cc=cc;} break;
			}
		switch(c)	{
					case 1:
						ganancia=0.8; break;
					case 2:
						ganancia=0.9; break;
					case 3:
						ganancia=1; break;
					case 4:
						ganancia=1.1; break;
					case 5:
						ganancia=1.2; break;
					}
		switch(cc)	{
					case 1:
						offset=-0.2; break;
					case 2:
						offset=-0.1; break;
					case 3:
						offset=0; break;
					case 4:
						offset=0.1;	break;
					case 5:
						offset=0.2; break;
					}
		}
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

