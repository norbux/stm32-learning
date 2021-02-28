/*
 * Example code for setting up IO ports/pins on STM32F103
 * For this example pins 13 and 15 of port C are used
 * */

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	/*
	 *  0x4002 1000 - 0x4002 13FF Reset and clock control RCC
	 *  -----------------------------------------------------
	 *  APB2 peripheral clock enable register (RCC_APB2ENR)
		Address: 0x18
		Reset value: 0x0000 0000
		Access: word, half-word and byte access
		for port C: Bit 4

		0x4001 1000 - 0x4001 13FF GPIO Port C
		------------------------------------------------------
		Port configuration register high (GPIOx_CRH) (x=A..G)
		Address offset: 0x04
		Reset value: 0x4444 4444
		for port C: bits 23:22 and 22:21

		Port output data register (GPIOx_ODR) (x=A..G)
		Address offset: 0x0C
		Reset value: 0x0000 0000
	*/

	uint32_t *pClock = (uint32_t*)0x40021018;
	uint32_t *pPortC = (uint32_t*)0x40011004;
	uint32_t *pPins = (uint32_t*)0x4001100C;

	// Enable clock for port C
	*pClock |= 0x10;

	// Configure port C
	*pPortC |= 1<<20;
	*pPortC |= 1<<28;
	*pPortC &= ~(1<<30);

	while(1)
	{
		//*pPins = 0x0;
		*pPins &= ~(1<<13);
		*pPins &= ~(1<<15);
		int i = 0;
		for (i = 0; i < 100000; i++);
		*pPins |= 1<<13;
		*pPins |= 1<<15;
		for (i = 0; i < 100000; i++);
	};
}
