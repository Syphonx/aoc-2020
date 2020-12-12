//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "Day7.h"

//	--- Day 7: Handy Haversacks ---
//	
//	You land at the regional airport in time for your next flight. In fact, 
//	it looks like you'll even have time to grab some food: all flights are
//	currently delayed due to issues in luggage processing.
//	
//	Due to recent aviation regulations, many rules (your puzzle input) are being 
//	enforced about bags and their contents; bags must be color-coded and must 
//	contain specific quantities of other color-coded bags. Apparently, nobody 
//	responsible for these regulations considered how long they would take to enforce!
//	
//	For example, consider the following rules:
//	
//	> light red bags contain 1 bright white bag, 2 muted yellow bags.
//	> dark orange bags contain 3 bright white bags, 4 muted yellow bags.
//	> bright white bags contain 1 shiny gold bag.
//		| Can contain another gold bag
//	> muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.
//		| Can contain another gold bag
//	x shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.
//		| Already a gold bag
//	x dark olive bags contain 3 faded blue bags, 4 dotted black bags.
//		| Already inside a gold bag
//	x vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.
//		| Already inside a gold bag
//	x faded blue bags contain no other bags.
//		| Already inside a gold bag and contains no other bags
//	x dotted black bags contain no other bags.
//		| Already inside a gold bag and contains no other bags
//		
//	These rules specify the required contents for 9 bag types. In this example, 
//	every faded blue bag is empty, every vibrant plum bag contains 11 bags (5 faded
//	blue and 6 dotted black), and so on.
//	
//	You have a shiny gold bag. If you wanted to carry it in at least one other bag,
//	how many different bag colors would be valid for the outermost bag? (In other 
//	words: how many colors can, eventually, contain at least one shiny gold bag?)
//	
//	In the above rules, the following options would be available to you:
//	
//	- A bright white bag, which can hold your shiny gold bag directly.
//	- A muted yellow bag, which can hold your shiny gold bag directly, plus some other bags.
//	- A dark orange bag, which can hold bright white and muted yellow bags, either of
//	  which could then hold your shiny gold bag.
//	- A light red bag, which can hold bright white and muted yellow bags, either of which
//	  could then hold your shiny gold bag.
//	
//	So, in this example, the number of bag colors that can eventually contain at least 
//	one shiny gold bag is 4.
//	
//	How many bag colors can eventually contain at least one shiny gold bag? (The list of 
//	rules is quite long; make sure you get all of it.)
//

struct Bag
{
	std::string			name;
	std::vector<int32>	children;
	uint8				valid : 1;

	Bag(const std::string& value)
	{
		name = value;
		valid = false;
	}
};

bool operator==(const Bag& lhs, const Bag& rhs)
{
	return lhs.name == rhs.name;
}

static int32 Solve_1(const std::vector<std::string> input)
{
	//
	// Bags must be color-coded and must contain specific quantities of other color-coded bags
	//

	int32						answer = 0;
	std::vector<std::string>	parts;
	std::vector<Bag>			bags;
	std::string					copy;

	// light red bags contain 1 bright white bag, 2 muted yellow bags.
	for (const auto& line : input)
	{
		copy = line;
		Remove(copy, ",.");
		Split(parts, copy, " ");

		// Insert
		std::string bag = parts[0] + parts[1];
		auto element_iter = std::find(bags.begin(), bags.end(), bag);
		int32 index = -1;

		if (element_iter == bags.end())
		{
			index =(int32) bags.size();
			bags.emplace_back(bag);
		}
		else
		{
			index = (int32)std::distance(bags.begin(), element_iter);
		}
		assert(index != -1);

		// Check for amount, or none
		if (parts[4] != "no")
		{
			for (size_t i = 4; i < parts.size(); i += 4)
			{
				bag = parts[i + 1] + parts[i + 2];
				auto child_iter = std::find(bags.begin(), bags.end(), bag);
				int32 child_index = -1;

				if (child_iter == bags.end())
				{
					child_index = (int32)bags.size();
					bags.emplace_back(bag);
				}
				else
				{
					child_index = (int32)std::distance(bags.begin(), child_iter);
				}
				assert(child_index != -1);
				bags[index].children.push_back(child_index);
			}
		}

		parts.clear();
	}
	
	Bag		answerbag("shinygold");
	auto	answer_iter = std::find(bags.begin(), bags.end(), answerbag);

	if (answer_iter != bags.end())
	{
		std::vector<int32> indexes;
		int32 answer_index = (int32)std::distance(bags.begin(), answer_iter);

		for (size_t i = 0; i < bags.size(); i++)
		{
			Bag& bag = bags[i];
			for (size_t c = 0; c < bag.children.size(); c++)
			{
				indexes.push_back(bag.children[c]);
			}
			
			for (size_t i = 0; i < indexes.size(); i++)
			{
				int32 index = indexes[i];

				if (index == answer_index || bags[index].valid)
				{
					answer++;
					bag.valid = true;
					break;
				}
				else
				{
					for (size_t c = 0; c < bags[index].children.size(); c++)
					{
						indexes.push_back(bags[index].children[c]);
					}
				}
			}

			indexes.clear();
		}
	}

	printf("Sum: %d\n", answer);
	return answer;
}

static int32 Solve_2(const std::vector<std::string> input)
{
	//
	// Bags must be color-coded and must contain specific quantities of other color-coded bags
	//

	int32						answer = 0;
	std::vector<std::string>	parts;
	std::vector<Bag>			bags;
	std::string					copy;

	// light red bags contain 1 bright white bag, 2 muted yellow bags.
	for (const auto& line : input)
	{
		copy = line;
		Remove(copy, ",.");
		Split(parts, copy, " ");

		// Insert
		std::string bag = parts[0] + parts[1];
		auto element_iter = std::find(bags.begin(), bags.end(), bag);
		int32 index = -1;

		if (element_iter == bags.end())
		{
			index =(int32) bags.size();
			bags.emplace_back(bag);
		}
		else
		{
			index = (int32)std::distance(bags.begin(), element_iter);
		}
		assert(index != -1);

		// Check for amount, or none
		if (parts[4] != "no")
		{
			for (size_t i = 4; i < parts.size(); i += 4)
			{
				int32 num = std::stoi(parts[i]);			
				bag = parts[i + 1] + parts[i + 2];

				auto child_iter = std::find(bags.begin(), bags.end(), bag);
				int32 child_index = -1;

				if (child_iter == bags.end())
				{
					child_index = (int32)bags.size();
					bags.emplace_back(bag);
				}
				else
				{
					child_index = (int32)std::distance(bags.begin(), child_iter);
				}
				assert(child_index != -1);

				for (size_t j = 0; j < num; j++)
				{
					bags[index].children.push_back(child_index);
				}
			}
		}

		parts.clear();
	}
	
	Bag		answerbag("shinygold");
	auto	answer_iter = std::find(bags.begin(), bags.end(), answerbag);

	if (answer_iter != bags.end())
	{
		std::vector<int32> indexes;
		int32 answer_index = (int32)std::distance(bags.begin(), answer_iter);
		
		Bag& bag = bags[answer_index];
		for (size_t c = 0; c < bag.children.size(); c++)
		{
			indexes.push_back(bag.children[c]);
		}

		for (size_t i = 0; i < indexes.size(); i++)
		{
			int32 index = indexes[i];
			for (size_t c = 0; c < bags[index].children.size(); c++)
			{
				indexes.push_back(bags[index].children[c]);
			}
		}

		answer = indexes.size();
	}

	printf("Sum: %d\n", answer);
	return answer;
}

void Day7::Part1()
{
	assert(Solve_1({
		"light red bags contain 1 bright white bag, 2 muted yellow bags.",
		"dark orange bags contain 3 bright white bags, 4 muted yellow bags.",
		"bright white bags contain 1 shiny gold bag.",
		"muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.",
		"shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.",
		"dark olive bags contain 3 faded blue bags, 4 dotted black bags.",
		"vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.",
		"faded blue bags contain no other bags.",
		"dotted black bags contain no other bags.",
		   }) != 0);
	Solve_1(GetStrInput("inputs/Day7.txt"));
}

void Day7::Part2()
{

	assert(Solve_2(
		{
			"shiny gold bags contain 2 dark red bags.",
			"dark red bags contain 2 dark orange bags.",
			"dark orange bags contain 2 dark yellow bags.",
			"dark yellow bags contain 2 dark green bags.",
			"dark green bags contain 2 dark blue bags.",
			"dark blue bags contain 2 dark violet bags.",
			"dark violet bags contain no other bags."
		}
	) != 0);
	Solve_2(GetStrInput("inputs/Day7.txt"));
}