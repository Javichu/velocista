/*
* VelocistaLib.c
*
* Created: 14/01/2015 12:11:30
*  Author: Javi
*/

#include "VelocistaLib.h"

void motors_init()
{
	// configure for inverted PWM output on motor control pins:
	//  set OCxx on compare match, clear on timer overflow
	//  Timer0 and Timer2 count up from 0 to 255
	TCCR0A = TCCR2A = 0xF3;
	
	// use the system clock/8 (=2.5 MHz) as the timer clock
	TCCR0B = TCCR2B = 0x02;
	
	// initialize all PWMs to 0% duty cycle (braking)
	OCR0A = OCR0B = OCR2A = OCR2B = 0;
	
	// set PWM pins as digital outputs (the PWM signals will not
	// appear on the lines if they are digital inputs)
	DDRD |= (1 << PORTD3) | (1 << PORTD5) | (1 << PORTD6);
	DDRB |= (1 << PORTB3);
}

void RobotInit(){
	// initialize your QTR sensors
	unsigned char qtr_rc_pins[] = {SENSOR1, SENSOR2, SENSOR3, SENSOR4, SENSOR5, SENSOR6, SENSOR7, SENSOR8};
	qtr_rc_init(qtr_rc_pins, 8, 2000, IRLIGHT);
	motors_init();
}

void MoverMotores(int m1Speed, int m2Speed){
	OCR0A = 0;
	OCR2A = 0;
	
	if (m1Speed < 0){
		m1Speed = 0;
	}
	if (m2Speed < 0){
		m2Speed = 0;
	}
	
	if (INIT_SPEED < MAX_SPEED){
		if(m1Speed > INIT_SPEED){
			m1Speed = INIT_SPEED;
		}
		if(m2Speed > INIT_SPEED){
			m2Speed = INIT_SPEED;
		}
		INIT_SPEED++;
	}else{
		if(m1Speed > MAX_SPEED){
			m1Speed = MAX_SPEED;
		}
		if(m2Speed > MAX_SPEED){
			m2Speed = MAX_SPEED;
		}
	}
	
	OCR0B = m1Speed;
	OCR2B = m2Speed;
	
}

void PID(){
	
	qtr_read(sensors, QTR_EMITTERS_ON);
	
	for (int i=0; i < 8; i++){
		if (sensors[i] < 200){
			sensors[i] = 0;
		}
	}
	
	numerador = 0;
	denominador = 0;
	for (int i=0; i < 8; i++){
		numerador = numerador + (((long)(1000)) * ((long) (i+1)) * ((long)(sensors[i])));
		denominador = denominador + ((long) (sensors[i]));
	}
	
	if (denominador != 0){
		position = numerador / denominador;
	}
	
	int error = position - 4500;
	
	int motorSpeed = kP * error + kD * (error - lastError);
	lastError = error;
	
	int m1Speed = MAX_SPEED + motorSpeed;
	int m2Speed = MAX_SPEED - motorSpeed;
	
	MoverMotores(m1Speed, m2Speed);

}

