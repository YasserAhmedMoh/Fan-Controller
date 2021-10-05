/*
 * dc_motor.c
 *
 *  Created on: Oct 5, 2021
 *      Author: yasser ahmed
 */
#include "avr/io.h" /* To use the ADC Registers */
#include "dc_motor.h"




void PWM_Timer0_Init(unsigned char set_duty_cycle)
{

	TCNT0 = 0; //Set Timer Initial value

	OCR0  = set_duty_cycle; // Set Compare Value

	DDRB  = DDRB | (1<<PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
void DcMotor_Init(void){

	GPIO_setupPinDirection(Motor_PORT_ID,PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(Motor_PORT_ID,PIN1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(Motor_PORT_ID,PIN3_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN2_ID,PIN_INPUT);

	GPIO_writePin(Motor_PORT_ID, PIN0_ID, LOGIC_LOW);
	GPIO_writePin(Motor_PORT_ID, PIN1_ID, LOGIC_LOW);
	GPIO_writePin(Motor_PORT_ID, PIN2_ID, LOGIC_LOW);

}
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	uint8 duty_cycle=(uint8)((uint32)(speed*255)/100);
	GPIO_writePort(Motor_PORT_ID,state);
	PWM_Timer0_Init(duty_cycle);
}
