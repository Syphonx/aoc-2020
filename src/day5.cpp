//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "day5.h"

//	--- Day 5: Binary Boarding ---
//	
//	You board your plane only to discover a new problem: you dropped your 
//	boarding pass! You aren't sure which seat is yours, and all of the flight 
//	attendants are busy with the flood of people that suddenly made it through
//	passport control.
//	
//	You write a quick program to use your phone's camera to scan all of the
//	nearby boarding passes (your puzzle input); perhaps you can find your seat
//	through process of elimination.
//	
//	Instead of zones or groups, this airline uses binary space partitioning to s
//	eat people. A seat might be specified like FBFBBFFRLR, where F means 
//	"front", B means "back", L means "left", and R means "right".
//	
//	The first 7 characters will either be F or B; these specify exactly one of
//	the 128 rows on the plane (numbered 0 through 127). Each letter tells you 
//	which half of a region the given seat is in. Start with the whole list of rows; 
//	the first letter indicates whether the seat is in the front (0 through 63) or 
//	the back (64 through 127). The next letter indicates which half of that region
//	the seat is in, and so on until you're left with exactly one row.
//	
//	For example, consider just the first seven characters of FBFBBFFRLR:
//	
//	Start by considering the whole range, rows 0 through 127.
//	F means to take the lower half, keeping rows 0 through 63.
//	B means to take the upper half, keeping rows 32 through 63.
//	F means to take the lower half, keeping rows 32 through 47.
//	B means to take the upper half, keeping rows 40 through 47.
//	B keeps rows 44 through 47.
//	F keeps rows 44 through 45.
//	The final F keeps the lower of the two, row 44.
//	The last three characters will be either L or R; these specify exactly one of 
//	the 8 columns of seats on the plane (numbered 0 through 7). The same process as
//	above proceeds again, this time with only three steps. L means to keep the lower
//	half, while R means to keep the upper half.
//	
//	For example, consider just the last 3 characters of FBFBBFFRLR:
//	
//	Start by considering the whole range, columns 0 through 7.
//	R means to take the upper half, keeping columns 4 through 7.
//	L means to take the lower half, keeping columns 4 through 5.
//	The final R keeps the upper of the two, column 5.
//	So, decoding FBFBBFFRLR reveals that it is the seat at row 44, column 5.
//	
//	Every seat also has a unique seat ID: multiply the row by 8, then add the column. 
//	In this example, the seat has ID 44 * 8 + 5 = 357.
//	
//	Here are some other boarding passes:
//	
//	BFFFBBFRRR: row 70, column 7, seat ID 567.
//	FFFBBBFRRR: row 14, column 7, seat ID 119.
//	BBFFBBFRLL: row 102, column 4, seat ID 820.
//	As a sanity check, look through your list of boarding passes. What is the highest 
//	seat ID on a boarding pass?
//

struct BoardingPass
{
	int32	Row;
	int32	Column;

	BoardingPass()
	{
		Row = 127;
		Column = 7;
	}

	const int16 GetID() const
	{
		return Row * 8 + Column;
	}
};

static int32 Solve_1(const std::vector<std::string> input)
{
	int32	index;
	int32	result = 0;

	for (index = 0; index < input.size(); index++)
	{
		int32				i = 0;
		BoardingPass		pass;
		int32				lower = 0;
		int32				upper = 127;
		const std::string&	data = input[i];
		char				letter = ' ';

		while (i < data.size())
		{
			letter = data[i];

			int32		diff = (upper - lower);
			int32		delta = std::ceil((diff + 0.5f) / 2);

			if			(letter == 'F')
			{
				upper = upper - delta;
			}
			else if		(letter == 'B')
			{
				lower = lower + delta;
			}

			if (i == 8)
			{
				pass.Row = min(lower, upper);
				lower = 0;
				upper = 7;
				diff = (upper - lower);
				delta = std::ceil((diff + 0.5f) / 2);
			}

			if			(letter == 'L')
			{
				lower = lower + delta;
			}
			else if		(letter == 'R')
			{
				upper = upper - delta;
			}

			if (i == 10)
			{
				pass.Column = max(lower, upper);
			}

			i++;
		}

		printf("ID: %d\n", pass.GetID());
		result = max(result, pass.GetID());
	}

	return result;
}

static int32 Solve_2(const std::vector<std::string> input)
{
	return 0;
}

void Day5::Part1()
{
	assert(Solve_1({ "BFFFBBFRRR", "FFFBBBFRRR", "BBFFBBFRLL" }) == 820);
	//	Solve_1(GetStrInput("inputs/day1.txt"));
}

void Day5::Part2()
{
}