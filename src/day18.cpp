//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "Day18.h"

using namespace std;

struct Calculator
{
	vector<char>		operators;
	vector<int32>		numbers;
	array<int32, 64>	runlengths;
	int32				depth;

	int32 Parse(const std::string& input)
	{
		int32			answer = 0;
		depth = 0;
		runlengths.fill(0);

		for (int32 i = 0; i < input.size(); i++)
		{
			const char expression = input[i];

			if (expression == ' ')
			{
				continue;
			}

			bool closed = false;
			if (expression == '(')
			{
				depth++;
			}
			else
			{
				closed = (expression == ')');
			}

			if (std::isdigit(expression))
			{
				runlengths[depth]++;
				numbers.push_back((int32)expression - 48);
			}
			else
			{
				if (
					(expression == '+') ||
					(expression == '-') ||
					(expression == '*') ||
					(expression == '/')
					)
				{
					operators.push_back(expression);
				}
			}

			while (closed || (numbers.size() >= 2 && operators.size() >= 1))
			{
				int32 index = numbers.size() - runlengths[depth];
				int32 l = numbers[index];
				int32 r = numbers[index + 1];
				auto  iter = numbers.begin() + index;

				numbers.erase(iter, iter + 2);
				runlengths[depth]--;

				iter = numbers.begin() + index;

				switch (operators[index])
				{
					case '+':	numbers.insert(iter, l + r);	break;
					case '-':	numbers.insert(iter, l - r);	break;
					case '*':	numbers.insert(iter, l * r);	break;
					case '/':	numbers.insert(iter, l / r);	break;
					default:	break;
				}

				operators.erase(operators.begin() + index);

				if (runlengths[depth] < 2)
				{
					if (depth > 0)
					{
						runlengths[depth - 1]++;
						runlengths[depth]--;
						depth--;
					}
					else
					{
						break;
					}
				}
			}
		}

		answer = numbers.back(); numbers.pop_back();
		return	answer;
	}
};

static int32	Solve_1(vector<string> input)
{
	int32		answer = 0;
	Calculator	calc;

	for (const std::string& expression : input)
	{
		answer += calc.Parse(expression);
	}

	printf("Answer: %d\n", answer);

	return answer;
}

static int32	Solve_2(vector<string> input)
{
	int32 answer = 0;

	printf("Answer: %d\n", answer);

	return answer;
}

void Day18::Part1()
{
	//assert(Solve_1({ "1 + (2 * 3) + (4 * (5 + 6))" }) == 51);
	//assert(Solve_1({ "2 * 3 + (4 * 5)" }) == 26);
	//assert(Solve_1({ "5 + (8 * 3 + 9 + 3 * 4 * 3)" }) == 437);
	//assert(Solve_1({ "5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))" }) == 12240);
	assert(Solve_1({ "((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2" }) == 13632);

	Solve_1(GetStrInput("inputs/Day18.txt"));
}

void Day18::Part2()
{
	assert(Solve_2(
		{
			"1 + (2 * 3) + (4 * (5 + 6))"
		}
	) != 0);
	Solve_2(GetStrInput("inputs/Day18.txt"));
}