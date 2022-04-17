#include "main.h"

// ISR(ADC_vect) //���������� ��������� ��������� ���
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
	ADCSRA|=(1<<ADEN)|(0<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//���������� ������������� ��� � ������� ��������� 128���
	ADMUX|=(1<<REFS0);												//��� AVCC
}

unsigned int getadc(uint8_t adc_num){								//������� �������� �������������� ��� ������ ��� � ���������� ���������
	ADMUX=adc_num;													//����� ����� ���������
	ADCSRA |= (1<<ADSC);											//�������� ��������������
	while((ADCSRA & (1<<ADSC)));									//�������� ��������� ��������������
	return ADCL|ADCH<<8;											//������� �������������� �� ���
}