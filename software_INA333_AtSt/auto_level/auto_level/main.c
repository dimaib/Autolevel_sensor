#include "main.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "stdio.h"
#include "uart.h"
#include "adc.h"
#include "math.h"

void dp_set_val(uint8_t num_channel, uint8_t val)
{
	_delay_ms(1);
	DP_CLK_RES;
	if(num_channel) DP_GAIN_ON; else DP_REF_ON;
	_delay_ms(2);
	for(uint8_t i=0;i<8;i++){
		DP_CLK_SET;
		if(val&(128>>i)) DP_SDI_SET; else DP_SDI_RES;
		DP_CLK_RES;
	}
	DP_CLK_SET;
	_delay_ms(1);
	if(num_channel) DP_GAIN_OFF; else DP_REF_OFF;
}

void pin_init()
{
	DDRC|=(1<<0);						//настройка выхода светодиода
	DDRB|=(1<<6)|(1<<7);				//настройка выхода CLK и SDI
	DDRD|=(1<<5)|(1<<6)|(1<<2);			//настройка выхода CS_ref, CS_gain и выхода срабатывания датчика
	DP_REF_OFF; DP_GAIN_OFF;
	DP_CLK_RES; DP_SDI_RES;
	dp_set_val(NUM_GAIN,5);
	dp_set_val(NUM_REF,0);
}

uint8_t auto_tune()															//функция для автоматической подстройки коэф. усиления и опорного сигнала INA333
{
	uint16_t adc_val=adc_convert(ADC_TENZ);
	if (adc_val<MIN_VAL){													//если значение АЦП меньше минимального корректного уровня, то требуетс поднять его с помощью напряжения смещения
		for(uint8_t i=0;i<255;i++){
			dp_set_val(NUM_REF,i);
			_delay_ms(2);
			if(adc_convert(ADC_TENZ)>=MIN_VAL) break;						//увеличиваем напряжение смещения до тех пор, пока минимальное, корреткное значение АЦП меньше минимума
		}
	}else if(adc_val>=1000){												//если значение АЦП больше корректного уровня, то требуется уго снизить с помощью уменьшения коэф. усиления
		dp_set_val(NUM_REF,0);
		for(uint8_t i=6;i<255;i++){
			dp_set_val(NUM_GAIN,i);
			_delay_ms(2);
			if(adc_convert(ADC_TENZ)<=MAX_VAL) break;						//уменьшаем коэф. усиления до тех пор пока значение АЦП больше максимума
		}
	}
	_delay_ms(50);
	adc_val=adc_convert(ADC_TENZ);
	if(adc_val>=MIN_VAL&&adc_val<=MAX_VAL) return 1; else return 0;			//возвращаем результат калибровки
}

uint16_t resize()
{
	if(!auto_tune()){
		while(1){
			LED_TOG;
			OUT_SET;
			print("Auto-tune error!\r\n");
			_delay_ms(100);
		}
	}else print("Auto-tune OK!\r\n");
	_delay_ms(100);
	return adc_convert(ADC_TENZ);
}

int main(void)
{
	init_USART();
	init_adc();
	pin_init();
	char buf[100]={0};
	_delay_ms(100);
	uint16_t zero=resize();
	int result=0;
	uint16_t porog=0;
    while (1) 
    {
		result=abs(adc_convert(ADC_TENZ)-zero);
		porog=adc_convert(ADC_POROG);
		sprintf(buf, "Porog:%d\tTenz:%d\r\n" ,porog,result);
		print(buf);
		if(result>porog){
			OUT_SET;
			LED_SET;
			_delay_ms(DELAY_OUT);
			OUT_RES;
			print("On out..\r\n");
			_delay_ms(200);
			zero=resize();
			_delay_ms(DELAY_WAIT);
			LED_RES;
		}
		_delay_ms(50);
    }
}
