//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "Day17.h"

using namespace std;

//               __  __  __          __         
//    +-----+   |__||__||__|        |__|         __
//   /     /|   |__||__||__| x 2    |__| x 2    |__| x 2
//  +-----+ |   |__||__||__|        |__|        
//  |     | +
//  |     |/         18               6           2
//  +-----+

enum State : uint8
{
	Invalid,
	Inactive,
	Active
};

struct ConwayCube
{
	State	state;
	State	pendingState;

	ConwayCube()
	{
		state = Inactive;
		pendingState = Invalid;
	}

	void Update()
	{
		if (pendingState != Invalid)
		{
			state = pendingState;
			pendingState = Invalid;
		}
	}

};

struct PocketDimension
{
	PocketDimension(int32 newWorldSize, int32 numDimensions)
	{
		worldSize = newWorldSize;
		world.resize(std::pow(worldSize, numDimensions));
	}

	int32 Flatten(int32 x, int32 y, int32 z) const
	{
		return x + worldSize * (y + worldSize * z);
	}

	int32 Flatten(int32 x, int32 y, int32 z, int32 w) const
	{
		return x + y * worldSize + z * worldSize * worldSize + w * worldSize * worldSize * worldSize;
	}

	void Set(int32 x, int32 y, int32 z, int32 w, State value)
	{
		world[Flatten(x, y, z, w)].state = value;
	}

	void SetPending(int32 x, int32 y, int32 z, int32 w, State value)
	{
		world[Flatten(x, y, z, w)].pendingState = value;
	}

	State Get(int32 x, int32 y, int32 z, int32 w) const
	{
		return world[Flatten(x, y, z, w)].state;
	}

	void Cycle()
	{
		for (int32 i = 0; i < worldSize; i++)
		{
			for (int32 j = 0; j < worldSize; j++)
			{
				for (int32 k = 0; k < worldSize; k++)
				{
					State CurrState = Get(i, j, k, 0);
					int32 NumActive = GetNumActiveNeighbours(i, j, k);

					if (CurrState == Active)
					{
						if (NumActive == 2 || NumActive == 3)
						{
							// Stay active
						}
						else
						{
							SetPending(i, j, k, 0, Inactive);
						}
					}
					else
					{
						if (CurrState == Inactive)
						{
							if (NumActive == 3)
							{
								SetPending(i, j, k, 0, Active);
							}
							else
							{
								// Stay inactive
							}
						}
						else
						{
							// Stay inactive
						}
					}
				}
			}
		}
	}

	void Cycle4d()
	{
		for (int32 i = 0; i < worldSize; i++)
		{
			for (int32 j = 0; j < worldSize; j++)
			{
				for (int32 k = 0; k < worldSize; k++)
				{
					for (int32 l = 0; l < worldSize; l++)
					{
						State CurrState = Get(i, j, k, l);
						int32 NumActive = GetNumActiveNeighbours4d(i, j, k, l);

						if (CurrState == Active)
						{
							if (NumActive == 2 || NumActive == 3)
							{
								// Stay active
							}
							else
							{
								SetPending(i, j, k, l, Inactive);
							}
						}
						else
						{
							if (CurrState == Inactive)
							{
								if (NumActive == 3)
								{
									SetPending(i, j, k, l, Active);
								}
								else
								{
									// Stay inactive
								}
							}
							else
							{
								// Stay inactive
							}
						}
					}
				}
			}
		}
	}

	int32 GetNumActiveNeighbours(int32 x, int32 y, int32 z) const
	{
		int32 NumActive = 0;

		for (size_t i = x - 1; i <= x + 1; i++)
		{
			for (size_t j = y - 1; j <= y + 1; j++)
			{
				for (size_t k = z - 1; k <= z + 1; k++)
				{
					if (i == x && j == y && k == z)
					{
						continue;
					}

					if (
						(i >= 0 && i < worldSize) &&
						(j >= 0 && j < worldSize) &&
						(k >= 0 && k < worldSize)
						)
					{
						if (Get(i, j, k, 0) == Active)
						{
							NumActive++;
						}
					}
				}
			}
		}

		return NumActive;
	}

	int32 GetNumActiveNeighbours4d(int32 x, int32 y, int32 z, int32 w) const
	{
		int32 NumActive = 0;

		for (size_t i = x - 1; i <= x + 1; i++)
		{
			for (size_t j = y - 1; j <= y + 1; j++)
			{
				for (size_t k = z - 1; k <= z + 1; k++)
				{
					for (size_t l = w - 1; l <= w + 1; l++)
					{
						if (i == x && j == y && k == z && l == w)
						{
							continue;
						}

						if (
							(i >= 0 && i < worldSize) &&
							(j >= 0 && j < worldSize) &&
							(k >= 0 && k < worldSize) &&
							(l >= 0 && l < worldSize)
							)
						{
							if (Get(i, j, k, l) == Active)
							{
								NumActive++;
							}
						}
					}
				}
			}
		}

		return NumActive;
	}

	void Update()
	{
		for (int32 i = 0; i < world.size(); i++)
		{
			world[i].Update();
		}
	}

	void Print3d()
	{
		for (int32 k = 0; k < worldSize; k++)
		{
			printf("z=%d\n", k);
			for (int32 j = 0; j < worldSize; j++)
			{
				for (int32 i = 0; i < worldSize; i++)
				{
					State CurrState = Get(i, j, k, 0);

					if (CurrState == Active)
					{
						printf("#");
					}
					else if (CurrState == Inactive)
					{
						printf(".");
					}
					else
					{
						printf(" ");
					}
				}
				printf("\n");
			}
		}
	}

	int32 numDimensions = 3;
	int32 worldSize = 32;
	std::vector<ConwayCube> world;
};

static int32	Solve_1(vector<string> input)
{
	int32 answer = 0;
	PocketDimension dimension(32, 3);
	int32 offset = (dimension.worldSize / 2) - ((int32)input[0].size() / 2);

	for (int32 y = 0; y < input.size(); y++)
	{
		const std::string& line = input[y];
		for (int32 x = 0; x < input[y].size(); x++)
		{
			const char state = line[x];
			if (state == '#')
			{
				dimension.Set(offset + x, offset + y, offset, 0, State::Active);
			}
			else
			{
				dimension.Set(offset + x, offset + y, offset, 0, State::Inactive);
			}
		}
	}

	const int32 numCycles = 6;
	for (int32 i = 0; i < numCycles; i++)
	{
		//dimension.Print3d();
		dimension.Cycle();
		dimension.Update();
	}

	int32 size = dimension.worldSize * dimension.worldSize * dimension.worldSize;
	for (int32 i = 0; i < size; i++)
	{
		if (dimension.world[i].state == Active)
		{
			answer++;
		}
	}

	printf("Answer: %d\n", answer);

	return answer;
}

static int32	Solve_2(vector<string> input)
{
	int32 answer = 0;
	PocketDimension dimension(32, 4);
	int32 offset = (dimension.worldSize / 2) - ((int32)input[0].size() / 2);

	for (int32 y = 0; y < input.size(); y++)
	{
		const std::string& line = input[y];
		for (int32 x = 0; x < input[y].size(); x++)
		{
			const char state = line[x];
			if (state == '#')
			{
				dimension.Set(offset + x, offset + y, offset, offset, State::Active);
			}
			else
			{
				dimension.Set(offset + x, offset + y, offset, offset, State::Inactive);
			}
		}
	}

	const int32 numCycles = 6;
	for (int32 i = 0; i < numCycles; i++)
	{
		//dimension.Print();
		dimension.Cycle4d();
		dimension.Update();
	}

	for (int32 i = 0; i < dimension.world.size(); i++)
	{
		if (dimension.world[i].state == Active)
		{
			answer++;
		}
	}

	printf("Answer: %d\n", answer);

	return answer;
}

void Day17::Part1()
{
	assert(Solve_1(
		{
			".#.",
			"..#",
			"###"
		}
	) == 112);
	Solve_1(GetStrInput("inputs/Day17.txt"));
}

void Day17::Part2()
{
	assert(Solve_2(
		{
			".#.",
			"..#",
			"###"
		}
	) != 0);
	Solve_2(GetStrInput("inputs/Day17.txt"));
}