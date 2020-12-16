//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "Day11.h"

enum class SeatType : uint8
{
	Invalid,
	Floor,
	Empty,
	Taken
};

struct Seat
{
	SeatType type;
	SeatType pendingType;

	Seat(SeatType newType)
	{
		type = newType;
		pendingType = SeatType::Invalid;
	}
};

struct Airport
{
	std::vector<Seat>		seats;
	int32					width;
	int32					height;

	Airport(int32 newWidth, int32 newHeight)
	{
		width = newWidth;
		height = newHeight;
		seats.reserve(width * height);
	}

	void					TakeYourSeats()
	{
		//	for (int32 i = 0; i < seats.size(); i++)
		//	{
		//		if (seats[i].type == SeatType::Empty)
		//		{
		//			seats[i].type = SeatType::Taken;
		//		}
		//	}
		for (size_t i = 0; i < seats.size(); i++)
		{
			if (seats[i].pendingType != SeatType::Invalid)
			{
				seats[i].type = seats[i].pendingType;
				seats[i].pendingType = SeatType::Invalid;
			}
		}
	}

	void					Parse(std::string s)
	{
		for (size_t i = 0; i < s.size(); i++)
		{
			if		(s[i] == '.')
			{
				seats.push_back(Seat(SeatType::Floor));
			}
			else if	(s[i] == 'L')
			{
				seats.push_back(Seat(SeatType::Empty));
			}
			else if	(s[i] == '#')
			{
				seats.push_back(Seat(SeatType::Taken));
			}
		}
	}

	bool					UpdateOccupancy()
	{
		bool bChanged = 0;

		for (int32 x = 0; x < width; x++)
		{
			for (int32 y = 0; y < height; y++)
			{
				int32		num = 0;
				SeatType	current = GetSeatType(x, y);

				if (IsSeatTaken(x + 1, y))		{ num++; }	// Right
				if (IsSeatTaken(x - 1, y))		{ num++; }	// Left
				if (IsSeatTaken(x, y + 1))		{ num++; }	// Up
				if (IsSeatTaken(x, y - 1))		{ num++; }	// Down
				if (IsSeatTaken(x + 1, y - 1))	{ num++; }	// T-Right
				if (IsSeatTaken(x - 1, y - 1))	{ num++; }	// T-Left
				if (IsSeatTaken(x + 1, y + 1))	{ num++; }	// B-Left
				if (IsSeatTaken(x - 1, y + 1))	{ num++; }	// B-Right

				if (current == SeatType::Empty && num == 0)
				{
					bChanged = true;
					SetSeatPendingType(x, y, SeatType::Taken);
				}
				else
				{
					if (current == SeatType::Taken && num >= 4)
					{
						bChanged = true;
						SetSeatPendingType(x, y, SeatType::Empty);
					}
				}
			}
		}

		TakeYourSeats();

		return bChanged;
	}

	const bool				IsSeatTaken(int32 x, int32 y) const
	{
		if (x >= 0 && y >= 0 && x < width && y < height)
		{
			return (GetSeatType(x, y) == SeatType::Taken);
		}
		else
		{
			return false;
		}
	}

	const void				SetSeatPendingType(int32 x, int32 y, SeatType seatType)
	{
		assert(x >= 0 && y >= 0 && x < width && y < height);
		seats[width * y + x].pendingType = seatType;
	}

	const SeatType			GetSeatType(int32 x, int32 y) const
	{
		return seats[width * y + x].type;
	}
};

static int32 Solve_1(std::vector<std::string> input)
{
	int32		answer = 0;
	Airport		airport((int32)input[0].size(), (int32)input.size());
	bool		bDebug = false;

	for (size_t i = 0; i < input.size(); i++)
	{
		airport.Parse(input[i]);
	}

	do 
	{
		if (!bDebug)
		{
			continue;
		}

		int x = 0;
		for (size_t i = 0; i < airport.seats.size(); i++)
		{
			switch (airport.seats[i].type)
			{
				default:
				case SeatType::Invalid:
					{

					}
					break;
				case SeatType::Floor:
					{
						printf(".");
					}
					break;
				case SeatType::Empty:
					{
						printf("L");
					}
					break;
				case SeatType::Taken:
					{
						printf("#");
					}
					break;
			}
			
			x++;
			if (x >= airport.width)
			{
				printf("\n");
				x = 0;
			}
		}

		printf("\n");
		printf("\n");
		printf("\n");
	}
	while (airport.UpdateOccupancy());

	
	for (size_t i = 0; i < airport.seats.size(); i++)
	{
		if (airport.seats[i].type == SeatType::Taken)
		{
			answer++;
		}
	}

	printf("Answer: %d\n", answer);

	return answer;
}

static int32 Solve_2(std::vector<std::string> input)
{
	int32 answer = 0;

	printf("Answer: %d\n", answer);

	return answer;
}

void Day11::Part1()
{
	assert(Solve_1(
		{
			"L.LL.LL.LL",
			"LLLLLLL.LL",
			"L.L.L..L..",
			"LLLL.LL.LL",
			"L.LL.LL.LL",
			"L.LLLLL.LL",
			"..L.L.....",
			"LLLLLLLLLL",
			"L.LLLLLL.L",
			"L.LLLLL.LL"
		}
	) == 37);
	Solve_1(GetStrInput("inputs/Day11.txt"));
}

void Day11::Part2()
{
	assert(Solve_2(
		{
			"L.LL.LL.LL",
			"LLLLLLL.LL",
			"L.L.L..L..",
			"LLLL.LL.LL",
			"L.LL.LL.LL",
			"L.LLLLL.LL",
			"..L.L.....",
			"LLLLLLLLLL",
			"L.LLLLLL.L",
			"L.LLLLL.LL"
		}
	) == 8);
	Solve_2(GetStrInput("inputs/Day11.txt"));
}