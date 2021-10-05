/*
 * dc_motor.h
 *
 *  Created on: Oct 5, 2021
 *      Author: yasser ahmed
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"
#include "gpio.h"
#include "common_macros.h"
#include "lm35_sensor.h"

#define Motor_PORT_ID PORTB_ID
typedef enum
{
	STOP,CW,A_CW
}DcMotor_State;

void PWM_Timer0_Init(unsigned char set_duty_cycle);

void DcMotor_Init(void);

void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
