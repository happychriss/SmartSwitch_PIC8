/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC10LF320
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB             :  MPLAB X 4.15

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include <xc.h>
#include "pin_manager.h"
#include "stdbool.h"
#include "../global.h"



void (*IOCAF1_InterruptHandler)(void);
void (*IOCAF2_InterruptHandler)(void);


void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATA = 0x0b1;

    /**
    TRISx registers
    */
    TRISA = 0x06;

    /**
    ANSELx registers
    */
    ANSELA = 0x00;

    /**
    WPUx registers
    */
    WPUA = 0x06;
    OPTION_REGbits.nWPUEN = 0;

    /**
    ODx registers
    */


    /**
    IOCx registers 
    */
    //interrupt on change for group IOCAF - flag
//    IOCAFbits.IOCAF1 = 0;
    //interrupt on change for group IOCAF - flag
//    IOCAFbits.IOCAF2 = 0;

    
    //interrupt on change for group IOCAN - negative
//    IOCANbits.IOCAN1 = 1;
    //interrupt on change for group IOCAN - negative
//    IOCANbits.IOCAN2 = 1;
    IOCAN=0x06;

    //interrupt on change for group IOCAP - positive
//    IOCAPbits.IOCAP1 = 1;
    //interrupt on change for group IOCAP - positive
//    IOCAPbits.IOCAP2 = 1;
     IOCAP=0x06;

    int dummy;
    dummy = IOCAF;
    IOCAF=0x00;
    
   

    // register default IOC callback functions at runtime; use these methods to register a custom function
    IOCAF1_SetInterruptHandler(IOCAF1_DefaultInterruptHandler);
    IOCAF2_SetInterruptHandler(IOCAF2_DefaultInterruptHandler);
   
    // Enable IOCI interrupt 
    INTCONbits.IOCIE = 1; 
    
}
  
void PIN_MANAGER_IOC(void)
{   
    
    unsigned short dummy;
    dummy=PORTAbits.RA1;
    dummy=PORTAbits.RA2;
    
	// interrupt on change for pin IOCAF1
    if(IOCAFbits.IOCAF1 == 1)
    {
        IOCAF1_ISR();  
    }	
	// interrupt on change for pin IOCAF2
    if(IOCAFbits.IOCAF2 == 1)
    {
        IOCAF2_ISR();  
    }	
}

/**
   IOCAF1 Interrupt Service Routine
*/
void IOCAF1_ISR(void) {

    // Add custom IOCAF1 code
     switch_status = SWITCH_CHANGED;

    // Call the interrupt handler for the callback registered at runtime
    if(IOCAF1_InterruptHandler)
    {
        IOCAF1_InterruptHandler();
    }
    IOCAFbits.IOCAF1 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF1 at application runtime
*/
void IOCAF1_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCAF1_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF1
*/
void IOCAF1_DefaultInterruptHandler(void){
    // add your IOCAF1 interrupt custom code
    // or set custom function using IOCAF1_SetInterruptHandler()
}

/**
   IOCAF2 Interrupt Service Routine
*/
void IOCAF2_ISR(void) {

    // Add custom IOCAF2 code
     switch_status = SWITCH_CHANGED;
    
    // Call the interrupt handler for the callback registered at runtime
    if(IOCAF2_InterruptHandler)
    {
        IOCAF2_InterruptHandler();
    }
    IOCAFbits.IOCAF2 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF2 at application runtime
*/
void IOCAF2_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCAF2_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF2
*/
void IOCAF2_DefaultInterruptHandler(void){
    // add your IOCAF2 interrupt custom code
    // or set custom function using IOCAF2_SetInterruptHandler()
}

/**
 End of File
*/