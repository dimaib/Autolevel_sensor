#ifndef MAIN
#define MAIN
#define TOGGLE_LED				PORTC^=(1<<0)			//мигание светодиода
#define TOGGLE_REL				PORTD^=(1<<2)			//мигание реле
#define SET_LED					PORTC|=(1<<0)			//включение светодиода
#define RES_LED					PORTC&=~(1<<0)			//отключение светодиода
#define SET_REL					PORTD|=(1<<2)			//включение реле
#define RES_REL					PORTD&=~(1<<2)			//отключение реле
//#define GET_ADC					ADMUX=adc_num; ADCSRA|=(1<<ADSC);	//запрос на преобразование АЦП
#define TENZ					6
#define POROG					7

#define IZM_NUM					60						//кол-во измерений при обнулении (максимум 60)
#define SENS					10						//чувствительность измерений при компенсации нуля
#define AVER_NUM				10						//кол-во измерений для усреднения показаний тензорезистора
#define AVER_POROG				30						//кол-во измерений для усреднения порога

#define POROG_ENABLE			1						//разрешить или запретить срабатывание порога

#define GAIN_NUM				0						//номер потенциометра для усиления INA333
#define REF_NUM					1						//номер потенциометра для опорного напряжения INA333

/*управление пинами SPI шины потенцеометра*/
#define SET_SDI 				PORTB|=(1<<6)
#define SET_CLK					PORTB|=(1<<7)
#define SET_CS_ref				PORTD|=(1<<5)
#define SET_CS_gain				PORTD|=(1<<6)

#define RES_SDI					PORTB&=~(1<<6)
#define RES_CLK					PORTB&=~(1<<7)
#define RES_CS_ref				PORTD&=~(1<<5)
#define RES_CS_gain				PORTD&=~(1<<6)
/*управление пинами SPI шины потенцеометра*/

#define MIN_ADC					200						//минимальное значение гистерезиса при атоподстройке INA333
#define MAX_ADC					900						//максимальное значение гистерезиса при атоподстройке INA333
#endif
extern uint8_t ref;
extern uint8_t gain;