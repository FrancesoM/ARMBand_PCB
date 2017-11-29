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
    
    /* Setup analog functionality and port direction */
    TRISAbits.TRISA3 = 0; //Pin as output
    PORTAbits.RA3 = 0; //Pin low
    
    /* Initialize peripherals */
    InitADC();
    I2C2CONLbits.I2CEN = 1;  //Enable i2c
    INTCON2bits.GIE = 1;     //Enable global interrupt
    IEC3bits.SI2C2IE = 1;    //Enable slave interrupts
}

/* For this application we will power up all the ADC modules.
 * both the 4 dedicated ADC cores and the Shared ones. 
 * The mapping is: 
 * AN0,1,2,3 -> Dedicated for each one
 * AN4,19,20,21 -> Shared 
 */
void InitADC(void)
{
    /*Set channels as input by selecting both the TRISA and ANSEL*/
    
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB5 = 1;
    TRISBbits.TRISB6 = 1;
    TRISBbits.TRISB7 = 1;
    TRISBbits.TRISB9 = 1;
    
    ANSELAbits.ANSA0 = 1;
    ANSELAbits.ANSA1 = 1;
    ANSELAbits.ANSA2 = 1;
    ANSELBbits.ANSB0 = 1;
    ANSELBbits.ANSB5 = 1;
    ANSELBbits.ANSB6 = 1;
    ANSELBbits.ANSB7 = 1;
    ANSELBbits.ANSB9 = 1;
    
    /* Select clock sources for ADC -> Tsrc 
     * default Instruction Clock*/
    
    //ADCON3Hbits.CLKSEL = 0b00; 32MHz
    
    /*Select divider -> TCoreSrc
     * default no division*/
    
    //ADCON3Hbits.CLKDIV = 0b000000; 32MHz
    
    /* Select divider per each core + shared -> TADCore
     * defaul division by 2*/
    
    //It should be ADCORExHbits.ADCS = "divider code", but we use the default div by 2
    //And for the shared  ADCON2Lbits.SHRADCS = "divider code". 16MHz
    
    /* Configure the ADC reference sources */
    
    ADCON3Lbits.REFSEL = 0b000;
    
    /* Select the resolution for dedicated and shared - 12 bits by default */
    //ADCORExHbits.RES = "value";
    //ADCON1Hbits.SHRRES = "value";
    
    /* Cofigure the data output format  */
    ADCON1Hbits.FORM = 0; //Integer
    
    /* Select the single or differential input config, and output format for 
     * each input. By default they are single input, unsigned output. */
    
    /*Select the default sampling time that occurs 
     * between trigger and start of conversion*/
    ADCON4L |= 0xf; //Enable delayed conversion on all dedicated ADC
    
    /*Default for each core is 2*Tadcore, since TadCore is 1/16 uS and we need 
     * 11nS minimum delay, this is by far shorter than what we can achieve with 
     * the fastest clock, so we keep it as default: delay=2*tadcore, for both the
     * dedicated and shared */
    
    //ADCORExLbits.SAMC = "multiplier"; //Dedicated
    //ADCON2Hbits.SHRSAMC = "multiplier"; //Shared
    
    /* Power up and set warmup time at least 10uS. Since the warmuptime is 
     * counted with tcoresrc, which is 32MHz we need to count: 322 clock 
     * periods. We can choose only a discrete set of values, so 512 is ok */
    
    ADCON1Lbits.ADON = 1;
    ADCON5Hbits.WARMTIME = 0b1001; //512
    
    /* Turn on the power module */
    
    ADCON5Lbits.C0PWR = 1;
    ADCON5Lbits.C1PWR = 1;
    ADCON5Lbits.C2PWR = 1;
    ADCON5Lbits.C3PWR = 1;
    ADCON5Lbits.SHRPWR = 1;
    
    unsigned int ready_mask = 0x8f00;
    while((ADCON5L&ready_mask) != ready_mask ); //Wait power bits to set
    
    ADCON3Hbits.C0EN = 1;
    ADCON3Hbits.C1EN = 1;
    ADCON3Hbits.C2EN = 1;
    ADCON3Hbits.C3EN = 1;
    ADCON3Hbits.SHREN = 1;
    
    /* Set the trigger source. We don't use the automatic hardware trigger  
     * because we use the individual channel trigger
     */
    
    /*Select the channels to be connected to the dedicated ADC*/
    
    ADCON4Hbits.C0CHS = 0;  //AN0
    ADCON4Hbits.C1CHS = 0;  //AN1
    ADCON4Hbits.C2CHS = 0;  //AN2
    ADCON4Hbits.C3CHS = 0;  //AN3
    
    
}

void SwipeSampling(unsigned int* buffer)
{
    /*Set the common trigger for the 2 channels AN0 and AN4 */
    ADTRIG0Hbits.TRGSRC3 = 0b00000;
    ADTRIG5Lbits.TRGSRC21 = 0b00000;
    ADTRIG0Lbits.TRGSRC0 = 0b00001;
    ADTRIG1Lbits.TRGSRC4 = 0b00001;
    /* Start trigger */
    ADCON3Lbits.SWCTRG = 1;
    /* Wait them to be ready*/
    while(ADSTATLbits.AN0RDY != 1 && ADSTATLbits.AN4RDY != 1);
    
    /* Read the values and store them in the buffer*/
    buffer[0] = ADCBUF0;
    buffer[4] = ADCBUF4;
    
    /* Repeat for AN1 and AN19*/
    ADTRIG0Lbits.TRGSRC0 = 0b00000; //No more common trigger
    ADTRIG1Lbits.TRGSRC4 = 0b00000;
    ADTRIG0Lbits.TRGSRC1 = 0b00001;
    ADTRIG4Hbits.TRGSRC19 = 0b00001;
    /* Start trigger */
    ADCON3Lbits.SWCTRG = 1;
    /* Wait them to be ready*/
    while(ADSTATLbits.AN1RDY != 1 && ADSTATHbits.AN19RDY != 1);
    /* Read the values and store them in the buffer*/
    buffer[1] = ADCBUF1;
    buffer[5] = ADCBUF19;
    
    /* Repeat for AN2 and AN20*/
    ADTRIG0Lbits.TRGSRC1 = 0b00000;
    ADTRIG4Hbits.TRGSRC19 = 0b00000;
    ADTRIG0Hbits.TRGSRC2 = 0b00001;
    ADTRIG5Lbits.TRGSRC20 = 0b00001;
    
    /* Start trigger */
    ADCON3Lbits.SWCTRG = 1;
    /* Wait them to be ready*/
    while(ADSTATLbits.AN2RDY != 1 && ADSTATHbits.AN20RDY != 1);
    /* Read the values and store them in the buffer*/
    buffer[2] = ADCBUF2;
    buffer[6] = ADCBUF20;
    
    /* Repeat for AN3 and AN21*/
    ADTRIG0Hbits.TRGSRC2 = 0b00000;
    ADTRIG5Lbits.TRGSRC20 = 0b00000;
    ADTRIG0Hbits.TRGSRC3 = 0b00001;
    ADTRIG5Lbits.TRGSRC21 = 0b00001;
    
    /* Start trigger */
    ADCON3Lbits.SWCTRG = 1;
    /* Wait them to be ready*/
    while(ADSTATLbits.AN3RDY != 1 && ADSTATHbits.AN21RDY != 1);
    /* Read the values and store them in the buffer*/
    buffer[3] = ADCBUF3;
    buffer[7] = ADCBUF21;
     
}
