#ifndef DIGITS_8x8_H
#define DIGITS_8x8_H

#include <vector>
#include <string>

const std::vector<std::string> custom_image = {
	"This is a custom",
	"size image that",
	"can be any height",
	"and width you want",
	"  ____  ",
	" /    \\ ",
	"|      |",
	" \\____/ "
};

// Digit "0"
const std::vector<std::string> digit_8x8_0 = {
    "  XXXX  ",
    " X    X ",
    " X  X X ",
    " X  X X ",
    " X X  X ",
    " X X  X ",
    " X    X ",
    "  XXXX  "
};

// Digit "1"
const std::vector<std::string> digit_8x8_1 = {
    "    X   ",
    "   XX   ",
    "  X X   ",
    "    X   ",
    "    X   ",
    "    X   ",
    "    X   ",
    "   XXX  "
};

// Digit "2"
const std::vector<std::string> digit_8x8_2 = {
    "  XXXX  ",
    " X    X ",
    "      X ",
    "      X ",
    "    XX  ",
    "  XX    ",
    " X      ",
    " XXXXXX "
};

// Digit "3"
const std::vector<std::string> digit_8x8_3 = {
    "  XXXX  ",
    " X    X ",
    "      X ",
    "    XX  ",
    "      X ",
    "      X ",
    " X    X ",
    "  XXXX  "
};

// Digit "4"
const std::vector<std::string> digit_8x8_4 = {
    " X    X ",
    " X    X ",
    " X    X ",
    " XXXXXX ",
    "      X ",
    "      X ",
    "      X ",
    "      X "
};

// Digit "5"
const std::vector<std::string> digit_8x8_5 = {
    " XXXXXX ",
    " X      ",
    " X      ",
    " XXXXX  ",
    "      X ",
    "      X ",
    " X    X ",
    "  XXXX  "
};

// Digit "6"
const std::vector<std::string> digit_8x8_6 = {
    "  XXXX  ",
    " X    X ",
    " X      ",
    " XXXXX  ",
    " X    X ",
    " X    X ",
    " X    X ",
    "  XXXX  "
};

// Digit "7"
const std::vector<std::string> digit_8x8_7 = {
    "  XXXXX ",
    "      X ",
    "      X ",
    "     X  ",
    "    X   ",
    "    X   ",
    "    X   ",
    "    X   "
};

// Digit "8"
const std::vector<std::string> digit_8x8_8 = {
    "  XXXX  ",
    " X    X ",
    " X    X ",
    "  XXXX  ",
    " X    X ",
    " X    X ",
    " X    X ",
    "  XXXX  "
};

// Digit "9"
const std::vector<std::string> digit_8x8_9 = {
    "  XXXX  ",
    " X    X ",
    " X    X ",
    " X    X ",
    "  XXXXX ",
    "      X ",
    " X    X ",
    "  XXXX  "
};

// Array of digits image from 0 to 9
const std::vector<std::string> digits_8x8[] = {
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
