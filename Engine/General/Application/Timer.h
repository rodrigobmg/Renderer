#pragma once

class Timer
{
public:
	Timer();
	~Timer() {}

	Timer(const Timer&) = delete;

	float GetGameTime() const;
	float GetDeltaTime() const;

	void Reset();
	void Start();
	void Stop();
	void Tick();

private:
	double	m_secondsPerCount;
	double	m_deltaTime;
	__int64	m_baseTime;
	__int64	m_pauseTime;
	__int64	m_stopTime;
	__int64	m_previousTime;
	__int64	m_currentTime;
	bool	m_stopped;
};