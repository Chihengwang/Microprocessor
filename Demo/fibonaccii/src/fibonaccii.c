#include "stm32l476xx.h"
#include "helper_functions.h"
#include "7seg.h"

#define SEG_gpio GPIOB      //Setting
#define DIN_pin 3
#define CS_pin 4
#define CLK_pin 5

#define BUTTON_gpio GPIOC
#define BUTTON_pin 13
int Get_digits(long long num){
    int i=0;
    while(1){
                i++;
        if(!(num/=10)){

         return i;
        }

    }
}
int read_gpio(GPIO_TypeDef* gpio, int pin)      //For read button
{
	if((gpio->IDR)>>pin & 1)
		return 0;
	else
		return 1;
}
int init_but(GPIO_TypeDef* gpio, int LED_pin)   //Button init.
{
	if(gpio==GPIOC)
	{
		RCC->AHB2ENR |=RCC_AHB2ENR_GPIOCEN;
	}
	else
	{
		return -1;
	}
	gpio->MODER &= ~(0b11<<(2*LED_pin));
	gpio->MODER |= (0b00<<(2*LED_pin));

	return 0;
}
void delay_without_interrupt(int msec){
	int loop_cnt = 500*msec;
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
	long long prev=0,now=1,res=0;
	int start=0;
	int button_press_cycle_per_second =10 ;
	int debounce_cycles =100;
	int debounce_threshold=debounce_cycles*0.7;
	int last_button_state=0;
	if(init_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin)!=0){
		return -1;
	}
	send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,SEG_ADDRESS_DECODE_MODE,0xFF);    //set decode or non decode mode
	send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,SEG_ADDRESS_SCAN_LIMIT,0b111);    //Set the digits
	send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,SEG_ADDRESS_SHUTDOWN,0x01);	 	//set open
	send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,SEG_ADDRESS_ITENSITY,0b1111);
	if(init_but(BUTTON_gpio,BUTTON_pin)!=0){
		//fail to init
		return -1;
	}
	int i=0;
		send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,i+1,0);
	for(i=1;i<8;i++){
		send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,i+1,15);
	}
//int current =0;
//while(1){
//	send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,SEG_ADDRESS_DIGIT_0,SEG_DATA_NON_DECODE_LOOP[current]);
//	current=(current+1)%16;
//	delay_without_interrupt(3000);
//}
	while(1){
			for(int a=0;a<button_press_cycle_per_second;a++){                                        //test 10 cylces (max 5 operation)
				int pos_cnt=0;
				for(int a=0;a<debounce_cycles;a++){                                                  //do it 100 times per cycles (used to determine whether your pressing is valid or not)
					if(read_gpio(BUTTON_gpio,BUTTON_pin)==0){
						pos_cnt++;
					}
					//delay_without_interrupt(0.1);   //delay part
				}
				if(pos_cnt>debounce_threshold){                                 //algorithm: detect press and release
					if(last_button_state==0){
				}
					else{

					}
					last_button_state=1;
			    }
				else{
					if(last_button_state==0){

					}
					else{
						res=now+prev;
						if(now>=prev&&start) prev=res;
						else now=res;
						start=1;
					}
					last_button_state=0;
				}
			}
			if(res<=99999999){
			int i=0,use=res;
			int dig=Get_digits(res);
			for(i=0;i<dig;i++,use/=10){
				send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,i+1,use%10);
			}
			}
			else{
				int i=0;
				send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,i+1,1);
				i++;
				send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,i+1,10);
				i++;
			for(i=2;i<8;i++){
				send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,i+1,15);
			}
			}
}
	return 0;
}
