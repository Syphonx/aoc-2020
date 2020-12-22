//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "Day15.h"

static int32	Solve_1(std::vector<std::string> input)
{
	int32								answer = 0;
	std::vector<int32>					numbers;
	std::unordered_map<int32, int32>	occurances;
	std::vector<std::string>			parts;
	const int32							target = 2020;
	numbers.reserve(target);

	if (Split(parts, input[0], ","))
	{
		for (const auto& p : parts)
		{
			int32 value = std::stoi(p);
			numbers.push_back(value);
			occurances[value]++;
		}
	}

	// Start 1 past the total of starting numbers
	for (int32 i = numbers.size(); i < target; i++)
	{
		int32 last = numbers[i - 1];
		int32 occurance = 0;
		int32 speak = -1;

		// How many times has it occurred?
		if (occurances.find(last) != occurances.end())
		{
			occurance = occurances.at(last);
		}

		// More than once?
		if (occurance > 1)
		{
			// Speak the difference between both instances
			int32 start = -1;
			int32 end = -1;

			for (int32 j = i - 1; j >= 0; j--)
			{
				if (numbers[j] == last)
				{
					if (end == -1)
					{
						end = j;
					}
					else
					{
						start = j;
						break;
					}
				}
			}

			speak = end - start;
		}
		else if (occurance == 1)
		{
			// New? Speak 0
			speak = 0;
		}

		// When speaking, increment occurances
		if (speak != -1)
		{
			numbers.push_back(speak);
			occurances[speak]++;
		}
	}

	// Access 2020th result
	answer = numbers[target - 1];

	printf("Answer: %d\n", answer);

	return answer;
}

static int32	Solve_2(std::vector<std::string> input)
{
	int32								answer = 0;
	int32								index = 0;
	std::vector<int32>					numbers;
	std::unordered_map<int32, int32>	occurances;
	std::vector<std::string>			parts;
	const int32							target = 30000000;

	numbers.resize(target);
	std::fill(numbers.begin(), numbers.end(), 0);
	
	if (Split(parts, input[0], ","))
	{
		for (const auto& p : parts)
		{
			int32 value = std::stoi(p);
			numbers[index] = value;
			occurances[value] = index;
			index++;
		}
	}
	parts.clear();
	occurances.erase(numbers[index-1]);

	// Start 1 past the total of starting numbers
	while (index < target)
	{
		int32	last = numbers[index - 1];
		int32	occurance = -1;

		// How many times has it occurred?
		if (occurances.find(last) != occurances.end())
		{
			// Speak the difference between both instances
			int32 speak = index - occurances[last] - 1;
			numbers[index] = speak;
			occurances[last] = index - 1;
		}
		else
		{
			numbers[index] = 0;
			occurances[last] = index - 1;
		}

		index++;
	}

	// Access 30000000th result
	answer = numbers[target - 1];

	printf("Answer: %d\n", answer);

	return answer;
}

void Day15::Part1()
{
	//	assert(Solve_1(
	//		{
	//			"0,3,6"
	//		}
	//	) == 436);
	//	Solve_1(GetStrInput("inputs/Day15.txt"));
}

void Day15::Part2()
{
	assert(Solve_2(
		{
			"0,3,6"
		}
	) == 175594);
	Solve_2(GetStrInput("inputs/Day15.txt"));
	system("pause");
}