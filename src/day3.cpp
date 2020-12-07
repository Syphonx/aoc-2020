//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "day3.h"

//	--- Day 3: Toboggan Trajectory ---
//	
//	With the toboggan login problems resolved, you set off toward the airport. 
//	While travel by toboggan might be easy, it's certainly not safe: there's very minimal 
//	steering and the area is covered in trees. You'll need to see which angles will take you 
//	near the fewest trees.
//	
//	Due to the local geology, trees in this area only grow on exact integer coordinates in a grid. 
//	You make a map (your puzzle input) of the open squares (.) and trees (#) you can see. For example:
//	
//	..##.......
//	#...#...#..
//	.#....#..#.
//	..#.#...#.#
//	.#...##..#.
//	..#.##.....
//	.#.#.#....#
//	.#........#
//	#.##...#...
//	#...##....#
//	.#..#...#.#
//	These aren't the only trees, though; due to something you read about once involving arboreal 
//	genetics and biome stability, the same pattern repeats to the right many times:
//	
//	..##.........##.........##.........##.........##.........##.......  --->
//	#...#...#..#...#...#..#...#...#..#...#...#..#...#...#..#...#...#..
//	.#....#..#..#....#..#..#....#..#..#....#..#..#....#..#..#....#..#.
//	..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#
//	.#...##..#..#...##..#..#...##..#..#...##..#..#...##..#..#...##..#.
//	..#.##.......#.##.......#.##.......#.##.......#.##.......#.##.....  --->
//	.#.#.#....#.#.#.#....#.#.#.#....#.#.#.#....#.#.#.#....#.#.#.#....#
//	.#........#.#........#.#........#.#........#.#........#.#........#
//	#.##...#...#.##...#...#.##...#...#.##...#...#.##...#...#.##...#...
//	#...##....##...##....##...##....##...##....##...##....##...##....#
//	.#..#...#.#.#..#...#.#.#..#...#.#.#..#...#.#.#..#...#.#.#..#...#.#  --->
//	You start on the open square (.) in the top-left corner and need to reach the bottom (below the
//	 bottom-most row on your map).
//	
//	The toboggan can only follow a few specific slopes (you opted for a cheaper model that prefers 
//	rational numbers); start by counting all the trees you would encounter for the slope right 3, down 1:
//	
//	From your starting position at the top-left, check the position that is right 3 and down 1. Then,
//	check the position that is right 3 and down 1 from there, and so on until you go past the bottom 
//	of the map.
//	
//	The locations you'd check in the above example are marked here with O where there was an open square
//	and X where there was a tree:
//	
//	..##.........##.........##.........##.........##.........##.......  --->
//	#..O#...#..#...#...#..#...#...#..#...#...#..#...#...#..#...#...#..
//	.#....X..#..#....#..#..#....#..#..#....#..#..#....#..#..#....#..#.
//	..#.#...#O#..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#
//	.#...##..#..X...##..#..#...##..#..#...##..#..#...##..#..#...##..#.
//	..#.##.......#.X#.......#.##.......#.##.......#.##.......#.##.....  --->
//	.#.#.#....#.#.#.#.O..#.#.#.#....#.#.#.#....#.#.#.#....#.#.#.#....#
//	.#........#.#........X.#........#.#........#.#........#.#........#
//	#.##...#...#.##...#...#.X#...#...#.##...#...#.##...#...#.##...#...
//	#...##....##...##....##...#X....##...##....##...##....##...##....#
//	.#..#...#.#.#..#...#.#.#..#...X.#.#..#...#.#.#..#...#.#.#..#...#.#  --->
//	In this example, traversing the map using this slope would cause you to encounter 7 trees.
//	
//	Starting at the top-left corner of your map and following a slope of right 3 and down 1, how many 
//	trees would you encounter?
//	
//	--- Part Two ---
//	
//	Time to check the rest of the slopes - you need to minimize the probability 
//	of a sudden arboreal stop, after all.
//	
//	Determine the number of trees you would encounter if, for each of the f
//	ollowing slopes, you start at the top-left corner and traverse the map all 
//	the way to the bottom:
//	
//	Right 1, down 1.
//	Right 3, down 1. (This is the slope you already checked.)
//	Right 5, down 1.
//	Right 7, down 1.
//	Right 1, down 2.
//	In the above example, these slopes would find 2, 7, 3, 4, and 2 tree(s) 
//	respectively; multiplied together, these produce the answer 336.
//	
//	What do you get if you multiply together the number of trees encountered on 
//	each of the listed slopes?

enum class CellType : uint8
{
	Invalid,
	Empty,
	Tree
};

struct MoveConfig
{
	int32					dx;
	int32					dy;

	MoveConfig()
	{
		dx = 0;
		dy = 0;
	}

	MoveConfig(int32 x, int32 y)
	{
		dx = x;
		dy = y;
	}
};

struct Toboggan
{
	int32					x;
	int32					y;

	Toboggan()
	{
		x = 0;
		y = 0;
	}

	void					Move(int32 dx = 3, int32 dy = 1)
	{
		x += dx;
		y += dy;
	}
};

struct Map
{
	int32					width;
	int32					height;
	std::vector<CellType>	cells;

	const int32				WrapX(int32 index) const
	{
		return ((index % width) + width) % width;
	}

	const int32				WrapY(int32 index) const
	{
		return ((index % height) + height) % height;
	}

	const CellType			GetCellWrapped(int32 x, int32 y) const
	{
		return GetCell(WrapX(x), y);
	}

	const CellType			GetCell(int32 x, int32 y) const
	{
		return cells[width * y + x];
	}

	const bool				InMap(int32 x, int32 y) const
	{
		return y >= 0 && y < height;
	}
};

static CellType GetCellType(const char c)
{
	if (c == '#')
	{
		return CellType::Tree;
	}
	else
	{
		if (c == '.')
		{
			return CellType::Empty;
		}
	}

	return CellType::Invalid;
}

static int32 Solve_1(const std::vector<std::string> input)
{
	Map		map;
	map.width = (int32)input[0].size();
	map.height = (int32)input.size();

	for (size_t i = 0; i < input.size(); i++)
	{
		const std::string& line = input[i];
		for (size_t j = 0; j < line.size(); j++)
		{
			map.cells.push_back(GetCellType(line[j]));
		}
	}

	int			numTrees = 0;
	Toboggan	toboggan;

	while (map.InMap(toboggan.x, toboggan.y))
	{
		if (map.GetCellWrapped(toboggan.x, toboggan.y) == CellType::Tree)
		{
			numTrees++;
		}

		toboggan.Move(3, 1);
	}

	return numTrees;
}

static int64 Solve_2(const std::vector<std::string> input)
{
	Map		map;
	map.width = (int32)input[0].size();
	map.height = (int32)input.size();

	for (size_t i = 0; i < map.height; i++)
	{
		const std::string& line = input[i];
		for (size_t j = 0; j < line.size(); j++)
		{
			map.cells.push_back(GetCellType(line[j]));
		}
	}

	int64					total = 1;
	std::stack<MoveConfig>	moves;
	moves.push({ 1, 2 });
	moves.push({ 7, 1 });
	moves.push({ 5, 1 });
	moves.push({ 3, 1 });
	moves.push({ 1, 1 });

	while (!moves.empty())
	{
		int			numTrees = 0;
		Toboggan	toboggan;
		MoveConfig	config = moves.top();
		moves.pop();

		while (map.InMap(toboggan.x, toboggan.y))
		{
			if (map.GetCellWrapped(toboggan.x, toboggan.y) == CellType::Tree)
			{
				numTrees++;
			}

			toboggan.Move(config.dx, config.dy);
		}

		total *= numTrees;
	}

	return total;
}

void Day3::Part1()
{
	const std::vector<std::string> example =
	{
		"..##.......",
		"#...#...#..",
		".#....#..#.",
		"..#.#...#.#",
		".#...##..#.",
		"..#.##.....",
		".#.#.#....#",
		".#........#",
		"#.##...#...",
		"#...##....#",
		".#..#...#.#",
	};

	assert(Solve_1(example) == 7);
	printf("Day 3: %d\n", Solve_1(GetStrInput("inputs/day3.txt")));
}

void Day3::Part2()
{
	const std::vector<std::string> example =
	{
		"..##.......",
		"#...#...#..",
		".#....#..#.",
		"..#.#...#.#",
		".#...##..#.",
		"..#.##.....",
		".#.#.#....#",
		".#........#",
		"#.##...#...",
		"#...##....#",
		".#..#...#.#",
	};

	assert(Solve_2(example) == 336);
	printf("Day 3: %lld\n", Solve_2(GetStrInput("inputs/day3.txt"))); 
}