// Lab6.c
// Runs on TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// EE319K lab6 starter
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 10/15/21  
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Key.h"
#include "Music.h"
#include "Lab6Grader.h"
// put both EIDs in the next two lines
char EID1[] = "ams23286"; //  ;replace abc123 with your EID
char EID2[] = "jad6983"; //  ;replace abc123 with your EID

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void DAC_Init(void);          // your lab 6 solution
void DAC_Out(uint8_t data);   // your lab 6 solution
uint8_t Testdata;

// lab video Lab6_voltmeter
int voltmetermain(void){ //voltmetermain(void){     
  TExaS_Init(SCOPE);    // bus clock at 80 MHz
  DAC_Init(); // your lab 6 solution
  Testdata = 15;
  EnableInterrupts();
  while(1){                
    Testdata = (Testdata+1)&0x3F;
    DAC_Out(Testdata);  // your lab 6 solution
  }
}
// DelayMs
//  - busy wait n milliseconds
// Input: time to wait in msec
// Outputs: none
void static DelayMs(uint32_t n){
  volatile uint32_t time;
  while(n){
    time = 6665;  // 1msec, tuned at 80 MHz
    while(time){
      time--;
    }
    n--;
  }
}
// lab video Lab6_static
const uint32_t Inputs[16]={0, 1, 7, 8, 15, 16, 17, 18, 31, 32, 33, 47, 48, 49, 62, 63};
int staticmain(void){  
  uint32_t last,now,i;  
  TExaS_Init(SCOPE);    // bus clock at 80 MHz
  LaunchPad_Init();
  DAC_Init(); // your lab 6 solution
  i = 0;
  EnableInterrupts();
  last = LaunchPad_Input();
  while(1){                
    now = LaunchPad_Input();
    if((last != now)&&now){
      Testdata = Inputs[i];
      DAC_Out(Testdata); // your lab 6 solution
      i=(i+1)&0x0F;
    }
    last = now;
    DelayMs(25);   // debounces switch
  }
}


     
int main(void){       
  TExaS_Init(SIMULATIONGRADER);    // bus clock at 80 MHz
  Key_Init();
  LaunchPad_Init();
  Sound_Init();
  Music_Init();
  EnableInterrupts();
  while(1){    
 //buttons
	uint32_t IsPressed;
	IsPressed = Key_In();
		
	if(IsPressed == 0){
		Sound_Start(0);}
	else if(IsPressed == 1){ //233.1 Hz
		Sound_Start(5363);}
	else if(IsPressed == 2){ //292.7 Hz
		Sound_Start(4257);}
	else if(IsPressed == 4){ //349.2 Hz
		Sound_Start(3579);}
	else if(IsPressed == 8){ //392.0 Hz
		Sound_Start(3189);}
    
  }             
}