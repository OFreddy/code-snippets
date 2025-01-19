#include <stdio.h>

#include "pid.h"

void PID_Init(T_PID *pid, PID_BASE_TYPE kp, PID_BASE_TYPE ki, PID_BASE_TYPE kd, PID_SAMPLETIME_MS_TYPE sampletime)
{
	pid->sampletime = sampletime;
	
	pid->pterm = pid->iterm = pid->dterm = 0.0; 
	
	pid->lastinput = 0.0;
	
	// Default min and max output for anti wind-up
	pid->minoutput = 0.0;
	pid->maxoutput = 100.0;
	
	pid->preverror = 0.0;
	
	PID_SetTunings(pid, kp, ki, kd);
}

void PID_SetTunings(T_PID *pid, PID_BASE_TYPE kp, PID_BASE_TYPE ki, PID_BASE_TYPE kd)
{
	PID_BASE_TYPE SampleTimeInSec = ((double)pid->sampletime) / 1000.0;
	
	pid->kp = kp;
	pid->ki = ki * SampleTimeInSec;
	pid->kd = kd / SampleTimeInSec;
}

PID_BASE_TYPE PID_Compute(T_PID *pid, PID_BASE_TYPE setpoint, PID_BASE_TYPE input, PID_SAMPLETIME_MS_TYPE currenttime)
{
	if ((currenttime - pid->lastsampletime) >= pid->sampletime)
	{
		pid->error = setpoint - input;
		
		// calc iterm, dterm and pterm
		pid->pterm = pid->kp * pid->error;

		// anti wind up: check if iTerm exceeds max / min output
		pid->iterm += pid->ki * pid->error;
		pid->iterm = PID_CLAMP(pid->iterm, pid->minoutput, pid->maxoutput);

		pid->dterm = pid->kd * (input - pid->lastinput);
		
		// anti wind up: check if output exceeds max / min output
		pid->output = PID_CLAMP(pid->pterm + pid->iterm + pid->dterm, pid->minoutput, pid->maxoutput);
		
		pid->lastinput = input;
		pid->lastsampletime = currenttime;
		
		printf("E: %.2f P: %.2f I: %.2F D: %.2f\n", pid->error, pid->pterm, pid->iterm, pid->dterm);
	}
	
	return pid->output;
}