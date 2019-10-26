#include "pch.h"
#include "Timer.h"

#include <Windows.h>

//Max 144fps
const float kMaxDeltaTime = 1.0f / 144.0f;

Timer::Timer()
	: m_secondsPerCount(0.0)
	, m_deltaTime(-1.0)
	, m_baseTime(0)
	, m_pauseTime(0)
	, m_stopTime(0)
	, m_previousTime(0)
	, m_currentTime(0)
	, m_stopped(true)
{
	__int64 countsPerSecond;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&countsPerSecond));
	m_secondsPerCount = 1.0 / static_cast<double>(countsPerSecond);
}

float Timer::GetGameTime() const
{
	if (m_stopped)
	{
		return static_cast<float>((m_stopTime - m_pauseTime - m_baseTime) * m_secondsPerCount);
	}
	else
	{
		return static_cast<float>((m_currentTime - m_pauseTime - m_baseTime) * m_secondsPerCount);
	}
}

float Timer::GetDeltaTime() const
{
	return static_cast<float>(m_deltaTime > kMaxDeltaTime ? kMaxDeltaTime : m_deltaTime);
}

void Timer::Reset()
{
	__int64 currentTime;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentTime));

	m_baseTime = currentTime;
	m_previousTime = currentTime;
	m_stopTime = 0;
	m_stopped = false;
}

void Timer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime));

	if (m_stopped)
	{
		m_pauseTime += startTime - m_stopTime;
		m_previousTime = startTime;
		m_stopTime = 0;
		m_stopped = false;
	}
}

void Timer::Stop()
{
	if (!m_stopped)
	{
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_stopTime));
		m_stopped = true;
	}
}

void Timer::Tick()
{
	if (m_stopped)
	{
		m_deltaTime = 0.0;
		return;
	}

	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_currentTime));

	m_deltaTime = (m_currentTime - m_previousTime) * m_secondsPerCount;
	m_previousTime = m_currentTime;

	if (m_deltaTime < 0.0)
	{
		m_deltaTime = 0.0;
	}
}
