#include "stm32l476xx.h"
#include "helper_functions.h"
#include "led_button.h"
//#include "7seg.h"

//Define pins for 4 leds
#define LED_gpio GPIOA
#define LED1_pin 5
#define LED2_pin 6
#define LED3_pin 7
#define LED4_pin 8

//Define pins for button (default on PC13)

#define BUTTON_gpio GPIOC
#define BUTTON_pin 13
int read_gpio(GPIO_TypeDef* gpio, int pin)
{
	if((gpio->IDR)>>pin & 1)
		return 0;
	else
		return 1;
}
int init_but(GPIO_TypeDef* gpio, int LED_pin)
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
int init_led(GPIO_TypeDef* gpio,int LED_pin){
	//Enable AHB2 Clock
	if(gpio==GPIOA){
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	}
	else if(gpio==GPIOB){
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	}
	else{
		//Error
		return -1;
	}
	gpio->MODER &= ~(0b11 << (2*LED_pin));
	gpio->MODER |= (0b01 << (2*LED_pin));
	return 0;
}
void delay_without_interrupt(int msec){
	int loop_cnt = 100*msec;
	while(loop_cnt){
		loop_cnt--;
	}
}
void set_gpio(GPIO_TypeDef* gpio,int pin){
	gpio->BSRR |= (1<<pin);
}
void reset_gpio(GPIO_TypeDef *gpio,int pin){
	gpio->BRR |= (1<<pin);
}
int main(){
	int shift_direction=0;
	int led_data=0b000010;
	int leds[4]={LED1_pin,LED2_pin,LED3_pin,LED4_pin};
	int state=0;
	int button_press_cycle_per_second =10;
	int debounce_cycles =100;
	int debounce_threshold=debounce_cycles*0.7;
	int last_button_state=0;
	if(init_led(LED_gpio,LED1_pin)!=0){
		//fail to init
		return -1;
	}
	if(init_led(LED_gpio,LED2_pin)!=0){
		//fail to init
		return -1;
	}
	if(init_led(LED_gpio,LED3_pin)!=0){
		//fail to init
		return -1;
	}
	if(init_led(LED_gpio,LED4_pin)!=0){
		//fail to init
		return -1;
	}
	if(init_but(BUTTON_gpio,BUTTON_pin)!=0){
		//fail to init
		return -1;
	}
	while(1){
		for(int a=0;a<button_press_cycle_per_second;a++){
			int pos_cnt=0;
			for(int a=0;a<debounce_cycles;a++){
				if(read_gpio(BUTTON_gpio,BUTTON_pin)==0){
					pos_cnt++;
				}
				delay_without_interrupt(1000/(button_press_cycle_per_second*debounce_cycles));
			}
			if(pos_cnt>debounce_threshold){
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
					state++;
					switch(state){
					case 0:
						led_data=0b00010;
						shift_direction=0;
						break;
					case 1:
						led_data=0b0000110;
						shift_direction=0;
						break;
					case 2:
						led_data=0b01110;
						shift_direction=0;
						break;
					default:
						state=0;
						led_data=0b000010;
						shift_direction=0;
					}

//					if(state==3){
//						state=0;
//					}
				}
				last_button_state=0;
			}
		}
		if(state==1){
			for(int a=0;a<4;a++){
				if((led_data>>(a+1))&0x1){
					reset_gpio(LED_gpio,leds[a]);
				}
				else{
					set_gpio(LED_gpio,leds[a]);
				}
			}
		//Shift led_data

						if(shift_direction==0){
							led_data=(led_data<<1);
						}
						else{
							led_data=(led_data>>1);
						}
						//Check to see if change shift direction
						if(led_data==0b0000110||led_data==0b11000){
							shift_direction = 1-shift_direction;
						}
						//Delay for 1 sec
						delay_without_interrupt(10);
	}
		if(state==0){

					for(int a=0;a<4;a++){
						if((led_data>>(a+1))&0x1){
							reset_gpio(LED_gpio,leds[a]);
						}
						else{
							set_gpio(LED_gpio,leds[a]);
						}
					}
				//Shift led_data

								if(shift_direction==0){
									led_data=(led_data<<1);
								}
								else{
									led_data=(led_data>>1);
								}
								//Check to see if change shift direction
								if(led_data==0b000010||led_data==0b10000){
									shift_direction = 1-shift_direction;
								}
								//Delay for 1 sec
								delay_without_interrupt(10);
			}
		if(state==2){

					for(int a=0;a<4;a++){
						if((led_data>>(a+1))&0x1){
							reset_gpio(LED_gpio,leds[a]);
						}
						else{
							set_gpio(LED_gpio,leds[a]);
						}
					}
				//Shift led_data

								if(shift_direction==0){
									led_data=(led_data<<1);
								}
								else{
									led_data=(led_data>>1);
								}
								//Check to see if change shift direction
								if(led_data==0b01110||led_data==0b11100){
									shift_direction = 1-shift_direction;
								}
								//Delay for 1 sec
								delay_without_interrupt(10);
			}
	}
	return 0;
}

