/*
****************************************************************************
BSD License
Copyright (c) 2014, i-Vizon
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the i-Vizon.
4. Neither the name of the i-Vizon nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY Mageswaran.D ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL Mageswaran.D BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

****************************************************************************
*/
/*
* =============================================================================
*
*
*   FILENAME            : iv_profiler.cpp
*
*   DESCRIPTION         : To find the time elapsed between operations
*
*
*   AUTHOR              : Mageswaran D
*
*
*   CHANGE HISTORY      :
*
*   DATE                : 16th May 2014
*
*   File Created.
*
* =============================================================================
*/
#include <../inc/iv_profiler.h>
#include <../inc/iv_common.h>
#include <time.h>

iv::Profiler::Profiler()
{

}

void iv::Profiler::startProfiler()
{
    if(clock_gettime(CLOCK_REALTIME, &_startTime))
        DEBUG_STRING("Error: clock_getres");
}

void iv::Profiler::endProfiler()
{
    if(clock_gettime(CLOCK_REALTIME, &_endTime))
        DEBUG_STRING("Error: clock_getres");
}

double iv::Profiler::elapsedTimeInNanosecs()
{
    return _endTime.tv_nsec - _startTime.tv_nsec;
}

double iv::Profiler::elapsedTimeInSecs()
{
    return _endTime.tv_sec - _startTime.tv_sec;
}

void iv::Profiler::startCpuProfiler()
{
    if(clock_gettime(CLOCK_REALTIME, &_startTimeCpu))
        DEBUG_STRING("Error: clock_getres");
}

void iv::Profiler::endCpuProfiler()
{
    if(clock_gettime(CLOCK_REALTIME, &_endTimeCpu))
        DEBUG_STRING("Error: clock_getres");

    _cpuProfiling = _endTimeCpu.tv_nsec - _startTimeCpu.tv_nsec;
}

void iv::Profiler::startGpuProfiler()
{
    if(clock_gettime(CLOCK_REALTIME, &_startTimeGpu))
        DEBUG_STRING("Error: clock_getres");
}

void iv::Profiler::endGpuProfiler()
{
    if(clock_gettime(CLOCK_REALTIME, &_endTimeGpu))
        DEBUG_STRING("Error: clock_getres");

    _gpuProfiling = _endTimeGpu.tv_nsec - _startTimeGpu.tv_nsec;
}

double iv::Profiler::calculateEfficiency()
{
    _profileDifference = _cpuProfiling - _gpuProfiling;
    _efficiency = (_profileDifference / _cpuProfiling) * 100;
    return _efficiency;
}


