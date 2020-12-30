//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "Day18.h"

using namespace std;

enum EOperators : uint8
{
	OPERATOR_NULL,
	OPERATOR_ADDITION,			/// +
	OPERATOR_SUBTRACTION,		/// -
	OPERATOR_MULTIPLICATION,	/// *
	OPERATOR_DIVISION,			/// /
};

struct Operator
{
	// Operator, one of the OPERATOR_* enum definitions
	int64	op;
	int64	precedence;

	// 'L' = left or 'R' = right
	int64	associativity;

	Operator(int64 opr, int64 prec, int64 assoc) :
		op(opr),
		precedence(prec),
		associativity(assoc)
	{
	}
};

struct OperatorValue
{
	Operator	op;
	int64		value;

	OperatorValue(const Operator& opr, int64 val) :
		op(opr),
		value(val)
	{
	}

	int64 GetPrecedence() const
	{
		return op.precedence;
	}

	bool IsNull() const
	{
		return op.op == OPERATOR_NULL;
	}
};

struct Calculator
{

public:

	std::string					expr;
	std::size_t					index;
	std::stack<OperatorValue>	stack;
	std::map<char, int32>		precedence;

	int64 Solve(const std::string& expression)
	{
		int64 result = 0;
		index = 0;
		expr = expression;
		result = ParseExpression();
		return result;
	}

	int64 Solve(char c)
	{
		std::string expr(1, c);
		return Solve(expr);
	}

	int64 Calculate(int64 v1, int64 v2, const Operator& op) const
	{
		switch (op.op)
		{
			case OPERATOR_ADDITION:			return v1 + v2;
			case OPERATOR_SUBTRACTION:		return v1 - v2;
			case OPERATOR_MULTIPLICATION:	return v1 * v2;
			case OPERATOR_DIVISION:			return v1 / v2;
			default:						return 0;
		}
	}

	bool IsEnd() const
	{
		return index >= expr.size();
	}

	char GetCharacter() const
	{
		if (!IsEnd())
			return expr[index];
		return 0;
	}

	void Expect(const std::string& str)
	{
		index += str.size();
	}

	void EatSpaces()
	{
		while (std::isspace(GetCharacter()) != 0)
			index++;
	}

	Operator ParseOperator()
	{
		EatSpaces();
		switch (GetCharacter())
		{
			case '+': index++;		return Operator(OPERATOR_ADDITION, precedence['+'], 'L');
			case '-': index++;		return Operator(OPERATOR_SUBTRACTION, precedence['-'], 'L');
			case '/': index++;		return Operator(OPERATOR_DIVISION, precedence['/'], 'L');
			case '*': index++;		return Operator(OPERATOR_MULTIPLICATION, precedence['*'], 'L');
			default:				return Operator(OPERATOR_NULL, 0, 'L');
		}
	}

	static int64 ToInteger(char c)
	{
		if (c >= '0' && c <= '9')
			return c - '0';
		return 0xf + 1;
	}

	int64 GetInteger() const
	{
		return ToInteger(GetCharacter());
	}

	int64 ParseDecimal()
	{
		int64 value = 0;
		for (int64 d; (d = GetInteger()) <= 9; index++)
			value = value * 10 + d;
		return value;
	}

	int64 ParseValue()
	{
		int64 val = 0;
		EatSpaces();

		switch (GetCharacter())
		{
			case '0':
			{
				val = ParseDecimal();
			}
			break;

			case '1': case '2': case '3': case '4': case '5':
			case '6': case '7': case '8': case '9':
			{
				val = ParseDecimal();
			}
			break;

			case '(':
			{
				index++;
				val = ParseExpression();
				EatSpaces();
				index++;
			}
			break;

			case '+':
			{
				index++;
				val = ParseValue();
			}
			break;

			case '-':
			{
				index++;
				val = ParseValue() * static_cast<int64>(-1);
			}
			break;

			default:
			{
			}
			break;
		}
		return val;
	}

	int64 ParseExpression()
	{
		stack.push(OperatorValue(Operator(OPERATOR_NULL, 0, 'L'), 0));

		// first parse value on the left
		int64 value = ParseValue();

		while (!stack.empty())
		{
			// parse an operator (+, -, *, ...)
			Operator op(ParseOperator());

			while (
				op.precedence < stack.top().GetPrecedence() || (
				op.precedence == stack.top().GetPrecedence() &&
				op.associativity == 'L')
			)
			{
				// end reached
				if (stack.top().IsNull())
				{
					stack.pop();
					return value;
				}

				// do the calculation ("reduce"), producing a new value
				value = Calculate(stack.top().value, value, stack.top().op);
				stack.pop();
			}

			// store on stack_ and continue parsing ("shift")
			stack.push(OperatorValue(op, value));

			// parse value on the right
			value = ParseValue();
		}
		return 0;
	}

};

static uint64	Solve_1(vector<string> input)
{
	uint64		answer = 0;
	Calculator	calc;
	calc.precedence['+'] = 10;
	calc.precedence['-'] = 10;
	calc.precedence['*'] = 10;
	calc.precedence['/'] = 10;

	for (const std::string& expression : input)
	{
		answer += calc.Solve(expression);
	}

	printf("Answer: %lld\n", answer);

	return answer;
}

static int64	Solve_2(vector<string> input)
{
	uint64		answer = 0;
	Calculator	calc;
	calc.precedence['+'] = 20;
	calc.precedence['-'] = 10;
	calc.precedence['*'] = 15;
	calc.precedence['/'] = 10;

	for (const std::string& expression : input)
	{
		answer += calc.Solve(expression);
	}

	printf("Answer: %lld\n", answer);

	return answer;
}

void Day18::Part1()
{
	assert(Solve_1({ "1 + (2 * 3) + (4 * (5 + 6))" }) == 51);
	assert(Solve_1({ "2 * 3 + (4 * 5)" }) == 26);
	assert(Solve_1({ "5 + (8 * 3 + 9 + 3 * 4 * 3)" }) == 437);
	assert(Solve_1({ "5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))" }) == 12240);
	assert(Solve_1({ "((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2" }) == 13632);

	Solve_1(GetStrInput("inputs/Day18.txt"));
}

void Day18::Part2()
{
	assert(Solve_2({ "1 + (2 * 3) + (4 * (5 + 6))" }) == 51);
	assert(Solve_2({ "2 * 3 + (4 * 5)" }) == 46);
	assert(Solve_2({ "5 + (8 * 3 + 9 + 3 * 4 * 3)" }) == 1445);
	assert(Solve_2({ "5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))" }) == 669060);
	assert(Solve_2({ "((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2" }) == 23340);

	Solve_2(GetStrInput("inputs/Day18.txt"));
}