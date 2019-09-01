/*
 * TypesDef.h
 *
 * Created: 14/01/2015 12:14:24
 *  Author: Javi
 */ 


#ifndef TYPESDEF_H_
#define TYPESDEF_H_

#include <pololu/orangutan.h>

//#define VELOCISTA_AMARILLO
#define VELOCISTA_AZUL

#define IRLIGHT IO_C5
#define SENSOR1 IO_B2
#define SENSOR2 IO_D2
#define SENSOR3 IO_D4
#define SENSOR4 IO_D7
#define SENSOR5 IO_C2
#define SENSOR6 IO_C1
#define SENSOR7 IO_C3
#define SENSOR8 IO_C4

#ifdef VELOCISTA_AMARILLO
	static int MAX_SPEED = 255;
	static int INIT_SPEED = 0;
	static float kP = 0.9;
	static float kD = 11.5;
#endif

#ifdef VELOCISTA_AZUL
	static int MAX_SPEED = 80;
	static int INIT_SPEED = 0;
	static float kP = 5.1;
	static float kD = 14.1;
#endif

static int lastError = 0;

unsigned int sensors[8];

static long numerador = 0;
static long denominador = 0;
static long position = 0;

char send_buffer[32];

#endif /* TYPESDEF_H_ */