#include "AATree.h"
CStopWatch::CStopWatch()
{
    m_start.QuadPart = 0;
    m_stop.QuadPart = 0;
    QueryPerformanceFrequency(&m_frequency);
}
// Start
void CStopWatch::start()
{
    QueryPerformanceCounter(&m_start);
}
// Stop
void CStopWatch::stop()
{
    QueryPerformanceCounter(&m_stop);
}
// Computing time(s)
double CStopWatch::getElapsedTime()
{
    double  r;
    LARGE_INTEGER time;
    time.QuadPart = m_stop.QuadPart - m_start.QuadPart;
    r = (double)time.QuadPart / (double)m_frequency.QuadPart;
    r *= 1000000;
    return r;
}
