//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "day1.h"
#include <assert.h>

//	--- Day 1: Report Repair ---
//	
//	After saving Christmas five years in a row, you've decided to take a vacation at a nice
//	resort on a tropical island. Surely, Christmas will go on without you.
//	
//	The tropical island has its own currency and is entirely cash-only. The gold coins used
//	there have a little picture of a starfish; the locals just call them stars. None of the 
//	currency exchanges seem to have heard of them, but somehow, you'll need to find fifty of 
//	these coins by the time you arrive so you can pay the deposit on your room.
//	
//	To save your vacation, you need to get all fifty stars by December 25th.
//	
//	Collect stars by solving puzzles. Two puzzles will be made available on each day in the 
//	Advent calendar; the second puzzle is unlocked when you complete the first. Each puzzle 
//	grants one star. Good luck!
//	
//	Before you leave, the Elves in accounting just need you to fix your expense report 
//	(your puzzle input); apparently, something isn't quite adding up.
//	
//	Specifically, they need you to find the two entries that sum to 2020 and then multiply those
//	two numbers together.
//	
//	For example, suppose your expense report contained the following:
//	
//	1721
//	979
//	366
//	299
//	675
//	1456
//	In this list, the two entries that sum to 2020 are 1721 and 299. Multiplying them together 
//	produces 1721 * 299 = 514579, so the correct answer is 514579.
//	
//	Of course, your expense report is much larger. Find the two entries that sum to 2020; what 
//	do you get if you multiply them together?
//	
//	--- Part Two ---
//	
//	The Elves in accounting are thankful for your help; one of them even offers you a starfish 
//	coin they had left over from a past vacation. They offer you a second one if you can find three numbers in your expense report that meet the same criteria.
//	
//	Using the above example again, the three entries that sum to 2020 are 979, 366, and 675. 
//	Multiplying them together produces the answer, 241861950.
//	
//	In your expense report, what is the product of the three entries that sum to 2020?

static int32_t Solve_1(const std::vector<int32_t> input)
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

static int32_t Solve_2(const std::vector<int32_t> input)
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
	Solve_1(GetIntInput("inputs/day1.txt"));
}

void Day1::Part2()
{
	assert(Solve_2({ 1721, 979, 366, 299, 675, 1456 }) == 241861950);
	Solve_2(GetIntInput("inputs/day1.txt"));
}