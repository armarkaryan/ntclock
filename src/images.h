#ifndef IMAGES_CUSTOM_H
#define IMAGES_CUSTOM_H

#include <vector>
#include <string>

#include "nttypes.h"

// Custom image
const struct nt::Image image_colon = {
	{	// img
		"        ",
		"   XX   ",
		"   XX   ",
		"        ",
		"        ",
		"   XX   ",
		"   XX   ",
		"        "
	},
	8,	// width
	8	// height
};

// Custom image
const struct nt::Image image_custom = {
	{	// img
		"This is a custom",
		"size image that",
		"can be any height",
		"and width you want",
		"  ____  ",
		" /    \\ ",
		"|      |",
		" \\____/ "
	},
	8,	// width
	8	// height
};

// Array of digits image from 0 to 9
const std::vector<nt::Image> images = {
	image_custom, image_colon
};

#endif	// IMAGES_CUSTOM_H
