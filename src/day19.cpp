//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "Day19.h"

using namespace std;

struct Subrule
{
	Subrule()
	{
		subrules.reserve(4);
	}

	vector<int32> subrules;
};

struct Rule
{
	Rule()
		: index(-1)
		, hasToken(false)
		, token('x')
	{
	}

	Rule(int32 inIndex)
		: index(inIndex)
		, hasToken(false)
		, token('x')
	{
		subrules.reserve(4);
	}

	int32 index;
	bool hasToken;
	char token;
	vector<Subrule> subrules;
};

static uint64	Solve_1(vector<string> input)
{
	uint64 answer = 0;
	vector<Rule> rules;
	vector<string> messages;
	vector<string> ruleParts;
	vector<string> subRuleParts;
	vector<string> subRuleIndexParts;
	vector<string> indexParts;
	bool bParseMessages = false;

	for (const auto line : input)
	{
		if (line == "")
		{
			bParseMessages = true;
			break;
		}

		if (bParseMessages)
		{
			messages.push_back(line);
		}
		else
		{
			int32 index = rules.size();
			ruleParts.clear();

			// 1: 2 3 | 3 2 -> [1, 2 3 | 3 2]
			if (Split(ruleParts, line, ": "))
			{
				int32 ruleIndex = stoi(ruleParts[0]);
				rules.emplace_back(ruleIndex);

				if (ruleParts[0] == "a")
				{
					rules[index].hasToken = true;
					rules[index].token = 'a';
				}
				else if (ruleParts[0] == "b")
				{
					rules[index].hasToken = true;
					rules[index].token = 'b';
				}

				subRuleParts.clear();

				// 2 3 | 3 2 -> [ 2 3 , 3 2]
				if (Split(subRuleParts, ruleParts[1], " | "))
				{
					int32 subruleIndex = 0;
					rules[index].subrules.resize(subRuleParts.size());

					for (const auto& subrule : subRuleParts)
					{
						// 2 3 | 3 2 -> [[2, 3], [3, 2]]
						if (Split(subRuleIndexParts, subrule, " "))
						{
							for (const auto& subRuleIndex : subRuleParts)
							{
								rules[index].subrules[subruleIndex].subrules.push_back(stoi(subRuleIndex));
							}
						}

						subruleIndex++;
					}
				}
			}
		}
	}

	printf("Answer: %lld\n", answer);

	return answer;
}

static uint64	Solve_2(vector<string> input)
{
	uint64		answer = 0;

	printf("Answer: %lld\n", answer);

	return answer;
}

void Day19::Part1()
{
	assert(Solve_1(
		{
			"0: 4 1 5",
			"1: 2 3 | 3 2",
			"2: 4 4 | 5 5",
			"3: 4 5 | 5 4",
			"4: \"a\"",
			"5: \"b\"",
			"",
			"ababbb",
			"bababa",
			"abbbab",
			"aaabbb",
			"aaaabbb"
		}
	) == 51);

	// Solve_1(GetStrInput("inputs/Day19.txt"));
}

void Day19::Part2()
{
	//	assert(Solve_2({ "1 + (2 * 3) + (4 * (5 + 6))" }) == 51);
	//	Solve_2(GetStrInput("inputs/Day19.txt"));
}