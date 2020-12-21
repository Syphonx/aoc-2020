//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "Day13.h"

struct Schedule
{
	int64				earliest;
	std::vector<int64>	timestamps;
	std::vector<int64>	offsets;

	Schedule()
	{
		earliest = 0;
	}
};

int64 RoundUp(int64 numToRound, int64 multiple)
{
	if (multiple == 0)
	{
		return numToRound;
	}

	int64 remainder = numToRound % multiple;
	if (remainder == 0)
	{
		return numToRound;
	}

	return (numToRound + multiple - remainder);
}

static int64	Solve_1(std::vector<std::string> input)
{
	int64						answer = 0;
	Schedule					schedule;
	std::vector<std::string>	parts;

	Remove(input[0], ",");
	schedule.earliest = std::stoi(input[0]);
	Split(parts, input[1], ",");

	for (int64 i = 0; i < parts.size(); i++)
	{
		if (parts[i] != "x")
		{
			schedule.timestamps.push_back(std::stoi(parts[i]));
		}
	}

	int64		index = 0;
	int64		highest = INT_MAX;

	for (int64 i = 0; i < schedule.timestamps.size(); i++)
	{
		int64	id = schedule.timestamps[i];
		
		int64	total = 0;
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

static int64	Solve_2(std::vector<std::string> input)
{
	int64						answer = 0;
	Schedule					schedule;
	std::vector<std::string>	parts;

	Remove(input[0], ",");
	Split(parts, input[1], ",");

	for (int64 i = 0; i < parts.size(); i++)
	{
		if (parts[i] != "x")
		{
			schedule.timestamps.push_back(std::stoi(parts[i]));
			schedule.offsets.push_back(i);
		}
	}

	int64		searchIndex = 1;
	int64		step = schedule.timestamps[0];
	int64		t = step;

	while (t < INT64_MAX)
	{
		int64	i = 0;
		bool	success = true;

		for (i = 0; i <= searchIndex; i++)
		{
			if ( (t + schedule.offsets[i]) % schedule.timestamps[i] != 0)
			{
				success = false;
				break;
			}
		}

		if (
			(success) && 
			(searchIndex == schedule.timestamps.size() - 1)
		)
		{
			answer = t;
			break;
		}

		if (success)
		{
			step *= schedule.timestamps[searchIndex];
			searchIndex++;
		}

		t += step;
	}

	printf("Answer: %lld\n", answer);

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
	assert(Solve_2(
		{
			"1",
			"17,x,13,19"
		}
	) == 3417);
	Solve_2(GetStrInput("inputs/Day13.txt"));
}