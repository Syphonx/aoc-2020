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
//	--- Part Two ---
//	Ding! The "fasten seat belt" signs have turned on. Time to find your seat.
//	
//	It's a completely full flight, so your seat should be the only missing boarding pass
//	in your list. However, there's a catch: some of the seats at the very front and back 
//	of the plane don't exist on this aircraft, so they'll be missing from your list as well.
//	
//	Your seat wasn't at the very front or back, though; the seats with IDs +1 and -1 from 
//	yours will be in your list.
//	
//	What is the ID of your seat?
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
	int32			index;
	int32			result = 0;
	BoardingPass	pass;

	for (index = 0; index < input.size(); index++)
	{
		int32				i = 0;
		int32				L = 0;
		int32				R = 127;
		const std::string&	data = input[index];
		char				letter = ' ';

		while (i < data.size())
		{
			letter = data[i];

			int32		diff = (R - L);
			int32		delta = (int32)std::ceil((diff + 0.5f) / 2);
			
			if (i == 6)
			{
				pass.Row = min(L, R);
				L = 0;
				R = 7;
			}
			else
			{
				if			(letter == 'F')
				{
					R -= delta;
				}
				else if		(letter == 'B')
				{
					L += delta;
				}
			}

			if			(letter == 'L')
			{
				R -= delta;
			}
			else if		(letter == 'R')
			{
				L += delta;
			}			

			if (i == 9)
			{
				pass.Column = max(L, R);
			}

			i++;
		}

		result = max(result, pass.GetID());
	}
	
	printf("ID: %d\n", result);
	return result;
}

static int32 Solve_2(const std::vector<std::string> input)
{
	int32				index;
	BoardingPass		pass;
	std::vector<int32>	seats;

	for (index = 0; index < input.size(); index++)
	{
		int32				i = 0;
		int32				L = 0;
		int32				R = 127;
		const std::string&	data = input[index];
		char				letter = ' ';

		while (i < data.size())
		{
			letter = data[i];

			int32		diff = (R - L);
			int32		delta = (int32)std::ceil((diff + 0.5f) / 2);
			
			if (i == 6)
			{
				pass.Row = min(L, R);
				L = 0;
				R = 7;
			}
			else
			{
				if			(letter == 'F')
				{
					R -= delta;
				}
				else if		(letter == 'B')
				{
					L += delta;
				}
			}

			if			(letter == 'L')
			{
				R -= delta;
			}
			else if		(letter == 'R')
			{
				L += delta;
			}			

			if (i == 9)
			{
				pass.Column = max(L, R);
				seats.push_back(pass.GetID());
			}

			i++;
		}
	}

	// Partial solution, answer was 610 but my data that solved #1 fine didn't work so :shrug:
	int32 result = 0;
	std::sort(seats.begin(), seats.end(), [](const int32& a, const int32& b) { return a < b; });
	for (const int32 seat : seats)
	{
		if (result != 0 && (seat - result) != 1)
		{
			std::cout << "MISSING ID BETWEEN " << seat << " AND " << result << "!!!" << std::endl;
		}
		result = seat;
	}

	printf("Seat: (%d)\n", result);

	return 1;
}

void Day5::Part1()
{
	assert(Solve_1({ "FBFBBFFRLR" }) == 357);
	assert(Solve_1({ "BFFFBBFRRR", "FFFBBBFRRR", "BBFFBBFRLL" }) == 820);
	Solve_1(GetStrInput("inputs/day5.txt"));
}

void Day5::Part2()
{
	Solve_2(GetStrInput("inputs/day5.txt"));
}