#ifndef UART_H
#define UART_H

#include "main.h"

#define BAUD 9600L									//Скорость обмена данными
#define UBRRL_value ((F_CPU/(BAUD*16))-1)				//Согластно заданной скорости подсчитываем значение для регистра UBRR

void init_USART(void); 								//инициализация UART
void send_byte(char value); 						//отправка одного байта в UART
void print(char *str);								//отправка массива данных в UART

#endif	//UART_H