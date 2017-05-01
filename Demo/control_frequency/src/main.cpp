#include "helper_functions.h"
#include "7seg.h"
#include "keypad.h"
#include "stm32l476xx.h"
#include "led_button.h"
#include "timer.h"

//define the pin we need;
//#define SEG_gpio GPIOC
//#define DIN_pin 3
//#define CS_pin 4
//#define CLK_pin 5
////define the pins for pads;
//#define COL_gpio GPIOA
//#define COL_pin 6   //6 7 8 9
//#define ROW_gpio GPIOB
//#define ROW_pin 3   //3 4 5 6

#define LED_gpio GPIOA
#define LED_pin 5

#define BUTTON_gpio GPIOC
#define BUTTON_pin 13

//define counter timer;
//#define COUNTER_timer TIM2;

void delay_without_interrupt(int msec){
	int loop_cnt = 100*msec;
	while(loop_cnt){
		loop_cnt--;
	}
}

int read_gpio(GPIO_TypeDef* gpio, int pin)      //For read button
{
	if((gpio->IDR>>pin) & 1)
		return 0;
	else
		return 1;
}
void set_gpio(GPIO_TypeDef * gpio,int pin){
	gpio->BSRR|=(0b1<<(pin));
}
void reset_gpio(GPIO_TypeDef * gpio,int pin){
	gpio->BRR|=(0b1<<(pin));
}

int Get_Digits(int num){
	if(num==0)
		return 0;
    int i=0;
    while(1){
                i++;
        if(!(num/=10)){

         return i;
        }

    }
}
int init_button(GPIO_TypeDef* gpio, int button_pin){

	RCC->AHB2ENR |=RCC_AHB2ENR_GPIOCEN;
	gpio->MODER &= ~(0b11<<(2*button_pin));
	gpio->MODER |= (0b00<<(2*button_pin));

	return 0;
}
int init_led(GPIO_TypeDef* gpio, int Led_pin){

	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	gpio->MODER &= ~(0b11 << (2*Led_pin));
	gpio->MODER |= (0b01 << (2*Led_pin));
	return 0;
}

void FPU_init(){
	SCB->CPACR |=(0XF<<20);
	__DSB();
	__ISB();
}
void SystemClock_Config(int speed){
	RCC->CFGR&=~RCC_CFGR_SW_Msk;
	RCC->CFGR|=RCC_CFGR_SW_MSI;
	while(!(((RCC->CFGR&RCC_CFGR_SWS_Msk)>>RCC_CFGR_SWS_Pos)==0));
	RCC->CR&=~RCC_CR_PLLON;
	while((RCC->CR&RCC_CR_PLLRDY)!=0);
	RCC->PLLCFGR&=~RCC_PLLCFGR_PLLSRC_Msk;
	RCC->PLLCFGR|=RCC_PLLCFGR_PLLSRC_MSI;

	int set_R,set_M,set_N;
	if(speed==40){
		set_R=1;
		set_N=40;
		set_M=0;
	}
	else if(speed==16){
		set_R=0;
		set_N=8;
		set_M=0;
	}
	else if(speed==10){
		set_R=3;
		set_N=20;
		set_M=0;
	}
	else if(speed==6){
		set_R=3;
		set_N=12;
		set_M=0;
	}
	else if(speed==1){
		set_R=3;
		set_N=8;
		set_M=3;
	}
	else{
		set_R=3;
		set_N=86;
		set_M=3;
	}
	RCC->PLLCFGR &=~RCC_PLLCFGR_PLLR_Msk;
	RCC->PLLCFGR |=(set_R<<RCC_PLLCFGR_PLLR_Pos);

	RCC->PLLCFGR &=~RCC_PLLCFGR_PLLN_Msk;
	RCC->PLLCFGR |=(set_N<<RCC_PLLCFGR_PLLN_Pos);

	RCC->PLLCFGR &=~RCC_PLLCFGR_PLLM_Msk;
	RCC->PLLCFGR |=(set_M<<RCC_PLLCFGR_PLLM_Pos);

	RCC->PLLCFGR |=RCC_PLLCFGR_PLLREN;

	RCC->CR |=RCC_CR_PLLON;

	RCC->CFGR &=~RCC_CFGR_SW_Msk;
	RCC->CFGR |=RCC_CFGR_SW_PLL;
	while(!(((RCC->CFGR&RCC_CFGR_SWS_Msk)>>RCC_CFGR_SWS_Pos)==3));
}

int main(){
	FPU_init();

	if(init_led(LED_gpio,LED_pin)!=0){
		return -1;
	}
	if(init_button(BUTTON_gpio,BUTTON_pin)!=0){
		return -1;
	}
	int state=0;
	int speed=0,trans[5]={1,6,10,16,40};
	SystemClock_Config(trans[speed]);
	int button_press_cycle_per_second=10;
	int debounce_cycles=100;
	int debounce_threshold=debounce_cycles*0.7;
	int last_button_state=0;
	while(1){
			for(int a=0;a<button_press_cycle_per_second;a++){
				int pos_cnt=0;
				for(int a=0;a<debounce_cycles;a++){
					if(read_gpio(BUTTON_gpio,BUTTON_pin)==0){
						pos_cnt++;
					}
					delay_without_interrupt(1);
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
						speed=(speed+1)%5;
						SystemClock_Config(trans[speed]);
						}

						last_button_state=0;
					}

				}
			//make sure the frequency we control can at least have one cycle to operator.
			//When state ==1 which means ,this cycle would be lit when state is set to zero
			if(state){
				set_gpio(LED_gpio,LED_pin);
				state=0;
			}
			else{
				reset_gpio(LED_gpio,LED_pin);
				state=1;
			}
		}

}







