#pragma once
#include "main.h"

const ULONG MAX_SAMPLE_COUNT = 50;
class CTimer
{
    public:
	CTimer();
	virtual ~CTimer();
    
	void Tick(float fLockFPS = 0.0f);
	unsigned long GetFrameRate(LPTSTR lpszString = nullptr)const;
	float GetTimeElapsed() const;
    
    private:
	bool            m_PerfHardware;             // Has Performance Counter
	float           m_TimeScale;                // Amount to scale counter
	float           m_TimeElapsed;              // Time elapsed since previous frame
	__int64         m_CurrentTime;              // Current Performance Counter
	__int64         m_LastTime;                 // Performance Counter last frame
	__int64         m_PerfFreq;                 // Performance Frequency
    
	float           m_FrameTime[MAX_SAMPLE_COUNT];
	ULONG           m_SampleCount;
    
	unsigned long   m_FrameRate;                // Stores current framerate
	unsigned long   m_FPSFrameCount;            // Elapsed frames in any given second
	float           m_FPSTimeElapsed;           // How much time has passed during FPS sample
};

