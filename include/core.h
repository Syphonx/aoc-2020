//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#pragma once

#include <Windows.h>
#include <process.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <forward_list>
#include <list>
#include <deque>
#include <array>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <set>
#include <unordered_set>
#include <cassert>
#include <stack>

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;

typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

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

static std::vector<int32_t> GetIntInput(std::string filepath)
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

static std::vector<std::string> GetStrInput(std::string filepath)
{
	std::vector<std::string> lines;
	std::string line;
	std::ifstream infile(filepath, std::ios_base::in);

	lines.clear();

	while (getline(infile, line, '\n'))
	{
		lines.push_back(line);
	}

	return lines;
}

static bool Split(std::vector<std::string> &out_result, std::string s, std::string delimiter)
{
	bool success = false;
	size_t start = 0;
	size_t end = s.find(delimiter);

	while (end != std::string::npos)
	{
		out_result.push_back(s.substr(start, end - start));
		start = end + delimiter.length();
		end = s.find(delimiter, start);
		success = true;
	}

	out_result.push_back(s.substr(start, end));

	return success;
}