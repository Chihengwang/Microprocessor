#include "stm32l476xx.h"
#include "helper_functions.h"
#include "7seg.h"

#define SEG_gpio GPIOB      //Setting
#define DIN_pin 3
#define CS_pin 4
#define CLK_pin 5

void delay_without_interrupt(int msec){
	int loop_cnt = 100*msec;
	while(loop_cnt){
		loop_cnt--;
	}
}
void set_gpio(GPIO_TypeDef* gpio,int pin){       //set 1
	gpio->BSRR |= (1<<pin);
}
void reset_gpio(GPIO_TypeDef *gpio,int pin){     //set 0
	gpio->BRR |= (1<<pin);
}

int init_7seg(GPIO_TypeDef* gpio, int DIN, int CS, int CLK){
	gpio->MODER &=~(0b11<<(2*DIN));                              //Set 3,4,5 to output mode
	gpio->MODER |=(0b01<<(2*DIN));
	gpio->MODER &=~(0b11<<(2*CS));
	gpio->MODER |=(0b01<<(2*CS));
	gpio->MODER &=~(0b11<<(2*CLK));
	gpio->MODER |=(0b01<<(2*CLK));
	send_7seg(gpio,DIN,CS,CLK,SEG_ADDRESS_DISPLAY_TEST,0x00);   //Set DISPLAY TEST REGISTER TO NORMAL OPERATION
	return 0;
}

void send_7seg(GPIO_TypeDef* gpio, int DIN, int CS, int CLK, int address, int data){
	int payload= ((address&0xFF)<<8)|(data&0xFF);                //Send the whole data (sixteen bits)
	int total_cycles=16+1;
	for(int a=1;a<=total_cycles;a++){
		reset_gpio(gpio,CLK);
		if(((payload>>(total_cycles-1-a))&0x1)&&a!=total_cycles){
			set_gpio(gpio,DIN);
		}
		else{
			reset_gpio(gpio,DIN);
		}
		if(a==total_cycles){
			set_gpio(gpio,CS);
		}
		else{
			reset_gpio(gpio,CS);
		}
		set_gpio(gpio,CLK);
	}
	return;
}
int main(){
	RCC->AHB2ENR|=RCC_AHB2ENR_GPIOBEN;
//	int SEG_DATA_NON_DECODE_LOOP[16]={
//			  SEG_DATA_NON_DECODE_0 ,
//		 	  SEG_DATA_NON_DECODE_1	,
//		      SEG_DATA_NON_DECODE_2	,
//			  SEG_DATA_NON_DECODE_3	,
//			  SEG_DATA_NON_DECODE_4	,
//			  SEG_DATA_NON_DECODE_5	,
//			  SEG_DATA_NON_DECODE_6	,
//			  SEG_DATA_NON_DECODE_7	,
//			  SEG_DATA_NON_DECODE_8	,
//			  SEG_DATA_NON_DECODE_9	,
//			  SEG_DATA_NON_DECODE_A	,
//			  SEG_DATA_NON_DECODE_B	,
//			  SEG_DATA_NON_DECODE_C	,
//			  SEG_DATA_NON_DECODE_D	,
//			  SEG_DATA_NON_DECODE_E	,
//			  SEG_DATA_NON_DECODE_F
//	};
	int id=150211047;
	int i;
	if(init_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin)!=0){
		return -1;
	}
	send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,SEG_ADDRESS_DECODE_MODE,0xFF);    //set decode or non decode mode
	send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,SEG_ADDRESS_SCAN_LIMIT,0b111);    //Set the digits
	send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,SEG_ADDRESS_SHUTDOWN,0x01);	 	//set open
	send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,SEG_ADDRESS_ITENSITY,0b1111);
//int current =0;
//while(1){
//	send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,SEG_ADDRESS_DIGIT_0,SEG_DATA_NON_DECODE_LOOP[current]);
//	current=(current+1)%16;
//	delay_without_interrupt(3000);
//}
	for(i=0;i<7;i++,id/=10){
		send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,i+1,id%10);
	}
		send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,i+1,id);
return 0;
}
