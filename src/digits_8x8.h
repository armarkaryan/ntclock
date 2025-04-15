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

// Рисуем изображение с оранжевым текстом
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

const std::string digits_8x8[] = {\
"\
  XXXX  \
 X    X \
 X  X X \
 X  X X \
 X X  X \
 X X  X \
 X    X \
  XXXX  ",
"\
    X   \
   XX   \
  X X   \
    X   \
    X   \
    X   \
    X   \
   XXX  ",
"\
  XXXX  \
 X    X \
      X \
      X \
    XX  \
  XX    \
 X      \
 XXXXXX ",
"\
  XXXX  \
 X    X \
      X \
    XX  \
      X \
      X \
 X    X \
  XXXX  ",
"\
 X    X \
 X    X \
 X    X \
 XXXXXX \
      X \
      X \
      X \
      X ",
"\
 XXXXXX \
 X      \
 X      \
 XXXXX  \
      X \
      X \
 X    X \
  XXXX  ",
"\
  XXXX  \
 X    X \
 X      \
 XXXXX  \
 X    X \
 X    X \
 X    X \
  XXXX  ",
"\
  XXXXX \
      X \
      X \
     X  \
    X   \
    X   \
    X   \
    X   ",
"\
  XXXX  \
 X    X \
 X    X \
  XXXX  \
 X    X \
 X    X \
 X    X \
  XXXX  ",
"\
  XXXX  \
 X    X \
 X    X \
 X    X \
  XXXXX \
      X \
 X    X \
  XXXX  "};

#endif	// DIGITS_8x8_H