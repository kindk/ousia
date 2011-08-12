/* *****************************************************************************
 * @file    sample/main.c
 *
 * @brief   sample code
 * @date    2011-08-10
 *
 * @history 2011-08-10 Initial revision
 *
 * *****************************************************************************
 * COPYRIGHT (C) LEAFGRASS - Librae (librae8226@gmail.com)
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 * ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <ousia/scheduler.h>
#include <stm32/libmaple/libmaple.h>
#include <stm32/libmaple/libmaple_types.h>
#include <stm32/libmaple/gpio.h>
#include <stm32/libmaple/usart.h>
#include <stm32/stm32utils/stm32utils.h>

#include <ulib/tprintf/tprintf.h>

#define VERSION     "v0.0.2"
#define VER_NAME    "Glossy Abelia"

void delayMicroseconds(uint32 us)
{
    delay_us(us);
}

void delay(uint32 ms)
{
    uint32 i;
    for (i = 0; i < ms; i++)
        delayMicroseconds(1000);
}

int main(void)
{
    int result = 0;
    int i = 0;
    char ch = 0;

    sample_function(10, 20, &result);

    init_printf(NULL, stm32utils_io_putc);
    stm32utils_system_init(); 

    /* led flashes -> sign of system reset ok */
    for(i = 0; i < 6; i++) {
        gpio_toggle_bit(GPIOA, 0);
        delay(50);
    }   

    /* Boot Animation */
    usart_putc(USART1, 0x0C);   /* clear screen */

    printf("Booting...\r\n\r\n");                         
    printf("                       _\r\n");
    printf("     _                / /\r\n");
    printf("    | |    ___  __ _ _| |_ __ _ _  __  __ _   _   _\r\n");
    printf("    | |   / _ \\/ _` |_   _/ _` | \\/ _)/ _` | / / / /\r\n");
    printf("    | |_ _  __( (_| | | |  (_| | | | ( (_| | \\ \\ \\ \\\r\n");
    printf("    |_ _ _\\___|\\__,_| | | \\__, / | |  \\__,_| /_/ /_/\r\n");
    printf("                      /_/ \\_ _/\r\n" );
    printf("\r\n");
    printf("Ousia "); printf(VERSION); printf(" "); printf(VER_NAME);
    printf("\r\n\tby Librae - g.leafgrass@gmail.com");
    printf("\r\n\r\n");
    printf("Hello, Ousia ~\r\n");

    for (;;) {
        if (USART1->flag_trigger) {
            for (i = 0; i < USART1->cnt_trigger; i++) {
                ch = usart_getc(USART1);
                if (ch) {
                    switch( ch ) {
                    case '\r':
                        printf( "\r\n" );
                        break;
                    case '\b':
                        printf( "\b \b" );
                        break;
                    default:
                        printf( "%c", ch );
                        break;
                    }
                }
            }
            USART1->cnt_trigger = 0;
        }
        delay(10);
    }

    return 0;
}

