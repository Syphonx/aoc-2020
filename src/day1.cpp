//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "day1.h"
#include <assert.h>

int32_t Solve_1(const std::vector<int32_t> input)
{
	bool		bDone = false;
	int32_t		entry_1 = -1;
	int32_t		entry_2 = -1;
	for (size_t i = 0; i < input.size(); i++)
	{
		entry_1 = input[i];
		for (size_t j = i + 1; j < input.size(); j++)
		{
			entry_2 = input[j];
			if (entry_1 + entry_2 == 2020)
			{
				goto the_end;
			}
		}
	}
	the_end:

	printf("Day 1: %d * %d = %d\n", entry_1, entry_2, entry_1 * entry_2);
	return entry_1 * entry_2;
}

int32_t Solve_2(const std::vector<int32_t> input)
{	
	bool		bDone = false;
	int32_t		entry_1 = -1;
	int32_t		entry_2 = -1;
	int32_t		entry_3 = -1;
	for (size_t i = 0; i < input.size(); i++)
	{
		entry_1 = input[i];
		for (size_t j = i + 1; j < input.size(); j++)
		{
			entry_2 = input[j];
			for (size_t k = j + 1; k < input.size(); k++)
			{
				entry_3 = input[k];
				if (entry_1 + entry_2 + entry_3 == 2020)
				{
					goto the_end;
				}
			}
		}
	}
	the_end:

	printf("Day 1: %d * %d * %d = %d\n", entry_1, entry_2, entry_3, entry_1 * entry_2 * entry_3);
	return entry_1 * entry_2 * entry_3;
}

void Day1::Part1()
{
	assert(Solve_1({ 1721, 979, 366, 299, 675, 1456 }) == 514579);
	Solve_1(GetInput("inputs/day1.txt"));
}

void Day1::Part2()
{
	assert(Solve_2({ 1721, 979, 366, 299, 675, 1456 }) == 241861950);
	Solve_2(GetInput("inputs/day1.txt"));
}