//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "day2.h"

//	--- Day 2: Password Philosophy ---
//	
//	Your flight departs in a few days from the coastal airport; the easiest way down to the coast 
//	from here is via toboggan.
//	
//	The shopkeeper at the North Pole Toboggan Rental Shop is having a bad day. 
//	"Something's wrong with our computers; we can't log in!" You ask if you can take a look.
//	
//	Their password database seems to be a little corrupted: some of the passwords wouldn't have 
//	been allowed by the Official Toboggan Corporate Policy that was in effect when they were chosen.
//	
//	To try to debug the problem, they have created a list (your puzzle input) of passwords 
//	(according to the corrupted database) and the corporate policy when that password was set.
//	
//	For example, suppose you have the following list:
//	
//	1-3 a: abcde
//	1-3 b: cdefg
//	2-9 c: ccccccccc
//	Each line gives the password policy and then the password. The password policy indicates the 
//	lowest and highest number of times a given letter must appear for the password to be valid. 
//	For example, 1-3 a means that the password must contain a at least 1 time and at most 3 times.
//	
//	In the above example, 2 passwords are valid. The middle password, cdefg, is not; it contains 
//	no instances of b, but needs at least 1. The first and third passwords are valid: they contain 
//	one a or nine c, both within the limits of their respective policies.
//	
//	How many passwords are valid according to their policies?
//
// --- Part Two ---
// 
// While it appears you validated the passwords correctly, they don't seem to be what the Official
// Toboggan Corporate Authentication System is expecting.
// 
// The shopkeeper suddenly realizes that he just accidentally explained the password policy rules 
// from his old job at the sled rental place down the street! The Official Toboggan Corporate Policy actually works a little differently.
// 
// Each policy actually describes two positions in the password, where 1 means the first character, 
// 2 means the second character, and so on. (Be careful; Toboggan Corporate Policies have no concept 
// of "index zero"!) Exactly one of these positions must contain the given letter. Other occurrences 
// of the letter are irrelevant for the purposes of policy enforcement.
// 
// Given the same example list from above:
// 
// 1-3 a: abcde is valid: position 1 contains a and position 3 does not.
// 1-3 b: cdefg is invalid: neither position 1 nor position 3 contains b.
// 2-9 c: ccccccccc is invalid: both position 2 and position 9 contain c.
// How many passwords are valid according to the new interpretation of the policies?

struct PasswordPolicy
{
	uint16		Min;
	uint16		Max;
	char		Token;
	uint8		bValid : 1;

	PasswordPolicy()
	{
		Min = 0;
		Max = 0;
		Token = ' ';
		bValid = false;
	}

	void		Parse(std::string input, bool bNewPolicy = false)
	{
		std::vector<std::string>	parts;
		std::vector<std::string>	temp;
		parts.reserve(3);

		//	"1-3"
		//	"a:"
		//	"abcde"
		if (Split(parts, input, " "))
		{
			//	"1-3"
			if (Split(temp, parts[0], "-"))
			{
				Min = (uint16)std::stoi(temp[0]);
				Max = (uint16)std::stoi(temp[1]);
			}

			//	"a:"
			Token = parts[1][0];

			//	"abcde"
			const std::string	password = parts[2];

			if (bNewPolicy)
			{
				const int32	MinIdx = Min-1;
				const int32	MaxIdx = Max-1;

				if (MaxIdx < password.size())
				{
					if (
						(password[MinIdx] == Token && password[MaxIdx] != Token) ||
						(password[MaxIdx] == Token && password[MinIdx] != Token)
					)
					{
						bValid = true;
					}
				}
			}
			else
			{
				size_t			num = std::count(password.begin(), password.end(), Token);
				if (num >= Min && num <= Max)
				{
					bValid = true;
				}
			}
		}
	}
};

static int32 Solve_1(const std::vector<std::string> input)
{
	int32 numValid = 0;
	int32 numLines = (int32)input.size();
	std::vector<PasswordPolicy> policies;

	policies.resize(numLines);

	for (size_t i = 0; i < numLines; i++)
	{
		policies[i].Parse(input[i], false);

		if (policies[i].bValid)
		{
			numValid++;
		}
	}

	return numValid;
}

static int32 Solve_2(const std::vector<std::string> input)
{
	int32 numValid = 0;
	int32 numLines = (int32)input.size();
	std::vector<PasswordPolicy> policies;

	policies.resize(numLines);

	for (size_t i = 0; i < numLines; i++)
	{
		policies[i].Parse(input[i], true);

		if (policies[i].bValid)
		{
			numValid++;
		}
	}

	return numValid;
}

void Day2::Part1()
{
	assert(Solve_1({ "1-3 a: abcde", "1-3 b: cdefg", "2-9 c: ccccccccc" }) == 2);
	printf("Day 2: %d\n", Solve_1(GetStrInput("inputs/day2.txt")));
}

void Day2::Part2()
{
	assert(Solve_2({ "1-3 a: abcde", "1-3 b: cdefg", "2-9 c: ccccccccc" }) == 1);
	printf("Day 2: %d\n", Solve_2(GetStrInput("inputs/day2.txt")));
}