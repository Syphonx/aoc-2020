//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "day6.h"

//	--- Day 6: Custom Customs ---
//
//	As your flight approaches the regional airport where you'll switch to a 
//	much larger plane, customs declaration forms are distributed to the passengers.
//	
//	The form asks a series of 26 yes-or-no questions marked a through z. All 
//	you need to do is identify the questions for which anyone in your group 
//	answers "yes". Since your group is just you, this doesn't take very long.
//	
//	However, the person sitting next to you seems to be experiencing a language 
//	barrier and asks if you can help. For each of the people in their group, you 
//	write down the questions for which they answer "yes", one per line. For example:
//	
//	abcx
//	abcy
//	abcz
//	In this group, there are 6 questions to which anyone answered "yes": a, b, c, x,
//	y, and z. (Duplicate answers to the same question don't count extra; each question 
//	counts at most once.)
//	
//	Another group asks for your help, then another, and eventually you've collected 
//	answers from every group on the plane (your puzzle input). Each group's answers are 
//	separated by a blank line, and within each group, each person's answers are on a 
//	single line. For example:
//	
//	abc
//	
//	a
//	b
//	c
//	
//	ab
//	ac
//	
//	a
//	a
//	a
//	a
//	
//	b
//	This list represents answers from five groups:
//	
//	The first group contains one person who answered "yes" to 3 questions: a, b, and c.
//	The second group contains three people; combined, they answered "yes" to 3 questions: a, b, and c.
//	The third group contains two people; combined, they answered "yes" to 3 questions: a, b, and c.
//	The fourth group contains four people; combined, they answered "yes" to only 1 question, a.
//	The last group contains one person who answered "yes" to only 1 question, b.
//	In this example, the sum of these counts is 3 + 3 + 3 + 1 + 1 = 11.
//	
//	For each group, count the number of questions to which anyone answered "yes". What is the sum of those counts?
//
//	--- Part Two ---
//	
//	As you finish the last group's customs declaration, you notice that you 
//	misread one word in the instructions:
//	
//	You don't need to identify the questions to which anyone answered "yes"; 
//	you need to identify the questions to which everyone answered "yes"!
//	
//	Using the same example as above:
//	
//	abc
//	
//	a
//	b
//	c
//	
//	ab
//	ac
//	
//	a
//	a
//	a
//	a
//	
//	b
//	This list represents answers from five groups:
//	
//	In the first group, everyone (all 1 person) answered "yes" to 3 questions: a, b, and c.
//	In the second group, there is no question to which everyone answered "yes".
//	In the third group, everyone answered yes to only 1 question, a. Since some people did not answer "yes" to b or c, they don't count.
//	In the fourth group, everyone answered yes to only 1 question, a.
//	In the fifth group, everyone (all 1 person) answered "yes" to 1 question, b.
//	In this example, the sum of these counts is 3 + 0 + 1 + 1 + 1 = 6.
//	
//	For each group, count the number of questions to which everyone answered "yes". What is the sum of those counts?
//

static int32 Solve_1(const std::vector<std::string> input)
{
	int32						answer = 0;
	std::unordered_set<char>	form;

	for (const auto& line : input)
	{
		if (line.empty())
		{
			answer += (int32)form.size();
			form.clear();
		}
		else
		{
			for (const auto& ch : line)
			{
				form.insert(ch);
			}
		}
	}
	answer += (int32)form.size();

	printf("Sum: %d\n", answer);

	return answer;
}

static int32 Solve_2(const std::vector<std::string> input)
{
	std::map<char, int32>	form;
	int32					answer = 0;
	int32					person = 0;
	int32					questions = 0;

	//		p1	p2	p3
	//	q1	x
	//	q2	x
	//	q3	x
	
	//		p1	p2	p3
	//	q1	x
	//	q2		x	
	//	q3			x
	
	//		p1	p2	p3
	//	q1	x	x
	//	q2	x		
	//	q3		x	

	for (const auto& line : input)
	{
		if (line.empty())
		{
			for (const auto& kv : form)
			{
				if (kv.second == person)
				{
					answer++;
				}
			}
			person = 0;
			form.clear();
		}
		else
		{
			for (const auto& ch : line)
			{
				const auto& ret = form.insert(std::pair<char, int32>(ch, 1));
				if (!ret.second)
				{
					ret.first->second++;
				}
			}
			person++;
		}
	}

	for (const auto& kv : form)
	{
		if (kv.second == person)
		{
			answer++;
		}
	}

	printf("Sum: %d\n", answer);

	return answer;
}

void Day6::Part1()
{
	assert(Solve_1({
		"abc",
		"",
		"a",
		"b",
		"c",
		"",
		"ab",
		"ac",
		"",
		"a",
		"a",
		"a",
		"a",
		"",
		"b"
		   }) == 11);
	Solve_1(GetStrInput("inputs/day6.txt"));
}

void Day6::Part2()
{
	assert(Solve_2({
		"abc",
		"",
		"a",
		"b",
		"c",
		"",
		"ab",
		"ac",
		"",
		"a",
		"a",
		"a",
		"a",
		"",
		"b"
		   }) == 6);
	Solve_2(GetStrInput("inputs/day6.txt"));
}