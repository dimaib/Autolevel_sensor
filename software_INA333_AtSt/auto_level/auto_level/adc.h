#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

void init_adc();						//������������� ������ ���
uint16_t adc_convert(uint8_t chanel);	//������ �������������� � ���������� �������� ��������������

#endif	//ADC_H