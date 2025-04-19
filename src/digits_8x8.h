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
const std::vector<std::string> digit_0 = {
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
const std::vector<std::string> digit_1 = {
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
const std::vector<std::string> digit_2 = {
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
const std::vector<std::string> digit_3 = {
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
const std::vector<std::string> digit_4 = {
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
const std::vector<std::string> digit_5 = {
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
const std::vector<std::string> digit_6 = {
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
const std::vector<std::string> digit_7 = {
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
const std::vector<std::string> digit_8 = {
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
const std::vector<std::string> digit_9 = {
    "  XXXX  ",
    " X    X ",
    " X    X ",
    " X    X ",
    "  XXXXX ",
    "      X ",
    " X    X ",
    "  XXXX  "
};

//
const std::vector<std::string> digits_8x8[] = {
    digit_0, digit_1, digit_2, digit_3, digit_4, digit_5, digit_6, digit_7, digit_8, digit_9
};

#endif	// DIGITS_8x8_H
