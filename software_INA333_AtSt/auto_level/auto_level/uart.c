//Файл с функциями и переменными для работы с UART

#include <avr/io.h>
#include "uart.h"

void init_USART() {									//инициализация UART

	UBRRL = UBRRL_value;							//Младшие 8 бит UBRRL_value
	UBRRH = (UBRRL_value >> 8);						//Старшие 8 бит UBRRL_value
	UCSRB |=(1<<TXEN);								//Бит разрешения передачи
	UCSRC |=(1<< URSEL)|(1<< UCSZ0)|(1<< UCSZ1);	//Устанавливем формат 8 бит данных
}

void send_byte(char value) {						//отправка одного байта в UART
	while(!( UCSRA & (1 << UDRE)));					//Ожидаем когда очистится буфер передачи
	UDR = value;									//Помещаем данные в буфер, начинаем передачу
}

void print(char *str)								//отправка массива данных в UART
{
	for(;str[0];str++) send_byte(str[0]);
}