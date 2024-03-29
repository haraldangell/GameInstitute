#include "CTimer.h"

CTimer::CTimer()
{
	// Query performance hardware and setup time scaling values
	if (QueryPerformanceFrequency((LARGE_INTEGER *)&m_PerfFreq))
	{
		m_PerfHardware = TRUE;
		QueryPerformanceCounter((LARGE_INTEGER *)&m_LastTime);
		m_TimeScale = 1.0f / m_PerfFreq;
	}
	else
	{
		// no performance counter, read in using timeGetTime 
		m_PerfHardware = FALSE;
		m_LastTime = timeGetTime();
		m_TimeScale = 0.001f;

	} // End If No Hardware

	  // Clear any needed values
	m_SampleCount = 0;
	m_FrameRate = 0;
	m_FPSFrameCount = 0;
	m_FPSTimeElapsed = 0.0f;
}

CTimer::~CTimer()
{
}

void CTimer::Tick(float fLockFPS)
{
	float fTimeElapsed;

	// Is performance hardware available?
	if (m_PerfHardware)
	{
		// Query high-resolution performance hardware
		QueryPerformanceCounter((LARGE_INTEGER *)&m_CurrentTime);
	}
	else
	{
		// Fall back to less accurate timer
		m_CurrentTime = timeGetTime();

	} // End If no hardware available

	  // Calculate elapsed time in seconds
	fTimeElapsed = (m_CurrentTime - m_LastTime) * m_TimeScale;

	// Smoothly ramp up frame rate to prevent jittering
	//if ( fLockFPS == 0.0f ) fLockFPS = (1.0f / GetTimeElapsed()) + 20.0f;

	// Should we lock the frame rate ?
	if (fLockFPS > 0.0f)
	{
		while (fTimeElapsed < (1.0f / fLockFPS))
		{
			// Is performance hardware available?
			if (m_PerfHardware)
			{
				// Query high-resolution performance hardware
				QueryPerformanceCounter((LARGE_INTEGER*)&m_CurrentTime);
			}
			else
			{
				// Fall back to less accurate timer
				m_CurrentTime = timeGetTime();

			} // End If no hardware available

			  // Calculate elapsed time in seconds
			fTimeElapsed = (m_CurrentTime - m_LastTime) * m_TimeScale;

		} // End While
	} // End If

	  // Save current frame time
	m_LastTime = m_CurrentTime;

	// Filter out values wildly different from current average
	if (fabsf(fTimeElapsed - m_TimeElapsed) < 1.0f)
	{
		// Wrap FIFO frame time buffer.
		memmove(&m_FrameTime[1], m_FrameTime, (MAX_SAMPLE_COUNT - 1) * sizeof(float));
		m_FrameTime[0] = fTimeElapsed;
		if (m_SampleCount < MAX_SAMPLE_COUNT) m_SampleCount++;

	} // End if


	  // Calculate Frame Rate
	m_FPSFrameCount++;
	m_FPSTimeElapsed += fTimeElapsed;
	if (m_FPSTimeElapsed > 1.0f)
	{
		m_FrameRate = m_FPSFrameCount;
		m_FPSFrameCount = 0;
		m_FPSTimeElapsed = 0.0f;
	} // End If Second Elapsed

	  // Count up the new average elapsed time
	m_TimeElapsed = 0.0f;
	for (ULONG i = 0; i < m_SampleCount; i++) m_TimeElapsed += m_FrameTime[i];
	if (m_SampleCount > 0) m_TimeElapsed /= m_SampleCount;

}

unsigned long CTimer::GetFrameRate(LPTSTR lpszString) const
{
	// Fill string buffer ?
	if (lpszString)
	{

		// Copy frame rate value into string
		_itot(m_FrameRate, lpszString, 10);

		// Append with FPS
		_tcscat(lpszString, _T(" FPS"));

	} // End if build FPS string

	return m_FrameRate;
}

float CTimer::GetTimeElapsed() const
{
	return m_TimeElapsed;
}
