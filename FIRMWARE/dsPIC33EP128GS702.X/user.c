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
#include "user.h"            /* variables/params used by user.c               */
#include "dsp.h"
#include "system.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    TRISAbits.TRISA3 = 0; //Pin as output
    PORTAbits.RA3 = 0; //Pin low
    
    /* Setup analog functionality and port direction */

    /* Initialize peripherals */
}

/* For this application we will power up all the ADC modules.
 * both the 4 dedicated ADC cores and the Shared ones. 
 * The mapping is: 
 * AN0,1,2,3 -> Dedicated for each one
 * AN4,19,20,21 -> Shared 
 */

/* The Initialization consists in giving power to the analog and
 * digital circuits, as well as deciding the clock, setting the 
 * pins as analog and inputs.
 */
