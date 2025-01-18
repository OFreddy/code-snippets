/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main()
{
    uint8_t tFinish = 1, tStart = UINT8_MAX, tPeriod = 10;
    uint8_t i;
    bool fExpired;
 
    for(i=0;i<UINT8_MAX;i++)
    {
        tStart = i;
        tFinish = i + tPeriod - 1;
        if ((uint8_t)(tFinish - tStart) >= tPeriod) {
	        fExpired = true;
        } else {
	        fExpired = false;
        }
        
        printf("i: %3u Expired: %u\n", i, fExpired);
    }

    return 0;
}



// Mit Tick
//     if (RTOS_TASKGETTICKCOUNT() - u32HostCommTimeout >= HOSTCOMM_TIMEOUT)
//     {
//        ...Timeout behandlung	
//     }

// Rücksetzen / Neustart:
// u32HostCommTimeout = RTOS_TASKGETTICKCOUNT();