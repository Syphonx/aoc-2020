//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "Day8.h"

//	--- Day 8: Handheld Halting ---
//
//	Your flight to the major airline hub reaches cruising altitude without 
//	incident. While you consider checking the in-flight menu for one of those 
//	drinks that come with a little umbrella, you are interrupted by the kid 
//	sitting next to you.
//	
//	Their handheld game console won't turn on! They ask if you can take a look.
//	
//	You narrow the problem down to a strange infinite loop in the boot code
//	(your puzzle input) of the device. You should be able to fix it, but first 
//	you need to be able to run the code in isolation.
//	
//	The boot code is represented as a text file with one instruction per line of 
//	text. Each instruction consists of an operation (acc, jmp, or nop) and an
//	argument (a signed number like +4 or -20).
//	
//	acc increases or decreases a single global value called the accumulator by the value given in the argument. For example, acc +7 would increase the accumulator by 7. The accumulator starts at 0. After an acc instruction, the instruction immediately below it is executed next.
//	jmp jumps to a new instruction relative to itself. The next instruction to execute is found using the argument as an offset from the jmp instruction; for example, jmp +2 would skip the next instruction, jmp +1 would continue to the instruction immediately below it, and jmp -20 would cause the instruction 20 lines above to be executed next.
//	nop stands for No OPeration - it does nothing. The instruction immediately below it is executed next.
//	For example, consider the following program:
//	
//	nop +0
//	acc +1
//	jmp +4
//	acc +3
//	jmp -3
//	acc -99
//	acc +1
//	jmp -4
//	acc +6
//	These instructions are visited in this order:
//	
//	nop +0  | 1
//	acc +1  | 2, 8(!)
//	jmp +4  | 3
//	acc +3  | 6
//	jmp -3  | 7
//	acc -99 |
//	acc +1  | 4
//	jmp -4  | 5
//	acc +6  |
//	
//	First, the nop +0 does nothing. Then, the accumulator is increased from 0 to 1 
//	(acc +1) and jmp +4 sets the next instruction to the other acc +1 near the bottom. 
//	After it increases the accumulator from 1 to 2, jmp -4 executes, setting the next 
//	instruction to the only acc +3. It sets the accumulator to 5, and jmp -3 causes the 
//	program to continue back at the first acc +1.
//	
//	This is an infinite loop: with this sequence of jumps, the program will run forever. 
//	The moment the program tries to run any instruction a second time, you know it will 
//	never terminate.
//	
//	Immediately before the program would run an instruction a second time, the value in 
//	the accumulator is 5.
//	
//	Run your copy of the boot code. Immediately before any instruction is executed a second
//	time, what value is in the accumulator?
//
//	--- Part Two ---
//	
//	After some careful analysis, you believe that exactly one instruction is corrupted.
//	
//	Somewhere in the program, either a jmp is supposed to be a nop, or a nop is supposed to 
//	be a jmp. (No acc instructions were harmed in the corruption of this boot code.)
//	
//	The program is supposed to terminate by attempting to execute an instruction immediately 
//	after the last instruction in the file. By changing exactly one jmp or nop, you can repair 
//	the boot code and make it terminate correctly.
//	
//	For example, consider the same program from above:
//	
//	nop +0
//	acc +1
//	jmp +4
//	acc +3
//	jmp -3
//	acc -99
//	acc +1
//	jmp -4
//	acc +6
//	If you change the first instruction from nop +0 to jmp +0, it would create a single-instruction 
//	infinite loop, never leaving that instruction. If you change almost any of the jmp instructions, 
//	the program will still eventually find another jmp instruction and loop forever.
//	
//	However, if you change the second-to-last instruction (from jmp -4 to nop -4), the program terminates! 
//	The instructions are visited in this order:
//	
//	nop +0  | 1
//	acc +1  | 2
//	jmp +4  | 3
//	acc +3  |
//	jmp -3  |
//	acc -99 |
//	acc +1  | 4
//	nop -4  | 5
//	acc +6  | 6
//	After the last instruction (acc +6), the program terminates by attempting to run the instruction below
//	the last instruction in the file. With this change, after the program terminates, the accumulator contains
//	the value 8 (acc +1, acc +1, acc +6).
//	
//	Fix the program so that it terminates normally by changing exactly one jmp (to nop) or nop (to jmp). 
//	What is the value of the accumulator after the program terminates?

enum class Opcode : uint8
{
	Inv,	// Invalid instruction
	Nop,	// No operation
	Acc,	// Accumulate
	Jmp		// Jump
};

struct Instruction
{
	Opcode				opcode;
	int16				value;

	Instruction()
	{
		opcode = Opcode::Inv;
	}

	Instruction(const std::string& instruction)
	{
		Parse(instruction);
	}

	void Parse(const std::string& instruction)
	{
		const std::string	opcodestr = instruction.substr(0, 3);
		const char			operand = instruction[4];
		const std::string	parameter = instruction.substr(5, instruction.size() - 5);
		//	printf("Parsed opcode: (%s) with param: %c%s\n", opcodestr.c_str(), operand, parameter.c_str());

		// Parse opcode

		if (opcodestr == "nop")
		{
			opcode = Opcode::Nop;
		}
		else if (opcodestr == "acc")
		{
			opcode = Opcode::Acc;
		}
		else if (opcodestr == "jmp")
		{
			opcode = Opcode::Jmp;
		}
		else
		{
			opcode = Opcode::Inv;
			printf("Invalid opcode: %s\n", instruction.c_str());
		}

		// Parse operand & value

		if (operand == '+')
		{
			value = std::stoi(parameter);
		}
		else if (operand == '-')
		{
			value = -std::stoi(parameter);
		}

	}
};

struct Machine
{
	int32				acc = 0;
	int32				ptr = 0;
	std::vector<bool>	counts;

	void Reset(int32 size)
	{
		acc = 0;
		ptr = 0;
		counts.clear();
		counts.resize(size);
	}

	int32 Execute(const std::vector<Instruction>& instructions)
	{
		while (ptr < instructions.size())
		{
			const Instruction& instruction = instructions[ptr];

			switch (instruction.opcode)
			{
				default:			// Fallthrough intentional
				case Opcode::Inv:
				case Opcode::Nop:
				{
					ptr++;
				}
				break;
				case Opcode::Acc:
				{
					acc += instruction.value;
					ptr++;
				}
				break;
				case Opcode::Jmp:
				{
					ptr += instruction.value;
				}
				break;
			}

			if (counts[ptr])
			{
				return acc;
			}
			else
			{
				counts[ptr] = true;
			}
		}

		return acc;
	}

	int32 Execute2(std::vector<Instruction>& instructions)
	{
		std::stack<int32> attempts;
		for (int32 i = 0; i < instructions.size(); i++)
		{
			const Instruction& instruction = instructions[i];
			if (
				(instruction.opcode == Opcode::Jmp) ||
				(instruction.opcode == Opcode::Nop)
			)
			{
				attempts.push(i);
			}
		}

		while (attempts.size() > 0)
		{
			bool			bSuccessful = true;
			Instruction&	instruction = instructions[attempts.top()];
			attempts.pop();
			Reset(instructions.size());

			if (instruction.opcode == Opcode::Jmp)
			{
				instruction.opcode = Opcode::Nop;
			}
			else
			{
				if (instruction.opcode == Opcode::Nop)
				{
					instruction.opcode = Opcode::Jmp;
				}
			}

			while (ptr < instructions.size())
			{
				int32 prevPtr = ptr;
				const Instruction& instruction = instructions[ptr];

				switch (instruction.opcode)
				{
					default:			// Fallthrough intentional
					case Opcode::Inv:
					case Opcode::Nop:
					{
						ptr++;
					}
					break;
					case Opcode::Acc:
					{
						acc += instruction.value;
						ptr++;
					}
					break;
					case Opcode::Jmp:
					{
						ptr += instruction.value;
					}
					break;
				}
				
				if (counts[prevPtr])
				{
					bSuccessful = false;
					break;
				}
				else
				{
					counts[prevPtr] = true;
				}
			}

			if (bSuccessful)
			{
				break;
			}
			else
			{
				// Repair the instruction if it didn't work
				if (instruction.opcode == Opcode::Jmp)
				{
					instruction.opcode = Opcode::Nop;
				}
				else
				{
					if (instruction.opcode == Opcode::Nop)
					{
						instruction.opcode = Opcode::Jmp;
					}
				}
			}
		}

		return acc;
	}
};

static int32 Solve_1(const std::vector<std::string> input)
{
	int32 answer = 0;
	Machine vm;
	std::vector<Instruction> instructions;
	instructions.reserve(input.size());
	vm.Reset(input.size());

	for (const std::string& line : input)
	{
		instructions.emplace_back(line);
	}

	answer = vm.Execute(instructions);

	printf("Answer: %d\n", answer);
	return answer;
}

static int32 Solve_2(const std::vector<std::string> input)
{
	int32 answer = 0;
	Machine vm;
	std::vector<Instruction> instructions;
	instructions.reserve(input.size());
	vm.Reset(input.size());

	for (const std::string& line : input)
	{
		instructions.emplace_back(line);
	}

	answer = vm.Execute2(instructions);

	printf("Answer: %d\n", answer);
	return answer;
}

void Day8::Part1()
{
	assert(Solve_1(
		{
			"nop +0",
			"acc +1",
			"jmp +4",
			"acc +3",
			"jmp -3",
			"acc -99",
			"acc +1",
			"jmp -4",
			"acc +6"
		}
	) == 5);
	Solve_1(GetStrInput("inputs/Day8.txt"));
}

void Day8::Part2()
{
	assert(Solve_2(
		{
			"nop +0",
			"acc +1",
			"jmp +4",
			"acc +3",
			"jmp -3",
			"acc -99",
			"acc +1",
			"jmp -4",
			"acc +6"
		}
	) == 8);
	Solve_2(GetStrInput("inputs/Day8.txt"));
}