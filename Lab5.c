// Lab5.c starter program EE319K Lab 5, Fall 2022
// Runs on TM4C123
// Put your names here
// Last Modified: 8/21/2021

/* Option A1, connect LEDs to PB5-PB0, switches to PA5-3, walk LED PF321
   Option A2, connect LEDs to PB5-PB0, switches to PA4-2, walk LED PF321
   Option A6, connect LEDs to PB5-PB0, switches to PE3-1, walk LED PF321
   Option A5, connect LEDs to PB5-PB0, switches to PE2-0, walk LED PF321
   Option B4, connect LEDs to PE5-PE0, switches to PC7-5, walk LED PF321
   Option B3, connect LEDs to PE5-PE0, switches to PC6-4, walk LED PF321
   Option B1, connect LEDs to PE5-PE0, switches to PA5-3, walk LED PF321
   Option B2, connect LEDs to PE5-PE0, switches to PA4-2, walk LED PF321
  */
// east/west red light connected to bit 5
// east/west yellow light connected to bit 4
// east/west green light connected to bit 3
// north/south red light connected to bit 2
// north/south yellow light connected to bit 1
// north/south green light connected to bit 0
// pedestrian detector connected to most significant bit (1=pedestrian present)
// north/south car detector connected to middle bit (1=car present)
// east/west car detector connected to least significant bit (1=car present)
// "walk" light connected to PF3-1 (built-in white LED)
// "don't walk" light connected to PF3-1 (built-in red LED)


#include <stdint.h>
#include "SysTick.h"
#include "Lab5grader.h"
#include "../inc/tm4c123gh6pm.h"

// put both EIDs in the next two lines
char EID1[] = "abc123"; //  ;replace abc123 with your EID
char EID2[] = "abc123"; //  ;replace abc123 with your EID

void DisableInterrupts(void);
void EnableInterrupts(void);

int main(void){ 
  DisableInterrupts();
  TExaS_Init(SW_PIN_PA543|LED_PIN_PB543210|LED_PIN_PF321); // enable the LED and switch pins in the TExaS simulation
  SysTick_Init();   // Initialize SysTick for software waits
  
  // initialize GPIO pins
  SYSCTL_RCGCGPIO_R |= 0x23; // enable clock to GPIO Ports A, B, and F
  GPIO_PORTA_DIR_R &= ~0x38; // set PA5-3 as inputs
  GPIO_PORTA_DEN_R |= 0x38;  // enable digital function on PA5-3
  GPIO_PORTB_DIR_R |= 0x3F;  // set PB5-0 as outputs
  GPIO_PORTB_DEN_R |= 0x3F;  // enable digital function on PB5-0
  GPIO_PORTF_DIR_R |= 0x0E;  // set PF3-1 as outputs
  GPIO_PORTF_DEN_R |= 0x0E;  // enable digital function on PF3-1
  
  EnableInterrupts(); 
  while(1){
    // 1) output
    GPIO_PORTB_DATA_R |= 0x3F;  // turn on all LEDs initially
    GPIO_PORTF_DATA_R |= 0x02;  // turn on the "don't walk" LED initially
    
    // 2) wait
    SysTick_Wait10ms(100); // wait for 1 second
    
    // 3) input
    if((GPIO_PORTA_DATA_R & 0x08) == 0) { // if switch PA3 is pressed
      GPIO_PORTF_DATA_R &= ~0x02; // turn off the "don't walk" LED
      GPIO_PORTB_DATA_R &= ~0x21; // turn off the PB5 and PB4 LEDs (red lights for east/west)
      GPIO_PORTB_DATA_R |= 0x0C;  // turn on the PB3 and PB2 LEDs (green lights for east/west)
      SysTick_Wait10ms(200);      // wait for 2 seconds
      GPIO_PORTB_DATA_R &= ~0x0C; // turn off the PB3 and PB2 LEDs (green lights for east/west)
      SysTick_Wait10ms(100);      // wait for 1 second
      GPIO_PORTB_DATA_R |= 0x10;  // turn on the PB4 LED (yellow light for east/west)
      SysTick_Wait10ms(200);      // wait for 2 seconds
      GPIO_PORTB_DATA_R &=




