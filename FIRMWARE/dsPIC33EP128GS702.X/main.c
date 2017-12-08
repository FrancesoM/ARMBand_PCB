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


#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */
#include <math.h>

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
unsigned int photoreflectors[8];// = {0xff00,0xdd22,0xbb44,0x9966,0x7788,0x55aa,0x33cc,0x11ee};
int counter = 0;
int lsb = 0;
int sample=0;
float deltaT = 0.1f;
float pi = 3.1415f;
float omega = 2500.0f; // 10rad/sec
float t=0;

int16_t main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
      
    
    while(1)
    {
        //PORTAbits.RA3 = LATAbits.LATA3 ^ 1;
        if(sample)
        {
            SwipeSampling(photoreflectors);
            //t += deltaT;
            sample = 0;
        }
        //__delay_ms(100);
    }
}
