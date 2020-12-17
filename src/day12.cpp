//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "Day12.h"

#define M_PI       3.14159265358979323846   // pi

//
//	--- Day 12: Rain Risk ---
//
//	Your ferry made decent progress toward the island, but the storm
//	came in faster than anyone expected. The ferry needs to take 
//	evasive actions!
//
//	Unfortunately, the ship's navigation computer seems to be 
//	malfunctioning; rather than giving a route directly to safety, it 
//	produced extremely circuitous instructions. When the captain uses 
//	the PA system to ask if anyone can help, you quickly volunteer.
//
//	The navigation instructions (your puzzle input) consists of a 
//	sequence of single - character actions paired with integer input 
//	values. After staring at them for a few minutes, you work out what 
//	they probably mean:
//
//	Action N means to move north by the given value.
//	Action S means to move south by the given value.
//	Action E means to move east by the given value.
//	Action W means to move west by the given value.
//	Action L means to turn left the given number of degrees.
//	Action R means to turn right the given number of degrees.
//	Action F means to move forward by the given value in the direction the ship is currently facing.
//	
//	The ship starts by facing east. Only the L and R actions change the direction 
//	the ship is facing. (That is, if the ship is facing east and the next instruction
//	is N10, the ship would move north 10 units, but would still move east if the following action were F.)
//
//	For example:
//
//	F10
//	N3
//	F7
//	R90
//	F11
//
//	These instructions would be handled as follows :
//
//	F10 would move the ship 10 units east (because the ship starts by facing east) to east 10, north 0.
//	N3 would move the ship 3 units north to east 10, north 3.
//	F7 would move the ship another 7 units east(because the ship is still facing east) to east 17, north 3.
//	R90 would cause the ship to turn right by 90 degrees and face south; it remains at east 17, north 3.
//	F11 would move the ship 11 units south to east 17, south 8.
//	At the end of these instructions, the ship's Manhattan distance (sum of the absolute values of its east/west position and its north/south position) from its starting position is 17 + 8 = 25.
//
//	Figure out where the navigation instructions lead. What is the Manhattan distance between that location and the ship's starting position?

enum class ActionType : uint8
{
	North,
	South,
	East,
	West,
	Left,
	Right,
	Forward
};

enum class Direction : uint8
{
	North,
	South,
	East,
	West
};

struct Ship
{
	int32			x;
	int32			y;
	Direction		direction;
	float			angle;
	bool			bIsPart2;

	Ship(int32 startX, int32 startY, bool bPart2 = false)
	{
		x = startX;
		y = startY;
		direction = Direction::East;
		angle = 90.0f;
		bIsPart2 = bPart2;
	}

	float			ConstrainAngle(float value)
	{
		value = fmod(value, 360);
		if (value < 0)
		{
			value += 360;
		}
		return value;
	}

	Direction		AngleToDirection(float value)
	{
		angle = ConstrainAngle(angle + value);

		if			(angle == 0.0f)
		{
			direction = Direction::North;
		}
		else if		(angle == 90.0f)
		{
			direction = Direction::East;
		}
		else if		(angle == 180.0f)
		{
			direction = Direction::South;
		}
		else if		(angle == 270.0f)
		{
			direction = Direction::West;
		}

		return direction;
	}

	void			Move(int32 dx, int32 dy)
	{
		x += dx;
		y += dy;
	}

	void			MoveForward(int32 value)
	{
		if (direction == Direction::North)
		{
			y += value;
		}
		else if (direction == Direction::East)
		{
			x += value;
		}
		else if (direction == Direction::South)
		{
			y -= value;
		}
		else if (direction == Direction::West)
		{
			x -= value;
		}
	}

	void			Turn(float value)
	{
		direction = AngleToDirection(value);
	}

	void			Parse(const std::string& s, int32 wdx = 0, int32 wdy = 0)
	{
		char		action = s[0];
		int32		value = std::stoi(s.substr(1, s.size()));

		switch (action)
		{
			case 'N': { if (bIsPart2) { break; } Move(0, value); } break;
			case 'S': { if (bIsPart2) { break; } Move(0, -value); } break;
			case 'E': { if (bIsPart2) { break; } Move(value, 0); } break;
			case 'W': { if (bIsPart2) { break; } Move(-value, 0); } break;
			case 'L': { if (bIsPart2) { break; } Turn(-value); } break;
			case 'R': { if (bIsPart2) { break; } Turn(value); } break;
			case 'F': 
				{ 
					if (bIsPart2)
					{
						int32 num = value;
						while (num > 0)
						{
							Move(wdx, wdy);
							num--;
						}
					}
					else
					{
						MoveForward(value);
					}
				} 
				break;
			default:
				{
				}
				break;
		}
	}
};

struct Waypoint
{
	int32			x;
	int32			y;

	Waypoint(int32 startX, int32 startY)
	{
		x = startX;
		y = startY;
	}

	void			Move(int32 dx, int32 dy)
	{
		x += dx;
		y += dy;
	}

	void			Parse(const std::string& s, Ship& ship)
	{
		char		action = s[0];
		int32		value = std::stoi(s.substr(1, s.size()));

		switch (action)
		{
			case 'N': { Move(0, +value); } break;
			case 'S': { Move(0, -value); } break;
			case 'E': { Move(+value, 0); } break;
			case 'W': { Move(-value, 0); } break;
			case 'L': { RotatePoint(x, y, 0, 0, -value); } break;
			case 'R': { RotatePoint(x, y, 0, 0, +value); } break;
			case 'F': 
				{
				} 
				break;
			default:
				{
				}
				break;
		}
	}

	void RotatePoint(int32& px, int32& py, float pivotX, float pivotY, float angle)
	{
		float s = sin(-angle * M_PI / 180);
		float c = cos(-angle * M_PI / 180);

		// Translate point back to origin:
		px -= pivotX;
		py -= pivotY;

		// Rotate point
		float xnew = (px * c) - (py * s);
		float ynew = (px * s) + (py * c);

		// Translate point back:
		px = xnew + pivotX;
		py = ynew + pivotY;
	}
};

float			ManhattanDistance(const int32 x1, const int32 x2, const int32 y1, const int32 y2)
{
	int32	x_dif = x2 - x1;
	int32	y_dif = y2 - y1;

	if (x_dif < 0)
	{
		x_dif = -x_dif;
	}

	if (y_dif < 0)
	{
		y_dif = -y_dif;
	}

	return (x_dif + y_dif);
}

static int32	Solve_1(std::vector<std::string> input)
{
	Ship		ship(0, 0);
	int32		answer = 0;

	for (size_t i = 0; i < input.size(); i++)
	{
		ship.Parse(input[i]);
	}

	answer = ManhattanDistance(0, 0, ship.x, ship.y);

	printf("Answer: %d\n", answer);

	return answer;
}

static int32	Solve_2(std::vector<std::string> input)
{
	Ship		ship(0, 0, true);
	Waypoint	waypoint(10, 1);
	int32		answer = 0;

	for (size_t i = 0; i < input.size(); i++)
	{
		ship.Parse(input[i], waypoint.x, waypoint.y);
		waypoint.Parse(input[i], ship);
	}

	answer = ManhattanDistance(0, 0, ship.x, ship.y);

	printf("Answer: %d\n", answer);

	return answer;
}

void Day12::Part1()
{
	assert(Solve_1(
		{
			"F10",
			"N3",
			"F7",
			"R90",
			"F11"
		}
	) == 25);
	Solve_1(GetStrInput("inputs/Day12.txt"));
}

void Day12::Part2()
{
	assert(Solve_2(
		{
			"F10",
			"N3",
			"F7",
			"R90",
			"F11"
		}
	) == 286);
	Solve_2(GetStrInput("inputs/Day12.txt"));
}