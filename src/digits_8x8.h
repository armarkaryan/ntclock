#ifndef DIGITS_8x8_H
#define DIGITS_8x8_H

#include <vector>
#include <string>

#include "nttypes.h"

// Digit "0"
const struct nt::Image digit_8x8_0 = {
	{	// img
		"  XXXX  ",
		" X    X ",
		" X  X X ",
		" X  X X ",
		" X X  X ",
		" X X  X ",
		" X    X ",
		"  XXXX  "
	},
	8,	// width
	8	// height
};

// Digit "1"
const struct nt::Image digit_8x8_1 = {
	{	// img
		"    X   ",
		"   XX   ",
		"  X X   ",
		"    X   ",
		"    X   ",
		"    X   ",
		"    X   ",
		"   XXX  "
	},
	8,	// width
	8	// height
};

// Digit "2"
const struct nt::Image digit_8x8_2 = {
	{	// img
		"  XXXX  ",
		" X    X ",
		"      X ",
		"      X ",
		"    XX  ",
		"  XX    ",
		" X      ",
		" XXXXXX "
	},
	8,	// width
	8	// height
};

// Digit "3"
const struct nt::Image digit_8x8_3 = {
	{	// img
		"  XXXX  ",
		" X    X ",
		"      X ",
		"    XX  ",
		"      X ",
		"      X ",
		" X    X ",
		"  XXXX  "
	},
	8,	// width
	8	// height
};

// Digit "4"
const struct nt::Image digit_8x8_4 = {
	{	// img
		" X    X ",
		" X    X ",
		" X    X ",
		" XXXXXX ",
		"      X ",
		"      X ",
		"      X ",
		"      X "
	},
	8,	// width
	8	// height
};

// Digit "5"
const struct nt::Image digit_8x8_5 = {
	{	// img
		" XXXXXX ",
		" X      ",
		" X      ",
		" XXXXX  ",
		"      X ",
		"      X ",
		" X    X ",
		"  XXXX  "
	},
	8,	// width
	8	// height
};

// Digit "6"
const struct nt::Image digit_8x8_6 = {
	{	// img
		"  XXXX  ",
		" X    X ",
		" X      ",
		" XXXXX  ",
		" X    X ",
		" X    X ",
		" X    X ",
		"  XXXX  "
	},
	8,	// width
	8	// height
};

// Digit "7"
const struct nt::Image digit_8x8_7 = {
	{	// img
		"  XXXXX ",
		"      X ",
		"      X ",
		"     X  ",
		"    X   ",
		"    X   ",
		"    X   ",
		"    X   "
	},
	8,	// width
	8	// height
};

// Digit "8"
const struct nt::Image digit_8x8_8 = {
	{	// img
		"  XXXX  ",
		" X    X ",
		" X    X ",
		"  XXXX  ",
		" X    X ",
		" X    X ",
		" X    X ",
		"  XXXX  "
	},
	8,	// width
	8	// height
};

// Digit "9"
const struct nt::Image digit_8x8_9 = {
	{	// img
		"  XXXX  ",
		" X    X ",
		" X    X ",
		" X    X ",
		"  XXXXX ",
		"      X ",
		" X    X ",
		"  XXXX  "
	},
	8,	// width
	8	// height
};

// Array of digits image from 0 to 9
const std::vector<nt::Image> digits_8x8 = {
	digit_8x8_0,
	digit_8x8_1,
	digit_8x8_2,
	digit_8x8_3,
	digit_8x8_4,
	digit_8x8_5,
	digit_8x8_6,
	digit_8x8_7,
	digit_8x8_8,
	digit_8x8_9
};

#endif	// DIGITS_8x8_H
