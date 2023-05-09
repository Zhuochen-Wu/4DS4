/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#define MEM_LOC(x) *((int*)x)
#define ABR_Loc1 MEM_LOC(0x20001000)
#define ABR_Loc2 MEM_LOC(0x20001001)
#define ABR_Loc3 MEM_LOC(0x20001005)
#define ABR_Loc4 MEM_LOC(0x20001007)

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    char ch;

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    PRINTF("hello world.\r\n");
    testFunction();
    while (1)
    {
        ch = GETCHAR();
        PUTCHAR(ch);
    }



}
void testFunction(){
	int *ptr_location = (int*) 0x20001000;
	*ptr_location = 11;

	ABR_Loc1 = 0xAC;
	ABR_Loc2 = 0xAABBCCDD;
	ABR_Loc3 = 0xABCD;
	ABR_Loc4 = 0xAABBCCDD;



	int loc1 = ABR_Loc1;
	int loc2 = ABR_Loc2;
	int loc3 = ABR_Loc3;
	int loc4 = ABR_Loc4;




}
