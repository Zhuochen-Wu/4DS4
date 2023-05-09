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
#include "fsl_ftm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void pwm_setup()
{
	ftm_config_t ftmInfo;
	ftm_chnl_pwm_signal_param_t ftmParam[3];

	ftmParam[0].chnlNumber = kFTM_Chnl_1;
	ftmParam[1].chnlNumber = kFTM_Chnl_4;
	ftmParam[2].chnlNumber = kFTM_Chnl_5;

	for (int i=0; i<3; i++){
		ftmParam[i].level = kFTM_HighTrue;
		ftmParam[i].dutyCyclePercent = 0;
		ftmParam[i].firstEdgeDelayPercent = 0U;
		ftmParam[i].enableComplementary = false;
		ftmParam[i].enableDeadtime = false;
	}

	FTM_GetDefaultConfig(&ftmInfo);

	FTM_Init(FTM3, &ftmInfo);
	FTM_SetupPwm(FTM3, ftmParam, 3U, kFTM_EdgeAlignedPwm, 5000U, CLOCK_GetFreq(kCLOCK_BusClk));
	FTM_StartTimer(FTM3, kFTM_SystemClock);
}

/*!
 * @brief Main function
 */
int main(void)
{
    char ch;
    int input = 0x000000;
    uint8_t red, green, blue;

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    pwm_setup();
    PRINTF("hello enter the input in hexadecimal");
    scanf("%x", &input);

    blue = ((float)(input & 0x0000FF)) / 0xFF * 100;
    green = ((float)((input & 0x00FF00) >> 8)) / 0xFF * 100;
    red = ((float)((input & 0xFF0000) >> 16)) / 0xFF * 100;

    PRINTF("blue\t%d%%\r\n", blue);
    PRINTF("green\t%d%%\r\n", green);
    PRINTF("red\t%d%%\r\n", red);

    FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_1, kFTM_EdgeAlignedPwm, red);
    FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_4, kFTM_EdgeAlignedPwm, blue);
    FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_5, kFTM_EdgeAlignedPwm, green);

    FTM_SetSoftwareTrigger(FTM3, true);

    while (1);
}
