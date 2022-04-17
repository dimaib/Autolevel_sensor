#ifndef MAIN
#define MAIN
#define TOGGLE_LED				PORTC^=(1<<0)			//������� ����������
#define TOGGLE_REL				PORTD^=(1<<2)			//������� ����
#define SET_LED					PORTC|=(1<<0)			//��������� ����������
#define RES_LED					PORTC&=~(1<<0)			//���������� ����������
#define SET_REL					PORTD|=(1<<2)			//��������� ����
#define RES_REL					PORTD&=~(1<<2)			//���������� ����
//#define GET_ADC					ADMUX=adc_num; ADCSRA|=(1<<ADSC);	//������ �� �������������� ���
#define TENZ					6
#define POROG					7

#define IZM_NUM					60						//���-�� ��������� ��� ��������� (�������� 60)
#define SENS					10						//���������������� ��������� ��� ����������� ����
#define AVER_NUM				10						//���-�� ��������� ��� ���������� ��������� ��������������
#define AVER_POROG				30						//���-�� ��������� ��� ���������� ������

#define POROG_ENABLE			1						//��������� ��� ��������� ������������ ������

#define GAIN_NUM				0						//����� ������������� ��� �������� INA333
#define REF_NUM					1						//����� ������������� ��� �������� ���������� INA333

/*���������� ������ SPI ���� �������������*/
#define SET_SDI 				PORTB|=(1<<6)
#define SET_CLK					PORTB|=(1<<7)
#define SET_CS_ref				PORTD|=(1<<5)
#define SET_CS_gain				PORTD|=(1<<6)

#define RES_SDI					PORTB&=~(1<<6)
#define RES_CLK					PORTB&=~(1<<7)
#define RES_CS_ref				PORTD&=~(1<<5)
#define RES_CS_gain				PORTD&=~(1<<6)
/*���������� ������ SPI ���� �������������*/

#define MIN_ADC					200						//����������� �������� ����������� ��� ������������� INA333
#define MAX_ADC					900						//������������ �������� ����������� ��� ������������� INA333
#endif
extern uint8_t ref;
extern uint8_t gain;