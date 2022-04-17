#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

void init_adc();						//инициализация модуля АЦП
uint16_t adc_convert(uint8_t chanel);	//запуск преобразования и считывания значения преобразования

#endif	//ADC_H