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

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/




struct struct1
{
	char x2;
	int x1;
};
struct struct2
{
	short x2;
	int x1;
};
struct struct3
{
	int x1;
	short x2;
};
struct struct4
{
	struct inner_struct
	{
		char x1;
		short x2;
		int x3;
	} inner_struct_1;
	int x1;
};


/*!
 * @brief Main function
 */
int main(void)
{


    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    PRINTF("hello world.\r\n");



    struct struct1 s1 = {0xFF,0xAAAAAAAA};
    struct struct2 s2 = {0xFFFF,0xAAAAAAAA};
    struct struct3 s3 = {0xAAAAAAAA,0xFFFF};
    struct struct4 s4 = {0xFF, 0xBBBB, 0xCCCCCCCC, 0xAAAAAAAA};

    PRINTF("%d\n", sizeof(s1));
    PRINTF("%d\n", sizeof(s2));
    PRINTF("%d\n", sizeof(s3));
    PRINTF("%d\n", sizeof(s4));

    while (1)
    {
    }
}
