/*
 * 44ANewADC.c
 *
 * Created: 22.04.2021 22:45:00
 * Author : Leo
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char lig=128;
char bit;
char EMA = 250;
char DMA = 250;
char ALFA1 = 8;
char ALFA2 = 32;

ISR(TIM1_OVF_vect)
{
	EMA=(ADCH/ALFA1)+(EMA/(1-ALFA1));
	DMA=(EMA/ALFA2)+(DMA/(1-ALFA2));
	if ((DMA-EMA)>32)
	{
		bit=1;
	} 
	else
	{
		bit=0;
	}
	
}

int main(void)
{
	/////////////////INTERRUPTION///////////
	
	TIMSK1 |= (1<<TOIE1);//���������� �� ������ �������.��������
	TCCR1B |= (0<<CS12)|(0<<CS11)|(1<<CS10); //������ ��� �����������
	TCNT1 = 0;//�������� ������/�������
	
	sei();//��������� ��������� ����������
	
	//////////////////////////////ADC///////////////////////////////
	
	//��� ���� ����� A �� ����
	DDRA=0;
	ADMUX=
	(1<<MUX0)|(0<<MUX1)|(0<<MUX2)|(0<<MUX3)|(0<<MUX4)|(0<<MUX5)|//����� ��������� �����
	(0<<REFS0)|(1<<REFS1);//����� ���
	
	ADCSRB=
	(0<<BIN)|(0<<ACME)|//���������� ����������� ��������
	(1<<ADLAR)|//�������� ������
	(0<<ADTS0)|(0<<ADTS1)|(0<<ADTS2);//���������� ����������� ��������
	
	ADCSRA=
	(1<<ADEN)|//��������� ������ ���
	(1<<ADPS0)|(0<<ADPS1)|(1<<ADPS2)|//�������������� ����������
	(1<<ADATE)|//����-��������� ���� ���
	(0<<ADIE);//������ ����������
	
	//������ ���
	ADCSRA|=(1<<ADSC);
	
	DIDR0=0xff;//���������� �������� ������� �� ����� ���
	
	///////////////////PWD////////////////////////
	
	//��������� ���� ������ �� �����
	DDRB = 0b11111111;
	//��������� �������
	TCCR0A = 0b10000011;
	TCCR0B = 0b00000010;
	OCR0A=128;
	
	//////////////////����������////////////////////
	
	/*
	public: unsigned char lig=128;
	char bit;
	char EMA = 250;
	char DMA = 250;
	char ALFA1 = 8;
	char ALFA2 = 32;
	*/
	
    while (1) 
    {
		OCR0A=ADCH;
    }
}

