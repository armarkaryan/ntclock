#ifndef IMAGE_CUSTOM_H
#define IMAGE_CUSTOM_H

#include <vector>
#include <string>

#include "nttypes.h"

// Custom image
const struct nt::Image custom_image = {
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
	18,	// width
	8	// height
};

// Array of digits image from 0 to 9
const std::vector<nt::Image> custom_images = {
	custom_image
};

#endif	// IMAGE_CUSTOM_H
