#include "main.h"

// ISR(ADC_vect) //прерывание окончания измерения АЦП
// {
// // 	if(adc_num==ADC6){
// // 		adc_num=ADC7;
// // 		adc_6=ADCL|ADCH<<8;
// // 		}else{
// // 		adc_num=ADC6;
// // 		adc_7=ADCL|ADCH<<8;
// // 	}
// // 	GET_ADC
// }

void adc_init(){
	ADCSRA|=(1<<ADEN)|(0<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//разрешение использования АЦП и частота измерения 128кГц
	ADMUX|=(1<<REFS0);												//ИОН AVCC
}

unsigned int getadc(uint8_t adc_num){								//функция начинает преобразование для канала АЦП и возвращает результат
	ADMUX=adc_num;													//задаём канал измерения
	ADCSRA |= (1<<ADSC);											//начинаем преобразование
	while((ADCSRA & (1<<ADSC)));									//ожидание окончания преобразования
	return ADCL|ADCH<<8;											//возврат преобразования от АЦП
}