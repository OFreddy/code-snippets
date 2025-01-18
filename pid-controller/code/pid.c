

#include "pid.h"

void PID_Init(T_PID *pid, PID_BASE_TYPE kp, PID_BASE_TYPE ki, PID_BASE_TYPE kd, PID_SAMPLETIME_MS_TYPE sampletime)
{
	pid->kp = kp;
	pid->ki = ki;
	pid->kd = kd;
	
	pid->sampletime = sampletime;
	
	pid->pterm = pid->iterm = pid->dterm = 0.0; 
	
	// Default min and max output for anti wind-up
	pid->minoutput = 0.0;
	pid->maxoutput = 100.0;
	
	pid->preverror = 0.0;
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
	}
	
	return pid->output;
}