//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "Day13.h"

struct Bus
{
	int32				id;
	int32				time;
};

struct Schedule
{
	int32				earliest;
	std::vector<int32>	timestamps;

	Schedule()
	{
		earliest = 0;
	}
};

int32 RoundUp(int32 numToRound, int32 multiple)
{
	if (multiple == 0)
	{
		return numToRound;
	}

	int32 remainder = numToRound % multiple;
	if (remainder == 0)
	{
		return numToRound;
	}

	return (numToRound + multiple - remainder);
}

static int32	Solve_1(std::vector<std::string> input)
{
	int32						answer = 0;
	Schedule					schedule;
	std::vector<std::string>	parts;

	Remove(input[0], ",");
	schedule.earliest = std::stoi(input[0]);
	Split(parts, input[1], ",");

	for (int32 i = 0; i < parts.size(); i++)
	{
		if (parts[i] != "x")
		{
			schedule.timestamps.push_back(std::stoi(parts[i]));
		}
	}

	int32		index = 0;
	int32		highest = INT_MAX;

	for (int32 i = 0; i < schedule.timestamps.size(); i++)
	{
		int32	id = schedule.timestamps[i];
		int32	multiple = RoundUp(schedule.earliest, id) / id;
		
		int32	total = 0;
		do 
		{
			total += id;
		}
		while (total < schedule.earliest);
		
		if (total < highest)
		{
			highest = total;
			index = i;
		}
	}

	answer = ((RoundUp(schedule.earliest, schedule.timestamps[index]) - schedule.earliest) * schedule.timestamps[index]);
	printf("Answer: %d\n", answer);

	return answer;
}

static int32	Solve_2(std::vector<std::string> input)
{
	int32		answer = 0;

	printf("Answer: %d\n", answer);

	return answer;
}

void Day13::Part1()
{
	assert(Solve_1(
		{
			"939",
			"7,13,x,x,59,x,31,19"
		}
	) == 295);
	Solve_1(GetStrInput("inputs/Day13.txt"));
}

void Day13::Part2()
{
	//	assert(Solve_2(
	//		{
	//			"939",
	//			"7,13,x,x,59,x,31,19"
	//		}
	//	) == 286);
	//	Solve_2(GetStrInput("inputs/Day13.txt"));
}