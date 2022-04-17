#include "adc.h"

#include <avr/io.h>

void init_adc()							//������������� ������ ���
{
	ADCSRA|=(1<<ADPS1);					//����� �������� ������� 64. ������� ������ ��� ~125��
	ADCSRA|=(1<<ADPS2);					//����� �������� ������� 64. ������� ������ ��� ~125��
	ADCSRA|=(1<<ADEN);					//���������� ������ ������ ���
	ADMUX|=(1<<REFS0);					//����� �������� ����������. Vcc �����������
}

uint16_t adc_convert(uint8_t chanel)	//������ �������������� � ���������� �������� ��������������
{
	ADMUX&=0xF0;						//����� ������� ��������������
	ADMUX|=chanel;
	ADCSRA|=(1<<ADSC);					//������ ��������������
	while(ADCSRA&(1<<ADSC));			//����������� ���� ��� �������� �������������� ���
	return (uint16_t)ADC;
}