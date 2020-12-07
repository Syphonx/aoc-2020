//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#pragma once

#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <iosfwd>
#include <fstream>
#include <vector>
#include <iostream>
#include <iterator>

class IDay
{
public:
	virtual void Part1() = 0;
	virtual void Part2() = 0;
};

class QueryPerformanceTimer
{

public:

	QueryPerformanceTimer()
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		m_inverseFrequency = 1000000.0 / (double)frequency.QuadPart;
	}

	void Start()
	{
		QueryPerformanceCounter(&m_start);
	}

	double Get()
	{
		QueryPerformanceCounter(&m_stop);

		double time = (double)(m_stop.QuadPart - m_start.QuadPart) * m_inverseFrequency;
		m_start = m_stop;

		// time value is in micro seconds
		return time;
	}

	LARGE_INTEGER m_start;
	LARGE_INTEGER m_stop;
	double m_inverseFrequency;
};

class ScopedQueryPerformanceTimer
{

public:

	ScopedQueryPerformanceTimer(const char*	aMsg = NULL)
	{
		m_msg = aMsg;
		m_timer.Start();
	}

	~ScopedQueryPerformanceTimer()
	{
		double timeUsed = m_timer.Get();
		printf("%s %f\n", m_msg, timeUsed / 1000.0);
	}

	QueryPerformanceTimer m_timer;
	const char*	m_msg;
};

static std::vector<int32_t> GetInput(std::string filepath)
{
	std::ifstream is(filepath);
	std::istream_iterator<int32_t> start(is), end;
	std::vector<int32_t> numbers(start, end);

#if 0
	std::cout << "Read " << numbers.size() << " numbers" << std::endl;
#endif

	// print the numbers to stdout
#if 0
	std::cout << "numbers read in:\n";
	std::copy(numbers.begin(), numbers.end(),
			  std::ostream_iterator<double>(std::cout, " "));
	std::cout << std::endl;
#endif

	return numbers;
}
