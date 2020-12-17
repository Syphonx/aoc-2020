//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "Day11.h"

//	--- Day 11: Seating System ---
//
//	Your plane lands with plenty of time to spare.The final leg of your journey 
//	is a ferry that goes directly to the tropical island where you can finally start 
//	your vacation.As you reach the waiting area to board the ferry, you realize you're
//	so early, nobody else has even arrived yet!
//	
//	By modeling the process people use to choose(or abandon) their seat in the 
//	waiting area, you're pretty sure you can predict the best place to sit. You make 
//	a quick map of the seat layout (your puzzle input).
//	
//	The seat layout fits neatly on a grid.Each position is either floor(.), an empty 
//	seat(L), or an occupied seat(#).For example, the initial seat layout might look like
//	this :
//	
//		L.LL.LL.LL
//		LLLLLLL.LL
//		L.L.L..L..
//		LLLL.LL.LL
//		L.LL.LL.LL
//		L.LLLLL.LL
//		..L.L.....
//		LLLLLLLLLL
//		L.LLLLLL.L
//		L.LLLLL.LL
//
//	Now, you just need to model the people who will be arriving shortly.Fortunately, people are entirely predictable and always follow a simple set of rules.All decisions are based on the number of occupied seats adjacent to a given seat(one of the eight positions immediately up, down, left, right, or diagonal from the seat).The following rules are applied to every seat simultaneously :
//	
//	If a seat is empty(L) and there are no occupied seats adjacent to it, the seat
//	becomes occupied.
//	If a seat is occupied(#) and four or more seats adjacent to it are also occupied,
//	the seat becomes empty.
//	Otherwise, the seat's state does not change.
//	Floor(.) never changes; seats don't move, and nobody sits on the floor.
//	
//	After one round of these rules, every seat in the example layout becomes occupied :
//	
//	#.##.##.##
//	#######.##
//	#.#.#..#..
//	####.##.##
//	#.##.##.##
//	#.#####.##
//	..#.#.....
//	##########
//	#.######.#
//	#.#####.##
//
//	After a second round, the seats with four or more occupied adjacent seats become empty again :
//	
//	#.LL.L#.##
//	#LLLLLL.L#
//	L.L.L..L..
//	#LLL.LL.L#
//	#.LL.LL.LL
//	#.LLLL#.##
//	..L.L.....
//	#LLLLLLLL#
//	#.LLLLLL.L
//	#.#LLLL.##
//
//	This process continues for three more rounds :
//	
//	#.##.L#.##
//	#L###LL.L#
//	L.#.#..#..
//	#L##.##.L#
//	#.##.LL.LL
//	#.###L#.##
//	..#.#.....
//	#L######L#
//	#.LL###L.L
//	#.#L###.##
//	#.#L.L#.##
//	#LLL#LL.L#
//	L.L.L..#..
//	#LLL.##.L#
//	#.LL.LL.LL
//	#.LL#L#.##
//	..L.L.....
//	#L#LLLL#L#
//	#.LLLLLL.L
//	#.#L#L#.##
//	#.#L.L#.##
//	#LLL#LL.L#
//	L.#.L..#..
//	#L##.##.L#
//	#.#L.LL.LL
//	#.#L#L#.##
//	..L.L.....
//	#L#L##L#L#
//	#.LLLLLL.L
//	#.#L#L#.##
//
//	At this point, something interesting happens : the chaos stabilizes and further 
//	applications of these rules cause no seats to change state!Once people stop moving 
//	around, you count 37 occupied seats.
//	
//	Simulate your seating area by applying the seating rules repeatedly until no 
//	seats change state.How many seats end up occupied ?
//	
//	Your puzzle answer was 2126.
//	
//	The first half of this puzzle is complete!It provides one gold star : *
//	
//	--- Part Two ---
//
//	As soon as people start to arrive, you realize your mistake.People don't just 
//	care about adjacent seats - they care about the first seat they can see in each of 
//	those eight directions!
//	
//	Now, instead of considering just the eight immediately adjacent seats, consider 
//	the first seat in each of those eight directions.For example, the empty seat below
//	would see eight occupied seats :
//	
//	.......#.
//	...#.....
//	.#.......
//	.........
//	..#L....#
//	....#....
//	.........
//	#........
//	...#.....
//
//	The leftmost empty seat below would only see one empty seat, but cannot see any 
//	of the occupied ones :
//	
//	.............
//	.L.L.#.#.#.#.
//	.............
//	The empty seat below would see no occupied seats :
//	
//	.##.##.
//	#.#.#.#
//	##...##
//	...L...
//	##...##
//	#.#.#.#
//	.##.##.
//
//	Also, people seem to be more tolerant than you expected : it now takes five or
//	more visible occupied seats for an occupied seat to become 
//	empty(rather than four or more from the previous rules).The other rules still 
//	apply : empty seats that see no occupied seats become occupied, seats matching 
//	no rule don't change, and floor never changes.
//	
//	Given the same starting layout as above, these new rules cause the seating area
//	to shift around as follows :
//	
//	L.LL.LL.LL
//	LLLLLLL.LL
//	L.L.L..L..
//	LLLL.LL.LL
//	L.LL.LL.LL
//	L.LLLLL.LL
//	..L.L.....
//	LLLLLLLLLL
//	L.LLLLLL.L
//	L.LLLLL.LL
//
//	#.##.##.##
//	#######.##
//	#.#.#..#..
//	####.##.##
//	#.##.##.##
//	#.#####.##
//	..#.#.....
//	##########
//	#.######.#
//	#.#####.##
//
//	#.LL.LL.L#
//	#LLLLLL.LL
//	L.L.L..L..
//	LLLL.LL.LL
//	L.LL.LL.LL
//	L.LLLLL.LL
//	..L.L.....
//	LLLLLLLLL#
//	#.LLLLLL.L
//	#.LLLLL.L#
//
//	#.L#.##.L#
//	#L#####.LL
//	L.#.#..#..
//	##L#.##.##
//	#.##.#L.##
//	#.#####.#L
//	..#.#.....
//	LLL####LL#
//	#.L#####.L
//	#.L####.L#
//	#.L#.L#.L#
//
//	#LLLLLL.LL
//	L.L.L..#..
//	##LL.LL.L#
//	L.LL.LL.L#
//	#.LLLLL.LL
//	..L.L.....
//	LLLLLLLLL#
//	#.LLLLL#.L
//	#.L#LL#.L#
//	#.L#.L#.L#
//	#LLLLLL.LL
//
//	L.L.L..#..
//	##L#.#L.L#
//	L.L#.#L.L#
//	#.L####.LL
//	..#.#.....
//	LLL###LLL#
//	#.LLLLL#.L
//	#.L#LL#.L#
//	#.L#.L#.L#
//	#LLLLLL.LL
//	L.L.L..#..
//
//	##L#.#L.L#
//	L.L#.LL.L#
//	#.LLLL#.LL
//	..#.L.....
//	LLL###LLL#
//	#.LLLLL#.L
//	#.L#LL#.L#
//
//	Again, at this point, people stop shifting around and the seating area reaches
//	equilibrium. Once this occurs, you count 26 occupied seats.
//	
//	Given the new visibility method and the rule change for occupied seats becoming 
//	empty, once equilibrium is reached, how many seats end up occupied ?
//

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

	bool					InMap(int32 x, int32 y)
	{
		if (x >= 0 && y >= 0 && x < width && y < height)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool					IsSeat(int32 x, int32 y)
	{
		if (
			(GetSeatType(x, y) == SeatType::Taken) ||
			(GetSeatType(x, y) == SeatType::Empty)
		)
		{
			return true;
		}

		return false;
	}

	bool					CheckSightline(int32 x, int32 y, int32 dx, int32 dy)
	{
		bool	bTaken = false;
		x += dx;
		y += dy;

		while (InMap(x, y))
		{
			if (IsSeat(x, y))
			{
				if (IsSeatTaken(x, y))
				{
					bTaken = true;
				}
				break;
			}
			else
			{
				x += dx;
				y += dy;
			}
		}

		return bTaken;
	}

	bool					UpdateOccupancy2()
	{
		bool bChanged = 0;

		for (int32 x = 0; x < width; x++)
		{
			for (int32 y = 0; y < height; y++)
			{
				int32		num = 0;
				SeatType	current = GetSeatType(x, y);

				if (CheckSightline(x, y,  1,  0))	{ num++; }	// Right
				if (CheckSightline(x, y, -1,  0))	{ num++; }	// Left
				if (CheckSightline(x, y,  0,  1))	{ num++; }	// Up
				if (CheckSightline(x, y,  0, -1))	{ num++; }	// Down
				if (CheckSightline(x, y,  1, -1))	{ num++; }	// T-Right
				if (CheckSightline(x, y, -1, -1))	{ num++; }	// T-Left
				if (CheckSightline(x, y,  1,  1))	{ num++; }	// B-Left
				if (CheckSightline(x, y, -1,  1))	{ num++; }	// B-Right

				if (current == SeatType::Empty && num == 0)
				{
					bChanged = true;
					SetSeatPendingType(x, y, SeatType::Taken);
				}
				else
				{
					if (current == SeatType::Taken && num >= 5)
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
	while (airport.UpdateOccupancy2());

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
	) == 26);
	Solve_2(GetStrInput("inputs/Day11.txt"));
}