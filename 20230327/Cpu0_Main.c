/**********************************************************************************************************************
 * \file Cpu0_Main.c
 * \copyright Copyright (C) Infineon Technologies AG 2019
 * 
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of 
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and 
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all 
 * derivative works of the Software, unless such copies or derivative works are solely in the form of 
 * machine-executable object code generated by a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE 
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 *********************************************************************************************************************/
 /*\title UART communication via ASCLIN module
 * \abstract An ASCLIN module configured for UART communication sends "Hello World!" and receives the string via the internal loopback.
 * \description The string "Hello World!" is sent and received via UART through one pin due to the internal loopback.
 *              The data can be visualized using an oscilloscope.
 *
 * \name ASCLIN_UART_1_KIT_TC275_LK
 * \version V1.0.0
 * \board AURIX TC275 lite Kit, KIT_AURIX_TC275_LITE, TC27xTP_D-Step
 * \keywords ASC, ASCLIN, ASCLIN_UART_1, AURIX, Oscilloscope, UART, communication
 * \documents https://www.infineon.com/aurix-expert-training/Infineon-AURIX_ASCLIN_UART_1_KIT_TC275_LK-TR-v01_00_00-EN.pdf
 * \documents https://www.infineon.com/aurix-expert-training/TC27D_iLLD_UM_1_0_1_12_0.chm
 * \lastUpdated 2021-06-29
 *********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "ASCLIN_UART.h"
#include "GPIO_LED_Button.h"
#include "ADC_Single_Channel.h"


int receive_data=0;
int indata=0;
int adc_valuee = 0;

IfxCpu_syncEvent g_cpuSyncEvent = 0;

int core0_main(void)
{
    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    init_ASCLIN_UART();                 /* Initialize the module                  */
    IfxCpu_enableInterrupts();          /* Enaconble interrupts after initialization */
    //send_receive_ASCLIN_UART_message(); /* Send the string                        */
    initINPUT();
    initOUTPUT();
    //initINPUT();
    vadcBackgroundScanInit();
    vadcBackgroundScanRun();

    while(1)
    {


        RX_BUFF();
        receive_data=receive_ASCLIN_UART_message();
        OUTPUT_control2(receive_data);
        indata=INPUT_control();
        adc_valuee = indicateConversionValue();
        data_in_4(indata, adc_valuee);
        send_ASCLIN_UART_message();
    }
    return (1);
}
