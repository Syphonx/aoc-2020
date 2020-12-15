//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "Day10.h"

struct Adapter
{
	int32					Joltage;
	int32					Diff;
	Adapter*				Next;
	std::stack<Adapter*>	Candidates;
	int32					NumCandidates;

	Adapter()
	{
		Joltage = 0;
		Diff = 0;
		Next = nullptr;
		NumCandidates = 0;
	}

	Adapter(int32 NewJoltage)
	{
		Joltage = NewJoltage;
		Diff = 0;
		Next = nullptr;
		NumCandidates = 0;
	}
};

static uint64 WalkTree(Adapter* current_adapter, uint64 num_cand)
{
	std::stack<Adapter*>	stack = current_adapter->Candidates;
	uint64					num = num_cand;

	while (!stack.empty())
	{
		Adapter* child = stack.top();
		num += WalkTree(child, child->Candidates.size()) + 1;
		stack.pop();
	}

	return num;
}

static int32 Solve_1(std::vector<int32> input)
{
	int32 answer = 0;

	std::sort(input.begin(), input.end(), [](const int32& a, const int32& b) { return a < b; });

	int32					num1diffs = 0;
	int32					num3diffs = 0;
	std::vector<Adapter>	adapters;
	adapters.resize(input.size() + 2);
	adapters[input.size() + 1].Joltage = *std::max_element(input.begin(), input.end()) + 3;

	for (size_t i = 0; i < input.size(); i++)
	{
		printf("%d ", input[i]);
		adapters[i + 1] = Adapter(input[i]);
	}

	for (size_t i = 0; i < adapters.size(); i++)
	{
		if (!adapters[i].Next)
		{
			for (size_t j = 0; j < adapters.size(); j++)
			{
				if (i == j || adapters[j].Next)
				{
					continue;
				}

				int32 diff = adapters[j].Joltage - adapters[i].Joltage;
				if (diff >= 1 && diff <= 3)
				{
					adapters[j].Diff = diff;
					adapters[i].Next = &adapters[j];
					if (diff == 1)
					{
						num1diffs++;
					}
					else
					{
						if (diff == 3)
						{
							num3diffs++;
						}
					}
					break;
				}
			}
		}
	}

	//	for (size_t i = 0; i < adapters.size(); i++)
	//	{
	//		for (size_t j = 0; j < adapters[i].Diff; j++)
	//		{
	//			printf("#");
	//		}
	//		printf("\n");
	//	}

	answer = num1diffs * num3diffs;
	printf("Answer: %d\n", answer);

	return answer;
}

static uint64 Solve_2(std::vector<int32> input)
{
	uint64 answer = 0;

	std::sort(input.begin(), input.end(), [](const int32& a, const int32& b) { return a < b; });

	std::vector<Adapter>	adapters;
	adapters.resize(input.size() + 2);
	adapters[input.size() + 1].Joltage = *std::max_element(input.begin(), input.end()) + 3;

	for (size_t i = 0; i < input.size(); i++)
	{
		adapters[i + 1] = Adapter(input[i]);
	}

	for (size_t i = 0; i < adapters.size(); i++)
	{
		if (!adapters[i].Next)
		{
			for (size_t j = 0; j < adapters.size(); j++)
			{
				if (i == j)
				{
					continue;
				}

				int32 diff = adapters[j].Joltage - adapters[i].Joltage;

				if (diff >= 1 && diff <= 3)
				{
					if (adapters[i].Next)
					{
						adapters[i].Candidates.push(&adapters[j]);
						adapters[i].NumCandidates = adapters[i].Candidates.size();
					}
					else
					{
						adapters[j].Diff = diff;
						adapters[i].Next = &adapters[j];
					}
				}
			}
		}
	}

	answer = 0;
	
	for (size_t i = 0; i < adapters.size(); i++)
	{
		Adapter* current_adapter = &adapters[i];
		answer += WalkTree(current_adapter, current_adapter->Candidates.size());
	}

	printf("Answer: %lld\n", answer);

	return answer;
}

void Day10::Part1()
{
	assert(Solve_1(
		{
			16,
			10,
			15,
			5,
			1,
			11,
			7,
			19,
			6,
			12,
			4
		}
	) == 35);
	Solve_1(GetIntInput("inputs/Day10.txt"));
}

void Day10::Part2()
{
	assert(Solve_2(
		{
			16,
			10,
			15,
			5,
			1,
			11,
			7,
			19,
			6,
			12,
			4
		}
	) == 8);
	Solve_2(GetIntInput("inputs/Day10.txt")); // 988872704
}