#include "helper_functions.h"
#include "7seg.h"
#include "keypad.h"
#include "stm32l476xx.h"

#define SEG_gpio GPIOB
#define DIN_pin 3
#define CS_pin 4
#define CLK_pin 5

#define COL_gpio GPIOA
#define COL_pin 5   //5 6 7 8
#define ROW_gpio GPIOC
#define ROW_pin 3   //3 4 5 6
double opans;
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
void display_number(GPIO_TypeDef * gpio,int DIN,int CS,int CLK,int num,int num_digs){
	if(num==-1){
		send_7seg(gpio,DIN,CS,CLK,2,SEG_DATA_NON_DECODE_DASH);
		send_7seg(gpio,DIN,CS,CLK,1,SEG_DATA_NON_DECODE_1);
		for(int i=3;i<9;i++)
			send_7seg(gpio,DIN,CS,CLK,i,0);
	}
	else{
		for(int i=1;i<=num_digs;i++){
					switch(num%10){
					case 0:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_0);break;
					case 1:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_1);break;
					case 2:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_2);break;
					case 3:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_3);break;
					case 4:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_4);break;
					case 5:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_5);break;
					case 6:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_6);break;
					case 7:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_7);break;
					case 8:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_8);break;
					case 9:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_9);break;
					}
					num/=10;
				}
		for(int i=num_digs+1;i<=8;i++){
			send_7seg(gpio,DIN,CS,CLK,i,0);
		}
	}
}
void display_digits(GPIO_TypeDef * gpio,int DIN,int CS,int CLK,int num,int num_digs){
	if(num_digs<=2){
		for(int i=1;i<=2;i++){
						switch(num%10){
						case 0:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_0);break;
						case 1:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_1);break;
						case 2:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_2);break;
						case 3:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_3);break;
						case 4:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_4);break;
						case 5:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_5);break;
						case 6:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_6);break;
						case 7:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_7);break;
						case 8:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_8);break;
						case 9:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_9);break;
						}
						num/=10;
					}
					send_7seg(gpio,DIN,CS,CLK,3,SEG_DATA_NON_DECODE_0p);
					for(int i=4;i<=8;i++){
						send_7seg(gpio,DIN,CS,CLK,i,0);
					}
	}
	else{
	for(int i=1;i<=2;i++){
				switch(num%10){
				case 0:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_0);break;
				case 1:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_1);break;
				case 2:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_2);break;
				case 3:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_3);break;
				case 4:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_4);break;
				case 5:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_5);break;
				case 6:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_6);break;
				case 7:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_7);break;
				case 8:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_8);break;
				case 9:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_9);break;
				}
				num/=10;
			}
			switch(num%10){
			case 0:send_7seg(gpio,DIN,CS,CLK,3,SEG_DATA_NON_DECODE_0p);break;
			case 1:send_7seg(gpio,DIN,CS,CLK,3,SEG_DATA_NON_DECODE_1p);break;
			case 2:send_7seg(gpio,DIN,CS,CLK,3,SEG_DATA_NON_DECODE_2p);break;
			case 3:send_7seg(gpio,DIN,CS,CLK,3,SEG_DATA_NON_DECODE_3p);break;
			case 4:send_7seg(gpio,DIN,CS,CLK,3,SEG_DATA_NON_DECODE_4p);break;
			case 5:send_7seg(gpio,DIN,CS,CLK,3,SEG_DATA_NON_DECODE_5p);break;
			case 6:send_7seg(gpio,DIN,CS,CLK,3,SEG_DATA_NON_DECODE_6p);break;
			case 7:send_7seg(gpio,DIN,CS,CLK,3,SEG_DATA_NON_DECODE_7p);break;
			case 8:send_7seg(gpio,DIN,CS,CLK,3,SEG_DATA_NON_DECODE_8p);break;
			case 9:send_7seg(gpio,DIN,CS,CLK,3,SEG_DATA_NON_DECODE_9p);break;
			}
			num/=10;
			for(int i=4;i<=num_digs;i++){
						switch(num%10){
						case 0:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_0);break;
						case 1:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_1);break;
						case 2:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_2);break;
						case 3:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_3);break;
						case 4:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_4);break;
						case 5:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_5);break;
						case 6:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_6);break;
						case 7:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_7);break;
						case 8:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_8);break;
						case 9:send_7seg(gpio,DIN,CS,CLK,i,SEG_DATA_NON_DECODE_9);break;
						}
						num/=10;
					}
			for(int i=num_digs+1;i<=8;i++){
				send_7seg(gpio,DIN,CS,CLK,i,0);
			}
	}
}
int read_gpio(GPIO_TypeDef* gpio, int pin)      //For read button
{
	if((gpio->IDR>>pin) & 1)
		return 1;                //«ö
	else
		return 0;                //¨S«ö
}
void set_gpio(GPIO_TypeDef * gpio,int pin){
	gpio->BSRR|=(0b1<<(pin));
}
void reset_gpio(GPIO_TypeDef * gpio,int pin){
	gpio->BRR|=(0b1<<(pin));
}
void send_7seg(GPIO_TypeDef * gpio,int DIN,int CS,int CLK,int address,int data){
	int payload = ((address&0xFF)<<8)|(data&0xFF);
	int total_cycles=16+1;

	for(int a=1;a<=total_cycles;a++){
		reset_gpio(gpio,CLK);
		if(((payload>>(total_cycles-a-1))&0b1)&&a!=total_cycles)
			set_gpio(gpio,DIN);
		else
			reset_gpio(gpio,DIN);
		if(a==total_cycles)
			set_gpio(gpio,CS);
		else
			reset_gpio(gpio,CS);
		set_gpio(gpio,CLK);
	}
}
int init_keypad(GPIO_TypeDef * Row_gpio,GPIO_TypeDef * Col_gpio,int Row_pin,int Col_pin){
	RCC->AHB2ENR |=RCC_AHB2ENR_GPIOAEN;     //enable
	RCC->AHB2ENR |=RCC_AHB2ENR_GPIOCEN;

	for(int a=0;a<4;a++){
		Col_gpio->MODER &= ~(0b11<<(2*(Col_pin+a)));   //output
		Col_gpio->MODER |= (0b01<<(2*(Col_pin+a)));

		Col_gpio->OTYPER &= ~(0b1<<(1*(Col_pin+a)));   //PP
		Col_gpio->OTYPER |= (0b0<<(1*(Col_pin+a)));

		Col_gpio->OSPEEDR &= ~(0b11<<(2*(Col_pin+a))); //
		Col_gpio->OSPEEDR |= (0b11<<(2*(Col_pin+a)));

		reset_gpio(Col_gpio,Col_pin+a);
	}
	for(int a=0;a<4;a++){
			Row_gpio->MODER &= ~(0b11<<(2*(Row_pin+a)));   //intput

			Row_gpio->PUPDR &= ~(0b00<<(2*(Row_pin+a)));
			Row_gpio->PUPDR |= (0b10<<(2*(Row_pin+a)));
		}
	return 0;
}
int check_keypad_input_one(GPIO_TypeDef* Row_gpio, GPIO_TypeDef* Col_gpio, int Row_pin, int Col_pin, int x, int y){
	int count=0;
	Col_gpio->ODR &= ~(0b1<<(Col_pin+y));
	Col_gpio->ODR |= (0b1<<(Col_pin+y));
	for(int a=0;a<400;a++)
		if(read_gpio(Row_gpio,Row_pin+x))
			count++;
	Col_gpio->ODR &= ~(0b1<<(Col_pin+y));
	Col_gpio->ODR |= (0b0<<(Col_pin+y));
	if(count>280)
		return 1;
	else
		return 0;
	}
void delay_without_interrupt(int msec){
	int loop_cnt = 500*msec;
	while(loop_cnt){
		loop_cnt--;
	}
}
int init_7seg(GPIO_TypeDef * gpio,int DIN,int CS,int CLK){

	RCC->AHB2ENR |=RCC_AHB2ENR_GPIOBEN;

	gpio->MODER &= ~(0b11<<(2*DIN));
	gpio->MODER |= (0b01<<(2*DIN));
	gpio->MODER &= ~(0b11<<(2*CS));
	gpio->MODER |= (0b01<<(2*CS));
	gpio->MODER &= ~(0b11<<(2*CLK));
	gpio->MODER |= (0b01<<(2*CLK));

	send_7seg(gpio,DIN,CS,CLK,SEG_ADDRESS_DISPLAY_TEST,0x0);
	send_7seg(gpio,DIN,CS,CLK,SEG_ADDRESS_DECODE_MODE,0x0);
	send_7seg(gpio,DIN,CS,CLK,SEG_ADDRESS_SCAN_LIMIT,0x7);
	send_7seg(gpio,DIN,CS,CLK,SEG_ADDRESS_ITENSITY,0xF);
	send_7seg(gpio,DIN,CS,CLK,SEG_ADDRESS_SHUTDOWN,0x1);

	return 0;
}
void operation(double *x,double *y,int op){
	switch(op){
		case 10:
			opans =*x+*y;
			break;
		case 11:
			opans =*x-*y;
			break;
		case 12:
			opans =(*x)*(*y);
			break;
		case 13:
			opans =(*x)/(*y);
			break;
	}
	//return ans;
}
int ans(double *nums,double *ops,int num,int op){
	double temp_ans=0;
	int index=0;
	int yes=0;
	do{
		index=0;
		yes=0;
		for(int i=0;i<op;i++){
			if(ops[i]==12||ops[i]==13){
				yes=1;
				operation(&nums[i],&nums[i+1],ops[i]);
				temp_ans=opans;
				index=i;
				nums[index]=temp_ans;
				op--;
				num--;
				for(int j=index;j<op;j++){
					ops[j]=ops[j+1];
				}
				for(int j=index+1;j<num;j++){
					nums[j]=nums[j+1];
				}
				break;
			}
		}
	}while(yes);
	do{
		index=0;
		yes=0;
		for(int i=0;i<op;i++){
				yes=1;
				operation(&nums[i],&nums[i+1],ops[i]);
				temp_ans=opans;
				index=i;
				nums[index]=temp_ans;
				op--;
				num--;
				break;
		}
		for(int j=index;j<op;j++){
			ops[j]=ops[j+1];
		}
		for(int j=index+1;j<num;j++){
			nums[j]=nums[j+1];
		}
	}while(yes);
	return nums[0]*100;
}
int main(){
	const int keypad[4][4]={       //10=+ 11 =- 12 =* 13=/ 15== 14=c
			{1,2,3,10},
			{4,5,6,11},
			{7,8,9,12},
			{15,0,14,13}
	};
	int	condition[4][4]={};
	double nums[100]={};
	double ops[99]={};
	int digital=1;
	int num=0;
	int op=0;
	double temp=0;
	int fuckyou=1;
	int error=0;
	int result=0;
	int answer=0;
	int temp2=0;
	int govern=0;
	int gg=0;
	if(init_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin)!=0){
		return -1;
	}
	if(init_keypad(ROW_gpio,COL_gpio,ROW_pin,COL_pin)!=0){
		return -1;
	}
	while(1){
		//int input=0;if
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				if(check_keypad_input_one(ROW_gpio,COL_gpio,ROW_pin,COL_pin,i,j)){
					if(condition[i][j]==0&&govern!=1){
						if(keypad[i][j]<10){
							fuckyou=0;
							if(digital<3){
								if(temp!=0)
									digital++;
								temp=temp+keypad[i][j];
							}
						}
						if(keypad[i][j]==14){
																for(int i=0;i<4;i++)
																	for(int j=0;j<4;j++)
																		condition[i][j]=0;
																for(int i=0;i<10;i++)
																	nums[i]=0;
																for(int i=0;i<9;i++)
																	ops[i]=0;
																digital=1;
																num=0;
																op=0;
																temp=0;
																//display_number(GPIOB,DIN_pin,CS_pin,CLK_pin,0,Get_Digits(0));
																error=0;
																fuckyou=1;
																result=0;
																answer=0;
																govern=0;
																temp2=0;
																if(init_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin)!=0){
																	return -1;
																}
																break;
						}

//						else{
//							if(fuckyou==1)
//								error=1;
//							else
//								error=0;
//							switch(keypad[i][j]){
//								case 14:
//									for(int i=0;i<4;i++)
//										for(int j=0;j<4;j++)
//											condition[i][j]=0;
//									for(int i=0;i<10;i++)
//										nums[i]=0;
//									for(int i=0;i<9;i++)
//										ops[i]=0;
//									digital=1;
//									num=0;
//									op=0;
//									temp=0;
//									//display_number(GPIOB,DIN_pin,CS_pin,CLK_pin,0,Get_Digits(0));
//									error=0;
//									fuckyou=1;
//									result=0;
//									answer=0;
//									break;
//								case 10:  //plus
//									digital=1;
//									nums[num]=temp;
//									num++;
//									ops[op]=10;
//									op++;
//									fuckyou=1;
//									temp=0;
//									break;
//								case 11:  //minus
//									digital=1;
//									nums[num]=temp;
//									num++;
//									ops[op]=11;
//									op++;
//									fuckyou=1;
//									temp=0;
//									break;
//								case 12:  //multiply
//									digital=1;
//									nums[num]=temp;
//									num++;
//									ops[op]=12;
//									op++;
//									fuckyou=1;
//									temp=0;
//									break;
//								case 13:  //devide
//									digital=1;
//									nums[num]=temp;
//									num++;
//									ops[op]=13;
//									op++;
//									fuckyou=1;
//									temp=0;
//									break;
//								case 15:
//									nums[num]=temp;
//									num++;
//									if(error!=1)
//										answer=ans(nums,ops,num,op);
//									result=1;
//									break;
//							}
//						}
						condition[i][j]=1;
					}
				}
				else{
						condition[i][j]=0;
				}
			}
		}
					if(temp2){
						for(int k=1;k<=Get_Digits(temp);k++)
							temp2=10*temp2;
					}
					temp2+=temp;
					if(temp2==0){
						for(int i=1;i<9;i++)
							send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,i,0);
					}
					else{
						display_number(GPIOB,DIN_pin,CS_pin,CLK_pin,temp2,Get_Digits(temp2));
						temp=0;
						digital=0;
					}
					int i,j;
					govern=0;
					for(i=0;i<4;i++){
						for(j=0;j<4;j++)
							if(condition[i][j]==1){
								govern=1;
							}
					}
	}
//		if(input==0)
//			for(int i=0;i<8;i++)
//				send_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin,i+1,15);
}
//one can use either ODR or MODER to manipulate the function!
