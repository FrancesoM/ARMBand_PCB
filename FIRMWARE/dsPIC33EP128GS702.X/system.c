/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC33E__)
    	#include <p33Exxxx.h>
    #elif defined(__dsPIC33F__)
    	#include <p33Fxxxx.h>
    #endif
#endif


#include <stdint.h>          /* For uint16_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */

#include "system.h"          /* variables/params used by system.c             */

/******************************************************************************/
/* System Level Functions                                                     */
/*                                                                            */
/* Custom oscillator configuration funtions, reset source evaluation          */
/* functions, and other non-peripheral microcontroller initialization         */
/* functions get placed in system.c.                                          */
/*                                                                            */
/******************************************************************************/

/* Refer to the device Family Reference Manual Oscillator section for
information about available oscillator configurations.  Typically
this would involve configuring the oscillator tuning register or clock
switching useing the compiler's __builtin_write_OSCCON functions.
Refer to the C Compiler for PIC24 MCUs and dsPIC DSCs User Guide in the
compiler installation directory /doc folder for documentation on the
__builtin functions.*/

/* TODO Add clock switching code if appropriate.  An example stub is below.   */
void ConfigureOscillator(void)
{

    /* Check if clock is stable after automatic clock switch after reset */
    while(OSCCONbits.COSC != OSCCONbits.NOSC);

    /* Define Prescaler/Postscaler and DividerFeedback for PLL*/
    PLLFBD = 62; //M=64
    CLKDIVbits.PLLPOST = 2; //N2 = 4
    CLKDIVbits.PLLPRE = 0; //N1 = 2
    
    /* When clock switch occurs switch to Primary Osc (HS, XT, EC) */
    __builtin_write_OSCCONH(0x03);  /* Set OSCCONH for clock switch to XT+PLL */
    __builtin_write_OSCCONL(OSCCONL | 0x01);  /* Start clock switching */
    
    /* Wait for Clock switch to occur */
    while(OSCCONbits.COSC != OSCCONbits.NOSC);

    /* Wait for PLL to lock, only if PLL is needed */
    while(OSCCONbits.LOCK != 1);

}

