#define F_CPU					8000000UL			//частоты работы контроллера

#include <avr/io.h> //atmega8
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "main.h"
#include "adc.h"
#include "uart.h"
#include "functions.h"

//глобальные переменные
 unsigned int zero	=0;								//ноль для измерений
 uint8_t gain		=0;								//усиление INA333
 uint8_t ref		=0;								//опорное напряжение на INA333
//глобальные переменные

int main(void)
{ 
	init_sys();										//начальная инициализация переменных и интерфейсов + автопостройка INA333
	int zero=0;										//ноль для измерений
	unsigned long sum_porog=0;						//переменная для суммирования порогов и дальнейшего усреднения
	int aver_porog=0;								//переменная для хранения среднего значения порога
	uint8_t por_i=0;
	long aver_sum=0;								//переменная для суммирования массива усреднения
	int tenz_adj=0;									//переменная для обработки измеренного значения тензорезистора
	int tenz_real=0;								//реальное значение АЦП
	uint8_t i_print=0;								//переменная для вывода
	char buf[30]={0};								//буфер для вывода строки
	int aver_ar_tenz[AVER_POROG]={0};
	zero=rezero();									//вычисление "нуля"
	for(int i=0;i<AVER_POROG;i++){					//начальное суммирование измерений порога
		sum_porog+=getadc(POROG);
	}
	aver_porog=sum_porog/AVER_POROG;				//усреднение порога
	sum_porog=0;									//обнуление суммы порогов
	for(int i=0;i<AVER_NUM;i++) aver_ar_tenz[i]=zero;//обнулене массива
	
// 	while(1){										//заглушка основгого тела программы
// 		sprintf(buf,"test \r\n");
// 		print_w(buf);
// 		TOGGLE_LED;
// 		_delay_ms(200);
// 	}												//заглушка основгого тела программы
	
	while (1)										//главный цикл
    {
		/*усреднение показаний тензорезистора*/
		tenz_real=getadc(TENZ);
		for(int i=0;i<AVER_NUM-1;i++)	{
			aver_ar_tenz[i]=aver_ar_tenz[i+1];
			aver_sum+=aver_ar_tenz[i];
		}
		aver_ar_tenz[AVER_NUM-1]=tenz_real;
		aver_sum=((aver_sum+tenz_real)/AVER_NUM)-zero;
		tenz_adj=aver_sum;aver_sum=0;
		/*усреднение показаний тензорезистора*/	
		
		/*усреднение порога*/
		sum_porog+=getadc(POROG); por_i++;			//прибавляем к сумме текущее показание порога и увеличиваем счётчик измерений
		if(por_i>=AVER_POROG) {						//если произошло определённое кол-во измерений, то:
			aver_porog=sum_porog/AVER_POROG;		//усредняем порог
			sum_porog=0; por_i=0;					//обнуляем сумму порогов и счётчик измерений
		}
		/*усреднение порога*/
		
		i_print++;//i_print=0;
		
		if(i_print>3){ //20
			sprintf(buf, "%d\t%d\t%d\t%d\tg=%d\tr=%d\r\n",tenz_adj,tenz_real,zero, aver_porog,gain,ref);				//вывод усреднёных значений АЦП
			print_w(buf);
			i_print=0;			
		}
		
		if((tenz_adj>=aver_porog||tenz_adj<=-100)&&POROG_ENABLE){					//&&0 никогда не даёт выполниться данному условию. просто для отключения функции
			sprintf(buf,"Porog...%d\\%d\r\n",tenz_adj,aver_porog);
			print_w(buf);
			SET_LED; SET_REL;						//зажечь светодиод, активировать выход касания
			_delay_ms(200);  RES_REL;				//ждём время срабатывания, и сбрасываем выход касания
			_delay_ms(1500); 						//ждём секнду, для устранения деформации тензорезистора
			zero=rezero(); RES_LED;					//обнуляем и сбрасываем светодиод
			for(int i=0;i<AVER_NUM;i++) aver_ar_tenz[i]=zero;
		}	
		//TOGGLE_LED;
		_delay_ms(10);
		//_delay_ms(100);
			
    }
}