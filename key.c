// Key.c
// This software configures the off-board piano keys
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// **************Key_Init*********************
// Initialize piano key inputs on PA5-2 or PE3-0
// Input: none 
// Output: none
void Key_Init(void){ volatile uint32_t delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTE_DIR_R &=0xF0;
	GPIO_PORTE_DEN_R |=0x0F;
	GPIO_PORTE_AFSEL_R &= ~(0x0F);

}
// **************Key_In*********************
// Input from piano key inputs on PA5-2 or PE3-0
// Input: none 
// Output: 0 to 15 depending on keys
//   0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2, 0x08 is just Key3
uint32_t Key_In(void){ 
  uint32_t input; 
	input = GPIO_PORTE_DATA_R & 0x0F;
	return input;
}

//------------LaunchPad_Init------------
// Initialize Switch input and LED output
// Input: none
// Output: none
void LaunchPad_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x00000020;
	while((SYSCTL_PRGPIO_R & 0x20) == 0) {};
		GPIO_PORTF_LOCK_R = 0x4C4F434B;
		GPIO_PORTF_CR_R = 0x1F;
		GPIO_PORTF_DIR_R = 0x0E;
		GPIO_PORTF_PUR_R = 0x11;
		GPIO_PORTF_DEN_R = 0x1F;
		GPIO_PORTF_DATA_R = 0;
}
