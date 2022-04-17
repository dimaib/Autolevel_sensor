//���� � ��������� � ����������� ��� ������ � UART

#include <avr/io.h>
#include "uart.h"

void init_USART() {									//������������� UART

	UBRRL = UBRRL_value;							//������� 8 ��� UBRRL_value
	UBRRH = (UBRRL_value >> 8);						//������� 8 ��� UBRRL_value
	UCSRB |=(1<<TXEN);								//��� ���������� ��������
	UCSRC |=(1<< URSEL)|(1<< UCSZ0)|(1<< UCSZ1);	//������������ ������ 8 ��� ������
}

void send_byte(char value) {						//�������� ������ ����� � UART
	while(!( UCSRA & (1 << UDRE)));					//������� ����� ��������� ����� ��������
	UDR = value;									//�������� ������ � �����, �������� ��������
}

void print(char *str)								//�������� ������� ������ � UART
{
	for(;str[0];str++) send_byte(str[0]);
}