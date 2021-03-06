#include "main.h"

unsigned int rezero(){								//???????????/???????? ????
	char buf[20];									//????? ??? ?????? ?????????
	unsigned long sum_zero=0;						//?????????? ??? ????????????
	for(int i=0;i<IZM_NUM;i++){
		sum_zero+=getadc(TENZ);
		_delay_ms(10);
	}
	sum_zero/=IZM_NUM;
	sprintf(buf,"Zero=%ld\r\n",sum_zero);
	print_w(buf);
	return (int)sum_zero;
}

void set_rez(uint8_t res_om, uint8_t num)			//????????? ???????? ????????????? ?????????????. 0 - gain, 1 - ref
{
	RES_CLK;
	if(num==REF_NUM) RES_CS_ref; else RES_CS_gain;	//???????? SPI ???? ?????????????
	for(int ii=0;ii<8;ii++){						//???? ??? ?????????? ???? ?? ????????? ?????????????
		SET_CLK;									//????????? ? ??????? ???? ???????????? ?????????????
		if(res_om&(128>>ii)) SET_SDI; else RES_SDI;	//???????????? ????? ??????? ?? ???????? ????. ???? ??? ????? ???????, ?? ?????????? SDI ? ???????, ????? ??????????
		RES_CLK;									//????? ???? ???????????? ?????????????
	}
	SET_CLK;										//????????????? SPI ???? ?????????????
	if(num==REF_NUM) SET_CS_ref; else SET_CS_gain;	//???????? SPI ???? ?????????????
}

void auto_tuning()									//?????????????? ?????????? ???????? ? ???????? ?????????? ??? INA333
{
	unsigned int tenz_real=0;						//?????????? ??? ?????????? ? ??? ???
	set_rez(0,0);									//????????????? ???????? (0)
	set_rez(0,1);									//????????????? ???????? ?????????? (0)
	for (uint8_t g=0;g<240;g+=25){					//???? ?????????????? ?????????? ???????? INA333
		set_rez(g,0);								//???????? ??????? ????????? ???????? ? ????????????
		for(uint8_t r=0;r<255;r++){					//???? ??? ?????????????? ?????????? ???????? ?????????? ??? INA333
			set_rez(r,1);							//???????? ??????? ????????? ???????? ?????????? ? ????????????
			tenz_real=getadc(TENZ);					//?????? ???????? ??? ??????????????
			if(tenz_real>MIN_ADC && tenz_real<MAX_ADC){//???? ?????? ???????? ?????????? ????????, ?? ???????? ?? ?????
				ref=r;
				break;
			}
			TOGGLE_LED;								//?????? ??????????? ?? ????? ??????????
		}
		if(tenz_real>MIN_ADC && tenz_real<MAX_ADC){	//???? ?????? ???????? ?????????? ????????, ?? ???????? ?? ?????
				gain=g;
				break;
			}
		}
}

void init_sys(){									//????????? ?????????????
	/*????????????? ??????*/
	DDRC=(1<<0);									//0 - Led ?? ????? 
	DDRD=(1<<2)|(1<<5)|(1<<6);						//2 - Rel, 5 - CS_ref, 6 - CS_gain ?? ?????
	DDRB=(1<<6)|(1<<7);								//6 - SDI, 7 - SCK ?? ?????
	/*????????????? ??????*/
	adc_init();										//????????????? ADC
	init_UART();									//????????????? UART
	auto_tuning();									//?????????????? ?????????? INA333
	print_w("Start...\r\n");						//????????? ?? ???????? ?????? ???????????
	_delay_ms(200);									//???????? ??? ?????????? ??????? ????????? ??? ???? ???????
	/*????????? ??????? ???????? ???????? ??????*/

	/*????????? ??????? ???????? ???????? ??????*/
}