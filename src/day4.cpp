//
//	Copyright 2020 Jak Barnes. All Rights Reserved.
//

#include "day4.h"

//	
//	--- Day 4: Passport Processing ---
//	
//	You arrive at the airport only to realize that you grabbed your North Pole
//	Credentials instead of your passport. While these documents are extremely
//	similar, North Pole Credentials aren't issued by a country and therefore
//	aren't actually valid documentation for travel in most of the world.
//	
//	It seems like you're not the only one having problems, though; a very long
//	line has formed for the automatic passport scanners, and the delay could
//	upset your travel itinerary.
//	
//	Due to some questionable network security, you realize you might be able to
//	solve both of these problems at the same time.
//	
//	The automatic passport scanners are slow because they're having trouble
//	detecting which passports have all required fields. The expected fields are
//	as follows:
//	
//	-	byr (Birth Year)
//	-	iyr (Issue Year)
//	-	eyr (Expiration Year)
//	-	hgt (Height)
//	-	hcl (Hair Color)
//	-	ecl (Eye Color)
//	-	pid (Passport ID)
//	-	cid (Country ID)
//	
//	Passport data is validated in batch files (your puzzle input). Each
//	passport is represented as a sequence of key:value pairs separated by
//	spaces or newlines. Passports are separated by blank lines.
//
//	Here is an example batch file containing four passports:
//
//	ecl:gry pid:860033327 eyr:2020 hcl:#fffffd
//	byr:1937 iyr:2017 cid:147 hgt:183cm
//
//	iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884
//	hcl:#cfa07d byr:1929
//
//	hcl:#ae17e1 iyr:2013
//	eyr:2024
//	ecl:brn pid:760753108 byr:1931
//	hgt:179cm
//
//	hcl:#cfa07d eyr:2025 pid:166559648
//	iyr:2011 ecl:brn hgt:59in
//	The first passport is valid - all eight fields are present. The second
//	passport is invalid - it is missing hgt (the Height field).
//
//	The third passport is interesting; the only missing field is cid, so it
//	looks like data from North Pole Credentials, not a passport at all! Surely,
//	nobody would mind if you made the system temporarily ignore missing cid
//	fields. Treat this "passport" as valid.
//
//	The fourth passport is missing two fields, cid and byr. Missing cid is
//	fine, but missing any other field is not, so this passport is invalid.
//
//	According to the above rules, your improved system would report 2 valid
//	passports.
//
//	Count the number of valid passports - those that have all required fields.
//	Treat cid as optional. In your batch file, how many passports are valid?
//
//	--- Part Two ---
//	
//	The line is moving more quickly now, but you overhear airport security 
//	talking about how passports with invalid data are getting through. Better 
//	add some data validation, quick!
//	
//	You can continue to ignore the cid field, but each other field has strict 
//	rules about what values are valid for automatic validation:
//	
//	byr (Birth Year) - four digits; at least 1920 and at most 2002.
//	iyr (Issue Year) - four digits; at least 2010 and at most 2020.
//	eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
//	hgt (Height) - a number followed by either cm or in:
//	If cm, the number must be at least 150 and at most 193.
//	If in, the number must be at least 59 and at most 76.
//	hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
//	ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
//	pid (Passport ID) - a nine-digit number, including leading zeroes.
//	cid (Country ID) - ignored, missing or not.
//	Your job is to count the passports where all required fields are both 
//	present and valid according to the above rules. Here are some example values:
//	
//	byr valid:   2002
//	byr invalid: 2003
//	
//	hgt valid:   60in
//	hgt valid:   190cm
//	hgt invalid: 190in
//	hgt invalid: 190
//	
//	hcl valid:   #123abc
//	hcl invalid: #123abz
//	hcl invalid: 123abc
//	
//	ecl valid:   brn
//	ecl invalid: wat
//	
//	pid valid:   000000001
//	pid invalid: 0123456789
//	Here are some invalid passports:
//	
//	eyr:1972 cid:100
//	hcl:#18171d ecl:amb hgt:170 pid:186cm iyr:2018 byr:1926
//	
//	iyr:2019
//	hcl:#602927 eyr:1967 hgt:170cm
//	ecl:grn pid:012533040 byr:1946
//	
//	hcl:dab227 iyr:2012
//	ecl:brn hgt:182cm pid:021572410 eyr:2020 byr:1992 cid:277
//	
//	hgt:59cm ecl:zzz
//	eyr:2038 hcl:74454a iyr:2023
//	pid:3556412378 byr:2007
//	Here are some valid passports:
//	
//	pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:1980
//	hcl:#623a2f
//	
//	eyr:2029 ecl:blu cid:129 byr:1989
//	iyr:2014 pid:896056539 hcl:#a97842 hgt:165cm
//	
//	hcl:#888785
//	hgt:164cm byr:2001 iyr:2015 cid:88
//	pid:545766238 ecl:hzl
//	eyr:2022
//	
//	iyr:2010 hgt:158cm hcl:#b6652a ecl:blu byr:1944 eyr:2021 pid:093154719
//	Count the number of valid passports - those that have all required fields 
//	and valid values. Continue to treat cid as optional. In your batch file, 
//	how many passports are valid?

enum class MeasurementType
{
	Invalid,
	Centermeteres,
	Inches
};

struct Height
{
	int32				Value;
	int32				MinCm;
	int32				MaxCm;
	int32				MinIn;
	int32				MaxIn;
	MeasurementType		Measurement;
	uint8				bValid : 1;

	Height()
	{
		Value = -1;
		MinCm = 150;
		MaxCm = 193;
		MinIn = 59;
		MaxIn = 76;
		Measurement = MeasurementType::Invalid;
		bValid = false;
	}

	bool Parse(std::string input)
	{
		bValid = false;
		std::size_t found = input.find("cm");

		if (found != std::string::npos)
		{
			Measurement = MeasurementType::Centermeteres;
		}
		else
		{
			found = input.find("in");
			if (found != std::string::npos)
			{
				Measurement = MeasurementType::Inches;
			}
		}

		const std::string size = input.substr(0, input.size() - 2);
		if (IsInteger(size))
		{
			Value = std::stoi(size);
		}

		switch (Measurement)
		{
			default:
			case MeasurementType::Invalid:
				{
					bValid = false;
				}
				break;
			case MeasurementType::Centermeteres:
				{
					if (Value >= MinCm && Value <= MaxCm)
					{
						bValid = true;
					}
					else
					{
						Value = -1;
					}
				}
				break;
			case MeasurementType::Inches:
				{
					if (Value >= MinIn && Value <= MaxIn)
					{
						bValid = true;
					}
					else
					{
						Value = -1;
					}
				}
				break;
		}

		return bValid;
	}
};

struct Passport
{
	int32				byr;			//	(Birth Year)
	int32				iyr;			//	(Issue Year)
	int32				eyr;			//	(Expiration Year)
	Height				hgt;			//	(Height)
	std::string			hcl;			//	(Hair Color)
	std::string			ecl;			//	(Eye Color)
	std::string			pid;			//	(Passport ID)
	std::string			cid;			//	(Country ID)
	uint8				bIsValid : 1;

	Passport()
	{
		byr = -1;
		iyr = -1;
		eyr = -1;
		hgt = Height();
		hcl = "";
		ecl = "";
		pid = "";
		cid = "";
		bIsValid = false;
	}

	bool		GetKeyValue(std::string& input, std::string& key, std::string& value)
	{
		std::vector<std::string> keyValue;
		if (Split(keyValue, input, ":"))
		{
			key = keyValue[0];
			value = keyValue[1];
			return true;
		}
		return false;
	}

	int32		AsInteger(const std::string& value)
	{
		if (IsInteger(value))
		{
			return std::stoi(value);
		}
		return -1;
	}

	bool		ValidateYear(const std::string& value, int32 min, int32 max)
	{
		bool bValid = false;
		if (IsInteger(value))
		{
			int32 year = std::stoi(value);
			if (year >= min && year <= max)
			{
				bValid = true;
			}
		}
		return bValid;
	}

	bool		ValidateHairColour(const std::string& colour)
	{
		bool bValid = false;
		if (IsColour(colour))
		{
			bValid = true;
		}
		return bValid;
	}

	bool		ValidateEyeColour(const std::string& colour)
	{
		const std::string colours[7] = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
		bool bValid = false;
		for (int32 i = 0; i < 7; i++)
		{
			if (colours[i] == colour)
			{
				bValid = true;
				break;
			}
		}
		return bValid;
	}

	void		Parse(std::string input, bool bNewPolicy = false)
	{
		std::vector<std::string> parts;
		parts.reserve(8);

		if (Split(parts, input, " "))
		{
			int32 numFields = 0;
			
			for (size_t i = 0; i < parts.size(); i++)
			{
				if (parts[i] == "")
				{
					continue;
				}

				std::string key;
				std::string value;
				GetKeyValue(parts[i], key, value);
				
				if			(key == "byr")
				{
					numFields++;
					if (ValidateYear(value, 1920, 2002))
					{
						byr = AsInteger(value);
					}
				}
				else if		(key == "iyr")
				{
					numFields++;
					if (ValidateYear(value, 2010, 2020))
					{
						iyr = AsInteger(value);
					}
				}
				else if		(key == "eyr")
				{
					numFields++;
					if (ValidateYear(value, 2020, 2030))
					{
						eyr = AsInteger(value);
					}
				}
				else if		(key == "hgt")
				{
					numFields++;
					hgt.Parse(value);
				}
				else if		(key == "hcl")
				{
					numFields++;
					if (ValidateHairColour(value))
					{
						hcl = value;
					}
				}
				else if		(key == "ecl")
				{
					numFields++;
					if (ValidateEyeColour(value))
					{
						ecl = value;
					}
				}
				else if		(key == "pid")
				{
					numFields++;
					if (
						(std::all_of(value.begin(), value.end(), ::isdigit)) &&
						(value.size() == 9)
					)
					{
						pid = value;
					}
				}
				else if		(key == "cid")
				{
					cid = value;
				}
			}

			bIsValid = (numFields == 7);
		}
	}

	bool		IsValid()
	{
		bIsValid = true;

		if (byr == -1)			{ bIsValid = false; } 
		if (iyr == -1)			{ bIsValid = false; }
		if (eyr == -1)			{ bIsValid = false; }
		if (hcl.empty())		{ bIsValid = false; }
		if (ecl.empty())		{ bIsValid = false; }
		if (pid.empty())		{ bIsValid = false; }
		if (hgt.Value == -1)	{ bIsValid = false; }

		return bIsValid;
	}

	void		Print(int32 index)
	{
		if (IsValid())
		{
			printf("Passport (%d) was valid\n", index);
		}
		else
		{
			printf("Passport (%d) was invalid\n", index);
		}
		printf("byr:(%d)\n", byr);
		printf("iyr:(%d)\n", iyr);
		printf("eyr:(%d)\n", eyr);
		printf("hcl:(%s)\n", hcl.c_str());
		printf("ecl:(%s)\n", ecl.c_str());
		printf("pid:(%s)\n", pid.c_str());
		printf("cid:(%s)\n", cid.c_str());
		printf("hgt:(%d)\n", hgt.Value);
		printf("\n");
	}
};

static int32 Solve_1(const std::vector<std::string> input)
{
	int32 numValid = 0;
	int32 numLines = (int32)input.size();
	std::vector<Passport> passports;

	passports.resize(numLines);
	
	int32 i = 0;
	int32 pindex = 0;
	std::string data;

	for (i = 0; i < numLines; i++)
	{	
		while (i < numLines && input[i] != "")
		{
			data.append(" ");
			data.append(input[i]);
			i++;
		}

		passports[pindex].Parse(data, false);
		if (passports[pindex].bIsValid)
		{
			numValid++;
		}
		data = "";
		pindex++;
	}

	return numValid;
}

static int32 Solve_2(const std::vector<std::string> input)
{
	int32 numValid = 0;
	int32 numLines = (int32)input.size();
	std::vector<Passport> passports;

	passports.resize(numLines);
	
	int32 i = 0;
	int32 pindex = 0;
	std::string data;

	for (i = 0; i < numLines; i++)
	{	
		while (i < numLines && input[i] != "")
		{
			data.append(" ");
			data.append(input[i]);
			i++;
		}

		passports[pindex].Parse(data, false);
		if (passports[pindex].IsValid())
		{
			numValid++;
		}
		data = "";
		pindex++;
	}

	return numValid;
}

void Day4::Part1()
{
	const std::vector<std::string> example =
	{
		"ecl:gry pid:860033327 eyr:2020 hcl:#fffffd",
		"byr:1937 iyr:2017 cid:147 hgt:183cm",
		"",
		"iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884",
		"hcl:#cfa07d byr:1929",
		"",
		"hcl:#ae17e1 iyr:2013",
		"eyr:2024",
		"ecl:brn pid:760753108 byr:1931",
		"hgt:179cm",
		"",
		"hcl:#cfa07d eyr:2025 pid:166559648",
		"iyr:2011 ecl:brn hgt:59in"
	};

	assert(Solve_1(example) == 2);
	printf("Day 4: %d\n", Solve_1(GetStrInput("inputs/day4.txt")));
}

void Day4::Part2()
{
	std::vector<std::string> example =
	{
		"eyr:1972 cid:100",
		"hcl:#18171d ecl:amb hgt:170 pid:186cm iyr:2018 byr:1926",
		"",
		"iyr:2019",
		"hcl:#602927 eyr:1967 hgt:170cm",
		"ecl:grn pid:012533040 byr:1946",
		"",
		"hcl:dab227 iyr:2012",
		"ecl:brn hgt:182cm pid:021572410 eyr:2020 byr:1992 cid:277",
		"",
		"hgt:59cm ecl:zzz",
		"eyr:2038 hcl:74454a iyr:2023",
		"pid:3556412378 byr:2007",
	};
	assert(Solve_2(example) == 0);

	example =
	{
		"pid:087499704 hgt:74in ecl:grn iyr:2012 eyr:2030 byr:1980",
		"hcl:#623a2f",
		"",
		"eyr:2029 ecl:blu cid:129 byr:1989",
		"iyr:2014 pid:896056539 hcl:#a97842 hgt:165cm",
		"",
		"hcl:#888785",
		"hgt:164cm byr:2001 iyr:2015 cid:88",
		"pid:545766238 ecl:hzl",
		"eyr:2022",
		"",
		"iyr:2010 hgt:158cm hcl:#b6652a ecl:blu byr:1944 eyr:2021 pid:093154719"
	};
	assert(Solve_2(example) == 4);

	printf("Day 4: %d\n", Solve_2(GetStrInput("inputs/day4.txt")));
}