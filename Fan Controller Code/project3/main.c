/*
 * main.c
 *
 *  Created on: Oct 5, 2021
 *      Author: Yasser Ahmed
 */
#include "avr/io.h" /* To use the ADC Registers */
#include "dc_motor.h"
#include "gpio.h"
#include "common_macros.h"
#include "lm35_sensor.h"
#include "std_types.h"
#include "lcd.h"
#include "adc.h"

int main(void){

	uint8 temp;
		ADC_ConfigType Adc_config={Prescaler_8,INTERNAL};
		LCD_init(); /* initialize LCD driver */
		ADC_init(&Adc_config); /* initialize ADC driver */
		DcMotor_Init();

		while(1)
		{

			temp = LM35_getTemperature();


			LCD_moveCursor(0,4);
			if(temp<30)
			{
				DcMotor_Rotate(STOP, 0);
				LCD_displayString("Fan is off");
			}
			else if(temp>=30&&temp<60)
			{
				DcMotor_Rotate(CW, 25);
				//LCD_moveCursor(1,7);
				LCD_displayString("Fan is on ");
			}
			else if(temp>=60&&temp<90)
			{
				DcMotor_Rotate(CW, 50);
				//	LCD_moveCursor(1,7);
				LCD_displayString("Fan is on ");
			}
			else if(temp>=90&&temp<120)
			{
				DcMotor_Rotate(CW, 75);
				//LCD_moveCursor(1,7);
				LCD_displayString("Fan is on ");
			}
			else if(temp>=120)
			{
				DcMotor_Rotate(CW, 100);
				//	LCD_moveCursor(1,7);
				LCD_displayString("Fan is on ");

			}

			 //  Display the temperature value every time at same position
			LCD_moveCursor(1,4);
			LCD_displayString("Temp =");
			if(temp >= 100)
			{
				LCD_intgerToString(temp);
			}
			else
			{
				LCD_intgerToString(temp);
				// In case the digital value is two or one digits print space in the next digit place
				LCD_displayCharacter(' ');
			}
			LCD_displayString("C");

		}





}
