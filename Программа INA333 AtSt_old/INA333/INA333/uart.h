void init_UART()												//Инициализация UARTa
{
	#define BAUDRATE 9600
	UBRRH = ((unsigned)(F_CPU / (16.0 * BAUDRATE) - 1) >> 8) & 0x0F;
	UBRRL = ((unsigned)(F_CPU / (16.0 * BAUDRATE) - 1) >> 0) & 0xFF;
	UCSRB = 0<<RXEN|1<<TXEN|0<<RXCIE|0<<TXCIE;					//разрешение приёма и передачи. Разрешение прерывания по приёму байта
	UCSRC = 1<<URSEL|1<<UCSZ0|1<<UCSZ1|0<<UCSZ2|0<<UPM0|0<<UPM1|0<<USBS;
	//sei();
}

void print_byte(unsigned char c)								//Отправка байта. С ожиданием
{
	while(!(UCSRA&(1<<UDRE))){}									//Устанавливается, когда регистр свободен
	UDR = c;
}

void print_w(char *s)											//Отправка строки. С ожиданием
{
	while(*s!=0) print_byte(*s++);
}