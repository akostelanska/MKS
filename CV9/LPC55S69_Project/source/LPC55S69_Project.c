/*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    LPC55S69_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif

	//PRINTF("Hello World\n");

	uint32_t DWT1;
	uint32_t DWT2;

	char password[20] = "12345";
	char input[20];
	char input_safe[20];

	uint32_t status;

	uint32_t strcmp_safe(const char *s1, const char *s2) {
		int m = 0;
		volatile size_t i = 0;
		volatile size_t j = 0;
		volatile size_t k = 0;

		if (s1 == NULL || s2 == NULL)
			return 0;

		while (1) {
			m |= s1[i] ^ s2[j];

			if (s1[i] == '\0')
				break;
			i++;

			if (s2[j] != '\0')
				j++;
			if (s2[j] == '\0')
				k++;
		}

		return m == 0;
	}

	/* Force the counter to be placed into memory. */
	volatile static int i = 0;
	/* Enter an infinite loop, just incrementing a counter. */
	while (1) {
		i++;
		/* 'Dummy' NOP to allow source level single stepping of
		 tight while() loop */
		__asm volatile ("nop");
		/*
		PRINTF("Enter password: \n\r");
		SCANF("%s", input);
		PRINTF("%s \n\r", input);
		DWT1 = DWT->CYCCNT;
		status = strcmp(password, input);
		DWT2 = DWT->CYCCNT;
		if (status == 0) {
			PRINTF("Correct password.\n\r");
		} else {
			PRINTF("Incorrect password.\n\r");
		}
		PRINTF("Number of cycles: %d \r\n", DWT2 - DWT1);
*/
		PRINTF("Safe compare.\n\r");
		PRINTF("Enter password: \n\r");
		SCANF("%s", input_safe);
		PRINTF("%s \n\r", input_safe);
		DWT1 = DWT->CYCCNT;
		status = strcmp_safe(password, input_safe);
		DWT2 = DWT->CYCCNT;
		if (status != 0) {
			PRINTF("Correct password.\n\r");
		} else {
			PRINTF("Incorrect password.\n\r");
		}
		PRINTF("Number of cycles: %d \r\n", DWT2 - DWT1);
	}
	return 0;
}
