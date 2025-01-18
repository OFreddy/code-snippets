


#ifndef PID_H_INCLUDED
#define PID_H_INCLUDED

#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include <stdio.h>
	#include <stdlib.h>
#endif

#define PID_BASE_TYPE float
#define PID_SAMPLETIME_MS_TYPE unsigned long

#define PID_CLAMP(VAL,MIN,MAX) (VAL<MIN?MIN:(VAL>MAX?MAX:VAL))

typedef struct S_PID
{
	// Controller parameters
	PID_BASE_TYPE kp;
	PID_BASE_TYPE ki;
	PID_BASE_TYPE kd;
	
	// Sample time
	PID_SAMPLETIME_MS_TYPE sampletime;
	PID_SAMPLETIME_MS_TYPE lastsampletime;
	
	// Input and output
	PID_BASE_TYPE input;
	PID_BASE_TYPE lastinput;
	PID_BASE_TYPE output;
	PID_BASE_TYPE maxoutput;
	PID_BASE_TYPE minoutput;

	// Terms
	PID_BASE_TYPE pterm;
	PID_BASE_TYPE iterm;
	PID_BASE_TYPE dterm;

	// Setpoint
	PID_BASE_TYPE setpoint;
	
	// Error and previous / sum error 
	PID_BASE_TYPE error;
	PID_BASE_TYPE preverror;
	
	// Sampling rate in ms
	
	
} T_PID;

extern void PID_Init(T_PID *pid, PID_BASE_TYPE kp, PID_BASE_TYPE ki, PID_BASE_TYPE kd, PID_SAMPLETIME_MS_TYPE sampletime);
extern void PID_SetTunings(T_PID *pid, PID_BASE_TYPE kp, PID_BASE_TYPE ki, PID_BASE_TYPE kd);
extern PID_BASE_TYPE PID_Compute(T_PID *pid, PID_BASE_TYPE setpoint, PID_BASE_TYPE input, PID_SAMPLETIME_MS_TYPE currenttime);


#endif // PID_H_INCLUDED