#define F_CPU					8000000UL			//������� ������ �����������

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

//���������� ����������
 unsigned int zero	=0;								//���� ��� ���������
 uint8_t gain		=0;								//�������� INA333
 uint8_t ref		=0;								//������� ���������� �� INA333
//���������� ����������

int main(void)
{ 
	init_sys();										//��������� ������������� ���������� � ����������� + ������������� INA333
	int zero=0;										//���� ��� ���������
	unsigned long sum_porog=0;						//���������� ��� ������������ ������� � ����������� ����������
	int aver_porog=0;								//���������� ��� �������� �������� �������� ������
	uint8_t por_i=0;
	long aver_sum=0;								//���������� ��� ������������ ������� ����������
	int tenz_adj=0;									//���������� ��� ��������� ����������� �������� ��������������
	int tenz_real=0;								//�������� �������� ���
	uint8_t i_print=0;								//���������� ��� ������
	char buf[30]={0};								//����� ��� ������ ������
	int aver_ar_tenz[AVER_POROG]={0};
	zero=rezero();									//���������� "����"
	for(int i=0;i<AVER_POROG;i++){					//��������� ������������ ��������� ������
		sum_porog+=getadc(POROG);
	}
	aver_porog=sum_porog/AVER_POROG;				//���������� ������
	sum_porog=0;									//��������� ����� �������
	for(int i=0;i<AVER_NUM;i++) aver_ar_tenz[i]=zero;//�������� �������
	
// 	while(1){										//�������� ��������� ���� ���������
// 		sprintf(buf,"test \r\n");
// 		print_w(buf);
// 		TOGGLE_LED;
// 		_delay_ms(200);
// 	}												//�������� ��������� ���� ���������
	
	while (1)										//������� ����
    {
		/*���������� ��������� ��������������*/
		tenz_real=getadc(TENZ);
		for(int i=0;i<AVER_NUM-1;i++)	{
			aver_ar_tenz[i]=aver_ar_tenz[i+1];
			aver_sum+=aver_ar_tenz[i];
		}
		aver_ar_tenz[AVER_NUM-1]=tenz_real;
		aver_sum=((aver_sum+tenz_real)/AVER_NUM)-zero;
		tenz_adj=aver_sum;aver_sum=0;
		/*���������� ��������� ��������������*/	
		
		/*���������� ������*/
		sum_porog+=getadc(POROG); por_i++;			//���������� � ����� ������� ��������� ������ � ����������� ������� ���������
		if(por_i>=AVER_POROG) {						//���� ��������� ����������� ���-�� ���������, ��:
			aver_porog=sum_porog/AVER_POROG;		//��������� �����
			sum_porog=0; por_i=0;					//�������� ����� ������� � ������� ���������
		}
		/*���������� ������*/
		
		i_print++;//i_print=0;
		
		if(i_print>3){ //20
			sprintf(buf, "%d\t%d\t%d\t%d\tg=%d\tr=%d\r\n",tenz_adj,tenz_real,zero, aver_porog,gain,ref);				//����� ��������� �������� ���
			print_w(buf);
			i_print=0;			
		}
		
		if((tenz_adj>=aver_porog||tenz_adj<=-100)&&POROG_ENABLE){					//&&0 ������� �� ��� ����������� ������� �������. ������ ��� ���������� �������
			sprintf(buf,"Porog...%d\\%d\r\n",tenz_adj,aver_porog);
			print_w(buf);
			SET_LED; SET_REL;						//������ ���������, ������������ ����� �������
			_delay_ms(200);  RES_REL;				//��� ����� ������������, � ���������� ����� �������
			_delay_ms(1500); 						//��� ������, ��� ���������� ���������� ��������������
			zero=rezero(); RES_LED;					//�������� � ���������� ���������
			for(int i=0;i<AVER_NUM;i++) aver_ar_tenz[i]=zero;
		}	
		//TOGGLE_LED;
		_delay_ms(10);
		//_delay_ms(100);
			
    }
}