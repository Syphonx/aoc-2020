//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "Day16.h"

using namespace std;

struct FieldRange
{
	array<int32, 2>		Lower = { 0, 0 };
	array<int32, 2>		Upper = { 0, 0 };

	void Parse(string ruleA, string ruleB)
	{
		int32	colonA = ruleA.find('-');
		int32	colonB = ruleB.find('-');

		Lower[0] = std::stoi(ruleA.substr(0, colonA));
		Upper[0] = std::stoi(ruleA.substr(colonA + 1));

		Lower[1] = std::stoi(ruleB.substr(0, colonB));
		Upper[1] = std::stoi(ruleB.substr(colonB + 1));
	}

	bool InRange(int32 number) const
	{
		bool bInRange = false;

		if (
			(number >= Lower[0] && number <= Upper[0]) ||
			(number >= Lower[1] && number <= Upper[1])
		)
		{
			bInRange = true;
		}

		return bInRange;
	}
};

struct Rule
{
	string			Key;
	FieldRange		Range;

	Rule()
	{
	}

	Rule(string NewKey, FieldRange& NewRange)
	{
		Key = NewKey;
		Range = std::move(NewRange);
	}

	bool IsMatch(int32 number) const
	{
		return Range.InRange(number);
	}
};

struct Ticket
{
	vector<int32>	Numbers;
	uint8			bIsValid : 1;

	Ticket()
	{
	}

	Ticket(string input)
	{
		vector<string> parts;
		if (Split(parts, input, ","))
		{
			for (auto& r : parts)
			{
				Numbers.push_back(stoi(r));
			}
		}
	}

	int32 GetScanningError(const vector<Rule>& rules) const
	{
		int32 errorRate = 0;

		for (const int32 number : Numbers)
		{
			bool bMatch = false;
			for (const auto& rule : rules)
			{
				if (rule.IsMatch(number))
				{
					bMatch = true;
					break;
				}
			}

			if (!bMatch)
			{
				errorRate += number;
			}
		}

		return errorRate;
	}
};

enum class ParseStage : uint8
{
	Rules,
	Ticket,
	Nearby
};

static int32	Solve_1(vector<string> input)
{
	int32				answer = 0;

	int32				scanningError = 0;
	vector<string>		parts;
	vector<string>		rangeParts;
	vector<Rule>		rules;
	vector<Ticket>		tickets;
	Ticket				myTicket;
	ParseStage			stage = ParseStage::Rules;

	for (const auto& line : input)
	{
		if (line == "")
		{
			stage = static_cast<ParseStage>(((int32)stage) + 1);
			continue;
		}

		switch (stage)
		{
			default:
			case ParseStage::Rules:
			{
				parts.clear();
				rangeParts.clear();

				if (Split(parts, line, ":"))
				{
					Trim(parts[0]);
					Remove(parts[0], " ");

					FieldRange ranges;
					if (Split(rangeParts, parts[1], "or"))
					{
						for (auto& r : rangeParts)
						{
							Trim(r);
							Remove(r, " ");
						}
						ranges.Parse(rangeParts[0], rangeParts[1]);
					}

					rules.push_back({ parts[0], ranges });
				}
			}
			break;

			case ParseStage::Ticket:
			{
				if (line.find("your") == -1)
				{
					myTicket = Ticket(line);
				}
			}
			break;
			
			case ParseStage::Nearby:
			{
				if (line.find("nearby") == -1)
				{
					tickets.emplace_back(Ticket(line));
				}
			}
			break;
		}
	}

	for (const auto& ticket : tickets)
	{
		scanningError += ticket.GetScanningError(rules);
	}
	answer = scanningError;

	printf("Answer: %d\n", answer);

	return answer;
}

static int32	Solve_2(vector<string> input)
{
	int32	answer = 0;

	printf("Answer: %d\n", answer);

	return answer;
}

void Day16::Part1()
{
	assert(Solve_1(
		{
			"class: 1-3 or 5-7",
			"row: 6-11 or 33-44",
			"seat: 13-40 or 45-50",
			"",
			"your ticket:",
			"7,1,14",
			"",
			"nearby tickets:",
			"7,3,47",
			"40,4,50",
			"55,2,20",
			"38,6,12"
		}
	) == 71);
	Solve_1(GetStrInput("inputs/Day16.txt"));
}

void Day16::Part2()
{
	assert(Solve_2(
		{
		}
	) == 0);
	Solve_2(GetStrInput("inputs/Day16.txt"));
}