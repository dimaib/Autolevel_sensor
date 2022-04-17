#ifndef UART_H
#define UART_H

#include "main.h"

#define BAUD 9600L									//�������� ������ �������
#define UBRRL_value ((F_CPU/(BAUD*16))-1)				//��������� �������� �������� ������������ �������� ��� �������� UBRR

void init_USART(void); 								//������������� UART
void send_byte(char value); 						//�������� ������ ����� � UART
void print(char *str);								//�������� ������� ������ � UART

#endif	//UART_H